#include "Aircraft.h"
#include "Runway.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <unistd.h>
using namespace std;

// Reads BOS_flights.csv and loads each flight into a queue
queue<Aircraft> loadFlights(const string &filename)
{
    queue<Aircraft> flightQueue;
    ifstream file(filename);
    string line;

    // Skip the header row
    getline(file, line);

    // Parse each line into an Aircraft object
    while (getline(file, line))
    {
        stringstream ss(line);
        string icao24, callsign, country, lon, lat, alt, onGround, vel, track, vRate, reqType;

        getline(ss, icao24, ',');
        getline(ss, callsign, ',');
        getline(ss, country, ',');
        getline(ss, lon, ',');
        getline(ss, lat, ',');
        getline(ss, alt, ',');
        getline(ss, onGround, ',');
        getline(ss, vel, ',');
        getline(ss, track, ',');
        getline(ss, vRate, ',');
        getline(ss, reqType, ',');

        // Remove any trailing whitespace or newline characters from reqType
        reqType.erase(0, reqType.find_first_not_of(" \t\r\n"));
        reqType.erase(reqType.find_last_not_of(" \t\r\n") + 1);

        // Set status based on whether the flight is landing or taking off
        string status = (reqType == "landing") ? "Inbound" : "Outbound";

        Aircraft a(
            icao24,
            callsign,
            status,
            stod(lon),
            stod(lat),
            stod(alt),
            stod(vel),
            stoi(track),
            reqType);
        flightQueue.push(a);
    }
    return flightQueue;
}

// Prints the current occupancy status of both runways
void printStatus(const Runway &r1, const Runway &r2)
{
    cout << "\n--- Runway Status ---" << endl;
    r1.displayInfo();
    r2.displayInfo();
    cout << "---------------------\n" << endl;
}

int main()
{
    // Load all flights from the CSV into the queue
    queue<Aircraft> flightQueue = loadFlights("../data/BOS_flights.csv");

    if (flightQueue.empty())
    {
        cout << "Error: Could not load flight data. Check that BOS_flights.csv is in the data folder." << endl;
        return 1;
    }

    // Initialize two runways
    Runway r1("R001", 4000, 90);
    Runway r2("R002", 3500, 270);

    cout << "========================================" << endl;
    cout << "   ATC SYSTEM ONLINE - BOS Airport      " << endl;
    cout << "========================================" << endl;
    cout << "Commands: assign R001 | assign R002 | deny | status" << endl;
    cout << "========================================\n" << endl;

    sleep(1);

    // Process each flight in the queue one at a time
    while (!flightQueue.empty())
    {
        Aircraft current = flightQueue.front();
        flightQueue.pop();

        // Display the incoming flight request
        cout << "[INCOMING] " << current.getCalsign()
             << " requesting " << current.getRequestType() << "." << endl;
        current.displayInfo();
        cout << endl;

        // Keep prompting the controller until the flight is handled
        bool handled = false;
        while (!handled)
        {
            cout << "> ";
            string cmd;
            getline(cin, cmd);

            if (cmd == "assign R001" || cmd == "assign r001")
            {
                if (r1.assignAircraft(current.getFlightId()))
                {
                    cout << "[CONFIRMED] " << current.getCalsign()
                         << " assigned to R001." << endl;
                    cout << "[CLEARED] " << current.getCalsign()
                         << " cleared for " << current.getRequestType()
                         << " on R001." << endl;
                    sleep(2); // Simulate time for landing/takeoff
                    cout << "[SUCCESS] " << current.getCalsign()
                         << " has completed " << current.getRequestType()
                         << " successfully. R001 is now clear.\n" << endl;
                    handled = true;
                    r1.clearRunway();
                }
                else
                {
                    cout << "[ERROR] R001 is occupied. Choose another runway or deny.\n" << endl;
                }
            }
            else if (cmd == "assign R002" || cmd == "assign r002")
            {
                if (r2.assignAircraft(current.getFlightId()))
                {
                    cout << "[CONFIRMED] " << current.getCalsign()
                         << " assigned to R002." << endl;
                    cout << "[CLEARED] " << current.getCalsign()
                         << " cleared for " << current.getRequestType()
                         << " on R002." << endl;
                    sleep(2); // Simulate time for landing/takeoff
                    cout << "[SUCCESS] " << current.getCalsign()
                         << " has completed " << current.getRequestType()
                         << " successfully. R002 is now clear.\n" << endl;
                    handled = true;
                    r2.clearRunway();
                }
                else
                {
                    cout << "[ERROR] R002 is occupied. Choose another runway or deny.\n" << endl;
                }
            }
            else if (cmd == "deny")
            {
                // Controller denied the request, move to next flight
                cout << "[DENIED] " << current.getCalsign()
                     << " request denied. Aircraft holding.\n" << endl;
                handled = true;
            }
            else if (cmd == "status")
            {
                printStatus(r1, r2);
            }
            else
            {
                cout << "[UNKNOWN COMMAND] Use: assign R001 | assign R002 | deny | status" << endl;
            }
        }
        sleep(1);
    }

    cout << "========================================" << endl;
    cout << "   All flights handled. ATC session complete." << endl;
    cout << "========================================" << endl;

    return 0;
}
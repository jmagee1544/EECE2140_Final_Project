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

// Parse the CSV and load aircraft into the queue
queue<Aircraft> loadFlights(const string &filename)
{
    queue<Aircraft> flightQueue;
    ifstream file(filename);
    string line;

    // Skip header line
    getline(file, line);

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

        // Trim whitespace from reqType
        reqType.erase(0, reqType.find_first_not_of(" \t\r\n"));
        reqType.erase(reqType.find_last_not_of(" \t\r\n") + 1);

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

void printStatus(const Runway &r1, const Runway &r2)
{
    cout << "\n--- Runway Status ---" << endl;
    r1.displayInfo();
    r2.displayInfo();
    cout << "---------------------\n"
         << endl;
}

int main()
{
    // Load flights from CSV
    queue<Aircraft> flightQueue = loadFlights("../data/BOS_flights.csv");

    if (flightQueue.empty())
    {
        cout << "Error: Could not load flight data. Check that BOS_flights.csv is in the data folder." << endl;
        return 1;
    }

    // Create runways
    Runway r1("R001", 4000, 90);
    Runway r2("R002", 3500, 270);

    cout << "========================================" << endl;
    cout << "   ATC SYSTEM ONLINE - BOS Airport      " << endl;
    cout << "========================================" << endl;
    cout << "Commands: assign R001 | assign R002 | deny | status" << endl;
    cout << "========================================\n"
         << endl;

    sleep(1);

    while (!flightQueue.empty())
    {
        Aircraft current = flightQueue.front();
        flightQueue.pop();

        // Display incoming flight request
        cout << "[INCOMING] " << current.getCalsign()
             << " requesting " << current.getRequestType() << "." << endl;
        current.displayInfo();
        cout << endl;

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
                    sleep(2);
                    cout << "[SUCCESS] " << current.getCalsign()
                         << " has completed " << current.getRequestType()
                         << " successfully. R001 is now clear.\n"
                         << endl;
                    handled = true;
                    r1.clearRunway();
                }
                else
                {
                    cout << "[ERROR] R001 is occupied. Choose another runway or deny.\n"
                         << endl;
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
                    sleep(2);
                    cout << "[SUCCESS] " << current.getCalsign()
                         << " has completed " << current.getRequestType()
                         << " successfully. R002 is now clear.\n"
                         << endl;
                    handled = true;
                    r2.clearRunway();
                }
                else
                {
                    cout << "[ERROR] R002 is occupied. Choose another runway or deny.\n"
                         << endl;
                }
            }
            else if (cmd == "deny")
            {
                cout << "[DENIED] " << current.getCalsign()
                     << " request denied. Aircraft holding.\n"
                     << endl;
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
#include "Aircraft.h"
#include "Runway.h"
#include "AirTrafficEntity.h"
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

    // Safety check for file opening
    if (!file.is_open())
    {
        cout << "Error: Could not open file " << filename << endl;
        return flightQueue;
    }

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

        try
        {
            Aircraft a(
                icao24,
                callsign,
                status,
                stod(lon),
                stod(lat),
                stod(alt),
                stod(vel),
                static_cast<int>(stod(track)),
                reqType);
            flightQueue.push(a);
        }
        catch (const invalid_argument &e)
        {
            cout << "Warning: Skipping malformed flight entry for " << callsign << endl;
        }
    }
    return flightQueue;
}

// Prints the current occupancy status of both runways, using base class pointers
void printStatus(const vector<AirTrafficEntity *> &entities)
{
    cout << "\n--- Runway Status ---" << endl;

    // Polymorphic display of all runways in the system through inherited objects
    for (AirTrafficEntity *entity : entities)
    {
        entity->displayInfo();
    }
    cout << "---------------------\n"
         << endl;
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
    const int RUNWAY1_LENGTH = 4000;
    const int RUNWAY1_ORIENTATION = 90;
    const int RUNWAY2_LENGTH = 3500;
    const int RUNWAY2_ORIENTATION = 270;

    Runway r1("R001", RUNWAY1_LENGTH, RUNWAY1_ORIENTATION);
    Runway r2("R002", RUNWAY2_LENGTH, RUNWAY2_ORIENTATION);

    // AirTrafficEntity as pointers for inheritance and polymorphic display
    // Raw pointers to stack-allocated objects — no ownership, no delete needed
    vector<AirTrafficEntity *> runwayEntities;
    runwayEntities.push_back(&r1);
    runwayEntities.push_back(&r2);

    cout << "========================================" << endl;
    cout << "   ATC SYSTEM ONLINE - BOS Airport      " << endl;
    cout << "========================================" << endl;
    cout << "Commands: assign R001 | assign R002 | deny | status" << endl;
    cout << "========================================\n"
         << endl;

    const int OPERATION_DELAY = 2;
    const int FLIGHT_DELAY = 1;

    sleep(FLIGHT_DELAY);

    // Process each flight in the queue one at a time
    while (!flightQueue.empty())
    {
        Aircraft current = flightQueue.front();
        flightQueue.pop();

        AirTrafficEntity *currentEntity = &current;

        // Display the incoming flight request
        cout << "[INCOMING] " << current.getcallsign()
             << " requesting " << current.getRequestType() << "." << endl;
        currentEntity->displayInfo();
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
                if (r1.assignAircraft(current.getId(), current.getX(), current.getY()))
                {
                    cout << "[CONFIRMED] " << current.getcallsign()
                         << " assigned to R001." << endl;
                    cout << "[CLEARED] " << current.getcallsign()
                         << " cleared for " << current.getRequestType()
                         << " on R001." << endl;
                    sleep(OPERATION_DELAY); // Simulate time for landing/takeoff
                    cout << "[SUCCESS] " << current.getcallsign()
                         << " has completed " << current.getRequestType()
                         << " successfully. R001 is now clear.\n"
                         << endl;
                    handled = true;
                    r1.clearRunway();
                }
                else
                {
                    cout << "[ERROR] R001 unavailable: occupied or spacing requirements not met. Choose another runway or deny.\n"
                         << endl;
                }
            }
            else if (cmd == "assign R002" || cmd == "assign r002")
            {
                if (r2.assignAircraft(current.getId(), current.getX(), current.getY()))
                {
                    cout << "[CONFIRMED] " << current.getcallsign()
                         << " assigned to R002." << endl;
                    cout << "[CLEARED] " << current.getcallsign()
                         << " cleared for " << current.getRequestType()
                         << " on R002." << endl;
                    sleep(OPERATION_DELAY); // Simulate time for landing/takeoff
                    cout << "[SUCCESS] " << current.getcallsign()
                         << " has completed " << current.getRequestType()
                         << " successfully. R002 is now clear.\n"
                         << endl;
                    handled = true;
                    r2.clearRunway();
                }
                else
                {
                    cout << "[ERROR] R002 unavailable: occupied or spacing requirements not met. Choose another runway or deny.\n"
                         << endl;
                }
            }
            else if (cmd == "deny")
            {
                // Controller denied the request, move to next flight
                cout << "[DENIED] " << current.getcallsign()
                     << " request denied. Aircraft holding.\n"
                     << endl;
                handled = true;
            }
            else if (cmd == "status")
            {
                printStatus(runwayEntities);
            }
            else
            {
                cout << "[UNKNOWN COMMAND] Use: assign R001 | assign R002 | deny | status" << endl;
            }
        }
        sleep(FLIGHT_DELAY);
    }

    cout << "========================================" << endl;
    cout << "   All flights handled. ATC session complete." << endl;
    cout << "========================================" << endl;

    return 0;
}
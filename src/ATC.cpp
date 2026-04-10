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

// Tracks a single controller action for the end-of-session log
struct LogEntry {
    string callsign;
    string requestType;
    string action;
    string runway;
};

// Parses a single CSV line into an Aircraft and pushes it to the queue
void parseFlight(const string &line, queue<Aircraft> &flightQueue)
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

    reqType.erase(0, reqType.find_first_not_of(" \t\r\n"));
    reqType.erase(reqType.find_last_not_of(" \t\r\n") + 1);

    string status = (reqType == "landing") ? "Inbound" : "Outbound";

    try {
        Aircraft a(icao24, callsign, status,
                   stod(lon), stod(lat), stod(alt),
                   stod(vel), static_cast<int>(stod(track)), reqType);
        flightQueue.push(a);
    } catch (const invalid_argument &e) {
        cout << "[WARNING] Skipping malformed entry for " << callsign << endl;
    }
}

// Reads BOS_flights.csv and loads each flight into a queue
queue<Aircraft> loadFlights(const string &filename)
{
    queue<Aircraft> flightQueue;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return flightQueue;
    }

    getline(file, line); // skip header
    while (getline(file, line))
        parseFlight(line, flightQueue);

    return flightQueue;
}

// Prints the ATC header and current runway status
void printDisplay(const Runway &r1, const Runway &r2, const Runway &r3)
{
    cout << "\n========================================" << endl;
    cout << "     AIR TRAFFIC CONTROL SYSTEM" << endl;
    cout << "     Logan Airport | Boston, MA" << endl;
    cout << "========================================" << endl;

    auto runwayStatus = [](const Runway &r) {
        string status = r.getIsOccupied() ? "OCCUPIED" : "OPEN";
        string clearable = "";
        if (r.getIsOccupied() && r.isClearable())
            clearable = " (ready to clear)";
        cout << "  " << r.getRunwayId() << ": " << status << clearable << endl;
    };

    cout << "--- Runways ---" << endl;
    runwayStatus(r1);
    runwayStatus(r2);
    runwayStatus(r3);
    cout << "=======================================\n" << endl;
}

// Prints the end-of-session action log
void printLog(const vector<LogEntry> &log)
{
    cout << "\n========================================" << endl;
    cout << "         SESSION ACTION LOG" << endl;
    cout << "========================================" << endl;
    for (const auto &entry : log) {
        cout << "[" << entry.action << "] " << entry.callsign
             << " (" << entry.requestType << ")";
        if (!entry.runway.empty())
            cout << " -> " << entry.runway;
        cout << endl;
    }
    cout << "========================================" << endl;
}

// Returns a runway pointer by ID string, or nullptr if not found
Runway* getRunway(const string &id, Runway &r1, Runway &r2, Runway &r3)
{
    if (id == "R01") return &r1;
    if (id == "R02") return &r2;
    if (id == "R03") return &r3;
    return nullptr;
}

int main()
{
    queue<Aircraft> flightQueue = loadFlights("../data/BOS_flights.csv");

    if (flightQueue.empty()) {
        cout << "Error: Could not load flight data." << endl;
        return 1;
    }

    Runway r1("R01", 4000, 90);
    Runway r2("R02", 3500, 270);
    Runway r3("R03", 3000, 180);

    vector<LogEntry> log;

    while (!flightQueue.empty())
    {
        r1.tick();
        r2.tick();
        r3.tick();

        Aircraft current = flightQueue.front();
        flightQueue.pop();

        bool handled = false;
        bool needsDisplay = true;

        while (!handled)
        {
            if (needsDisplay) {
                printDisplay(r1, r2, r3);
                cout << "[REQUEST] " << current.getCallsign()
                     << " requesting " << current.getRequestType()
                     << " | " << current.getId()
                     << " | Alt: " << current.getAltitude() << "ft"
                     << " | Speed: " << current.getSpeed() << "kts" << endl;

                if (current.getRequestType() == "takeoff")
                    cout << "[INFO] Takeoff — runway locked for 2 flight cycles." << endl;
                else
                    cout << "[INFO] Landing — runway clearable after 1 flight cycle." << endl;

                cout << "\nCommands: a (approve) | d (deny) | clear R01/R02/R03" << endl;
            }

            needsDisplay = false;
            cout << "> ";

            string cmd;
            getline(cin, cmd);

            // --- CLEAR ---
            if (cmd.rfind("clear ", 0) == 0) {
                string rid = cmd.substr(6);
                Runway *rwy = getRunway(rid, r1, r2, r3);
                if (!rwy) {
                    cout << "[ERROR] Unknown runway: " << rid << endl;
                } else if (!rwy->getIsOccupied()) {
                    cout << "[WARNING] " << rid << " is already open." << endl;
                } else if (!rwy->isClearable()) {
                    cout << "[WARNING] " << rid << " cannot be cleared yet — still in progress." << endl;
                } else {
                    rwy->clearRunway();
                    cout << "[CLEARED] " << rid << " is now open." << endl;
                    log.push_back({"", "", "CLEARED", rid});
                }
            }

            // --- DENY ---
            else if (cmd == "d") {
                cout << "[DENIED] " << current.getCallsign() << " added to end of queue." << endl;
                flightQueue.push(current);
                log.push_back({current.getCallsign(), current.getRequestType(), "DENIED", ""});
                handled = true;
            }

            // --- APPROVE ---
            else if (cmd == "a") {
                bool anyOpen = !r1.getIsOccupied() || !r2.getIsOccupied() || !r3.getIsOccupied();
                if (!anyOpen) {
                    cout << "[WARNING] All runways occupied. Clear a runway or deny." << endl;
                } else {
                    cout << "Assign to runway (a R01 / a R02 / a R03) or d to deny: ";
                    bool assigned = false;
                    while (!assigned) {
                        string rcmd;
                        getline(cin, rcmd);

                        if (rcmd == "d") {
                            cout << "[DENIED] " << current.getCallsign() << " added to end of queue." << endl;
                            flightQueue.push(current);
                            log.push_back({current.getCallsign(), current.getRequestType(), "DENIED", ""});
                            handled = true;
                            assigned = true;
                        } else if (rcmd.rfind("a ", 0) == 0) {
                            string rid = rcmd.substr(2);
                            Runway *rwy = getRunway(rid, r1, r2, r3);
                            if (!rwy) {
                                cout << "[ERROR] Unknown runway: " << rid << ". Try again: ";
                            } else if (rwy->getIsOccupied()) {
                                cout << "[ERROR] " << rid << " is occupied. Choose another: ";
                            } else {
                                int cycles = (current.getRequestType() == "takeoff") ? 2 : 1;
                                rwy->assignAircraft(current.getId(), current.getX(), current.getY(), cycles);
                                cout << "[APPROVED] " << current.getCallsign()
                                     << " assigned to " << rid
                                     << " for " << current.getRequestType() << "." << endl;
                                log.push_back({current.getCallsign(), current.getRequestType(), "APPROVED", rid});
                                handled = true;
                                assigned = true;
                            }
                        } else {
                            cout << "[UNKNOWN] Use: a R01 | a R02 | a R03 | d : ";
                        }
                    }
                }
            }

            else {
                cout << "[UNKNOWN COMMAND] Use: a | d | clear R01/R02/R03" << endl;
            }
        }
    }

    printDisplay(r1, r2, r3);
    cout << "All flights processed." << endl;
    printLog(log);

    return 0;
}
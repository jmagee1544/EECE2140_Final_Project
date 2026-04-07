#ifndef AIRCRAFT_H
#define AIRCRAFT_H
#include <string>
using namespace std;

class Aircraft
{
private:
    std::string id;          // Unique flight identifier
    std::string calsign;     // Aircraft callsign
    std::string status;      // Current flight status (e.g., airborne, landed)
    std::string requestType; // Type of ATC request associated with this aircraft
    double x;                // Current X coordinate
    double y;                // Current Y coordinate
    double altitude;         // Current altitude in feet
    double speed;            // Current speed in knots
    int heading;             // Current heading in degrees

public:
    // Constructs an Aircraft with all flight parameters including identity, position, and request type
    Aircraft(std::string id, std::string calsign, std::string status, double x, double y, double altitude, double speed, int heading, std::string requestType);

    // Returns the unique flight identifier
    std::string getFlightId() const;

    // Returns the aircraft callsign
    std::string getCalsign() const;

    // Returns the current flight status
    std::string getStatus() const;

    // Returns the aircraft's current X coordinate
    double getX() const;

    // Returns the aircraft's current Y coordinate
    double getY() const;

    // Returns the aircraft's current altitude in feet
    double getAltitude() const;

    // Returns the aircraft's current speed in knots
    double getSpeed() const;

    // Returns the aircraft's current heading in degrees
    int getHeading() const;

    // Returns the type of ATC request associated with this aircraft
    std::string getRequestType() const;

    // Updates the aircraft's positional data including coordinates, altitude, speed, and heading
    void updatePosition(double x, double y, double altitude, double speed, int heading);

    // Updates the aircraft's current flight status
    void updateStatus(std::string status);

    // Prints a formatted summary of all aircraft flight information to standard output
    void displayInfo() const;
};

#endif // AIRCRAFT_H
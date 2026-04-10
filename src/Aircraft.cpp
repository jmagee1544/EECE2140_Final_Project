#include "Aircraft.h"
#include <iostream>
using namespace std;

// Constructs an Aircraft with all flight parameters including identity, position, and request type
Aircraft::Aircraft(string id, string callsign, string status, double x, double y, double altitude, double speed, int heading, string requestType)
    : id(id), callsign(callsign), status(status), x(x), y(y), altitude(altitude), speed(speed), heading(heading), requestType(requestType)
{
    if (altitude < 0) altitude = 0;
    if (speed < 0) speed = 0;
    if (heading < 0 || heading > 360) heading = 0;
}


// Returns the aircraft Callsign
string Aircraft::getCallsign() const
{
    return callsign;
}

// Returns the current flight status (e.g., airborne, landed)
string Aircraft::getStatus() const
{
    return status;
}

// Returns the aircraft's current X coordinate
double Aircraft::getX() const
{
    return x;
}

// Returns the aircraft's current Y coordinate
double Aircraft::getY() const
{
    return y;
}

// Returns the aircraft's current altitude in feet
double Aircraft::getAltitude() const
{
    return altitude;
}

// Returns the aircraft's current speed in knots
double Aircraft::getSpeed() const
{
    return speed;
}

// Returns the aircraft's current heading in degrees
int Aircraft::getHeading() const
{
    return heading;
}

// Returns the type of ATC request associated with this aircraft
string Aircraft::getRequestType() const
{
    return requestType;
}

// Returns the unique identifier of this aircraft
string Aircraft::getId() const {
    return id;
}
// Updates the aircraft's positional data including coordinates, altitude, speed, and heading
void Aircraft::updatePosition(double x, double y, double altitude, double speed, int heading)
{
    this->x = x;
    this->y = y;
    this->altitude = altitude;
    this->speed = speed;
    this->heading = heading;
}

// Updates the aircraft's current flight status
void Aircraft::updateStatus(string status)
{
    this->status = status;
}

// Prints a formatted summary of all aircraft flight information to standard output
void Aircraft::displayInfo() const
{
    cout << "Flight ID: " << id << ", Callsign: " << callsign << ", Status: " << status
         << ", Position: (" << x << ", " << y << "), Altitude: " << altitude
         << " ft, Speed: " << speed << " knots, Heading: " << heading << " degrees" << endl;
}
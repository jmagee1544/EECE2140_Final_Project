#include "Runway.h"
#include <iostream>
#include <cmath>
using namespace std;

const double Runway::MIN_SEPARATION = 5.0;

// Constructs a Runway with the given ID, length, and orientation, initializing it as unoccupied
Runway::Runway(string runwayId, int length, int orientation)
    : runwayId(runwayId), length(length), orientation(orientation), isOccupied(false), assignedAircraftId(""), lastX(0.0), lastY(0.0)
{
}

// Returns the unique runway identifier
string Runway::getRunwayId() const
{
    return runwayId;
}

// Returns the ID of the aircraft currently assigned to this runway, or empty if none
string Runway::getAssignedAircraftId() const
{
    return assignedAircraftId;
}

// Returns the unique identifier of this runway
string Runway::getId() const 
{
    return runwayId;
}


// Returns the runway length in meters
int Runway::getLength() const
{
    return length;
}

// Returns the runway orientation in degrees
int Runway::getOrientation() const
{
    return orientation;
}

// Returns true if the runway is currently occupied by an aircraft, false otherwise
bool Runway::getIsOccupied() const
{
    return isOccupied;
}

// Checks if incoming aircraft is safely separated from the last assigned aircraft
// Constant time distance check between two positions
bool Runway::checkSpacing(double incomingX, double incomingY) const
{
    if (!isOccupied) return true;
    double dx = incomingX - lastX;
    double dy = incomingY - lastY;
    return sqrt(dx * dx + dy * dy) >= MIN_SEPARATION;
}

// Assigns an aircraft to this runway if available and spacing requirements are met
bool Runway::assignAircraft(string aircraftId, double x, double y)
{
    if (!isOccupied && checkSpacing(x, y))
    {
        assignedAircraftId = aircraftId;
        lastX = x;
        lastY = y;
        isOccupied = true;
        return true;
    }
    return false;
}

// Clears the runway by removing the assigned aircraft and marking it as available
void Runway::clearRunway()
{
    assignedAircraftId = "";
    isOccupied = false;
}

// Prints a formatted summary of the runway's status, including occupancy and assigned aircraft if applicable
void Runway::displayInfo() const
{
    cout << "Runway ID: " << runwayId << ", Length: " << length << "m, Orientation: " << orientation << " degrees, ";
    if (isOccupied)
    {
        cout << "Occupied by Aircraft ID: " << assignedAircraftId;
    }
    else
    {
        cout << "Available";
    }
    cout << endl;
}
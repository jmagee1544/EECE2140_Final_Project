#include "Runway.h"
#include <iostream>
using namespace std;

// Constructs a Runway with the given ID, length, and orientation, initializing it as unoccupied
Runway::Runway(string runwayId, int length, int orientation)
    : runwayId(runwayId), length(length), orientation(orientation), isOccupied(false), assignedAircraftId("")
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

// Assigns an aircraft to this runway if it is available; returns true on success, false if already occupied
bool Runway::assignAircraft(string aircraftId)
{
    if (!isOccupied)
    {
        assignedAircraftId = aircraftId;
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
#include "Runway.h"
#include <iostream>
using namespace std;

Runway::Runway(string runwayId, int length, int orientation)
    : runwayId(runwayId), length(length), orientation(orientation), isOccupied(false), assignedAircraftId("")
{
}

string Runway::getRunwayId() const
{
    return runwayId;
}

string Runway::getAssignedAircraftId() const
{
    return assignedAircraftId;
}

int Runway::getLength() const
{
    return length;
}

int Runway::getOrientation() const
{
    return orientation;
}

bool Runway::getIsOccupied() const
{
    return isOccupied;
}

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

void Runway::clearRunway()
{
    assignedAircraftId = "";
    isOccupied = false;
}

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

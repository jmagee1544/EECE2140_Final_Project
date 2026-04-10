#include "Runway.h"
#include <iostream>
#include <cmath>
using namespace std;

const double Runway::MIN_SEPARATION = 5.0;

Runway::Runway(string runwayId, int length, int orientation)
    : runwayId(runwayId), length(length), orientation(orientation),
      isOccupied(false), assignedAircraftId(""), lastX(0.0), lastY(0.0), clearCountdown(0)
{
}

// O(1) getters — direct member access
string Runway::getRunwayId() const { return runwayId; }
string Runway::getAssignedAircraftId() const { return assignedAircraftId; }
string Runway::getId() const { return runwayId; }
int Runway::getLength() const { return length; }
int Runway::getOrientation() const { return orientation; }
bool Runway::getIsOccupied() const { return isOccupied; }

// Returns true once the countdown has reached zero — runway is ready to be manually cleared
bool Runway::isClearable() const
{
    return isOccupied && clearCountdown <= 0;
}

// Decrements the cycle countdown each time a new flight is processed from the queue
// O(1) — constant time counter decrement
void Runway::tick()
{
    if (isOccupied && clearCountdown > 0)
        clearCountdown--;
}

// Assigns an aircraft and locks the runway for the given number of flight cycles
// O(1) — constant time assignment and state update
bool Runway::assignAircraft(string aircraftId, double x, double y, int cycles)
{
    if (!isOccupied && checkSpacing(x, y)) {
        assignedAircraftId = aircraftId;
        lastX = x;
        lastY = y;
        isOccupied = true;
        clearCountdown = cycles;
        return true;
    }
    return false;
}

// O(1) — constant time distance check between two positions
bool Runway::checkSpacing(double incomingX, double incomingY) const
{
    if (!isOccupied) return true;
    double dx = incomingX - lastX;
    double dy = incomingY - lastY;
    return sqrt(dx * dx + dy * dy) >= MIN_SEPARATION;
}

// O(1) — constant time state reset
void Runway::clearRunway()
{
    assignedAircraftId = "";
    isOccupied = false;
    clearCountdown = 0;
}

void Runway::displayInfo() const
{
    cout << "Runway ID: " << runwayId << ", Length: " << length
         << "m, Orientation: " << orientation << " degrees, ";
    if (isOccupied)
        cout << "Occupied by: " << assignedAircraftId
             << " (cycles remaining: " << clearCountdown << ")";
    else
        cout << "Available";
    cout << endl;
}
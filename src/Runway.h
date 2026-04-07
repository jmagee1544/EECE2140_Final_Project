#ifndef RUNWAY_H
#define RUNWAY_H

#include <string>
#include "AirTrafficEntity.h"
using namespace std;

class Runway : public AirTrafficEntity {
private:
    string runwayId;                // Unique identifier for the runway
    string assignedAircraftId;      // ID of the aircraft currently assigned to this runway
    int length;                     // Length of the runway in meters
    int orientation;                // Runway orientation in degrees
    bool isOccupied;                // True if the runway is currently in use

public:
    // Constructs a Runway with the given ID, length, and orientation
    Runway(string runwayId, int length, int orientation);

    // Unique identifier of this runway
    string getId() const override; 

    // Returns the unique runway identifier
    string getRunwayId() const;

    // Returns the ID of the aircraft currently assigned to this runway
    string getAssignedAircraftId() const;

    // Returns the runway length in meters
    int getLength() const;

    // Returns the runway orientation in degrees
    int getOrientation() const;

    // Returns true if the runway is currently occupied, false otherwise
    bool getIsOccupied() const;

    // Assigns an aircraft to this runway if available; returns true on success, false if occupied
    bool assignAircraft(string aircraftId);

    // Clears the runway, removing the assigned aircraft and marking it as available
    void clearRunway();

    // Prints a formatted summary of the runway's current status to standard output
    void displayInfo() const override;
};
#endif // Runway.h
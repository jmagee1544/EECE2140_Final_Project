#ifndef RUNWAY_H
#define RUNWAY_H

#include <string>
#include "AirTrafficEntity.h"

class Runway : public AirTrafficEntity {
private:
    std::string runwayId;                // Unique identifier for the runway
    std::string assignedAircraftId;      // ID of the aircraft currently assigned to this runway
    int length;                     // Length of the runway in meters
    int orientation;                // Runway orientation in degrees
    bool isOccupied;                // True if the runway is currently in use
    double lastX;                   // X position of last assigned aircraft
    double lastY;                   // Y position of last assigned aircraft
    static const double MIN_SEPARATION;
    bool checkSpacing(double incomingX, double incomingY) const;

public:
    // Constructs a Runway with the given ID, length, and orientation
    Runway(std::string runwayId, int length, int orientation);

    // Unique identifier of this runway
    std::string getId() const override; 

    // Returns the unique runway identifier
    std::string getRunwayId() const;

    // Returns the ID of the aircraft currently assigned to this runway
    std::string getAssignedAircraftId() const;

    // Returns the runway length in meters
    int getLength() const;

    // Returns the runway orientation in degrees
    int getOrientation() const;

    // Returns true if the runway is currently occupied, false otherwise
    bool getIsOccupied() const;

    // Assigns an aircraft to this runway if available; returns true on success, false if occupied
    bool assignAircraft(std::string aircraftId, double x, double y);

    // Clears the runway, removing the assigned aircraft and marking it as available
    void clearRunway();

    // Prints a formatted summary of the runway's current status to standard output
    void displayInfo() const override;

    // Destructor
    virtual ~Runway() {}
};
#endif // Runway.h
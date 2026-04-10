#ifndef RUNWAY_H
#define RUNWAY_H

#include <string>
#include "AirTrafficEntity.h"

class Runway : public AirTrafficEntity {
private:
    std::string runwayId;
    std::string assignedAircraftId;
    int length;
    int orientation;
    bool isOccupied;
    double lastX;
    double lastY;
    int clearCountdown;   // Cycles remaining before runway can be cleared
    static const double MIN_SEPARATION;
    bool checkSpacing(double incomingX, double incomingY) const;

public:
    Runway(std::string runwayId, int length, int orientation);

    std::string getId() const override;
    std::string getRunwayId() const;
    std::string getAssignedAircraftId() const;
    int getLength() const;
    int getOrientation() const;
    bool getIsOccupied() const;

    // Returns true if the runway has served enough cycles and can be manually cleared
    bool isClearable() const;

    // Decrements the clearCountdown each flight cycle
    void tick();

    // Assigns aircraft with a cycle lock (1 for landing, 2 for takeoff)
    bool assignAircraft(std::string aircraftId, double x, double y, int cycles);

    void clearRunway();
    void displayInfo() const override;

    // No dynamic memory — compiler-generated copy/move/assignment are sufficient
    virtual ~Runway() {}
};

#endif
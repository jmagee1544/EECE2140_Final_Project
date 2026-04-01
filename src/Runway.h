#ifndef RUNWAY_H
#define RUNWAY_H
#include <string>
using namespace std;

class Runway {
private:
    string runwayId;
    string assignedAircraftId;
    int length;
    int orientation;
    bool isOccupied;
public:
    Runway(string runwayId, int length, int orientation);
    string getRunwayId() const;
    string getAssignedAircraftId() const;
    int getLength() const;
    int getOrientation() const;
    bool getIsOccupied() const;
    bool assignAircraft(string aircraftId);
    void clearRunway();
    void displayInfo() const;
};
#endif // Runway.h
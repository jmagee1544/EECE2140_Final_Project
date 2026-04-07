#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <string>
#include "AirTrafficEntity.h"
using namespace std;

class Aircraft : public AirTrafficEntity {
private:
    string id;
    string calsign;
    string status;
    string requestType;
    double x;
    double y;
    double altitude;
    double speed;
    int heading;

public:
    Aircraft(string id, string calsign, string status,
             double x, double y, double altitude,
             double speed, int heading, string requestType);

    // override from base class
    string getId() const override;

    // existing getters
    string getFlightId() const;
    string getCalsign() const;
    string getStatus() const;
    double getX() const;
    double getY() const;
    double getAltitude() const;
    double getSpeed() const;
    int getHeading() const;
    string getRequestType() const;

    // setters / updates
    void updatePosition(double x, double y, double altitude, double speed, int heading);
    void updateStatus(string status);

    // override display
    void displayInfo() const override;
};

#endif
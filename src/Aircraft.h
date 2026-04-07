#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <string>
#include "AirTrafficEntity.h"

class Aircraft : public AirTrafficEntity {
private:
    std::string id;
    std::string callsign;
    std::string status;
    std::string requestType;
    double x;
    double y;
    double altitude;
    double speed;
    int heading;

public:
    Aircraft(std::string id, std::string callsign, std::string status,
             double x, double y, double altitude,
             double speed, int heading, std::string requestType);

    // override from base class
    std::string getId() const override;

    // existing getters
    std::string getcallsign() const;
    std::string getStatus() const;
    double getX() const;
    double getY() const;
    double getAltitude() const;
    double getSpeed() const;
    int getHeading() const;
    std::string getRequestType() const;

    // setters / updates
    void updatePosition(double x, double y, double altitude, double speed, int heading);
    void updateStatus(std::string status);

    // override display
    void displayInfo() const override;

    // Destructor
    virtual ~Aircraft() {}
};

#endif
#ifndef AIRCRAFT_H
#define AIRCRAFT_H
#include <string>
using namespace std;

class Aircraft
{
private:
    std::string id;
    std::string calsign;
    std::string status;
    std::string requestType;
    double x;
    double y;
    double altitude;
    double speed;
    int heading;
    

public:
    Aircraft(std::string id, std::string calsign, std::string status, double x, double y, double altitude, double speed, int heading, std::string requestType);
    std::string getFlightId() const;
    std::string getCalsign() const;
    std::string getStatus() const;
    double getX() const;
    double getY() const;
    double getAltitude() const;
    double getSpeed() const;
    int getHeading() const;
    std::string getRequestType() const;
    void updatePosition(double x, double y, double altitude, double speed, int heading);
    void updateStatus(std::string status);
    void displayInfo() const;
};

#endif // AIRCRAFT_H
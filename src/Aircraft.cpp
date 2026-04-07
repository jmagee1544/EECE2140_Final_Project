#include "Aircraft.h"
#include <iostream>
using namespace std;

Aircraft::Aircraft(string id, string calsign, string status, double x, double y, double altitude, double speed, int heading, string requestType)
    : id(id), calsign(calsign), status(status), x(x), y(y), altitude(altitude), speed(speed), heading(heading), requestType(requestType)
{
}

string Aircraft::getFlightId() const
{
    return id;
}

string Aircraft::getCalsign() const
{
    return calsign;
}

string Aircraft::getStatus() const
{
    return status;
}

double Aircraft::getX() const
{
    return x;
}

double Aircraft::getY() const
{
    return y;
}

double Aircraft::getAltitude() const
{
    return altitude;
}

double Aircraft::getSpeed() const
{
    return speed;
}

int Aircraft::getHeading() const
{
    return heading;
}

string Aircraft::getRequestType() const
{
    return requestType;
}

void Aircraft::updatePosition(double x, double y, double altitude, double speed, int heading)
{
    this->x = x;
    this->y = y;
    this->altitude = altitude;
    this->speed = speed;
    this->heading = heading;
}

void Aircraft::updateStatus(string status)
{
    this->status = status;
}

void Aircraft::displayInfo() const
{
    cout << "Flight ID: " << id << ", Calsign: " << calsign << ", Status: " << status
         << ", Position: (" << x << ", " << y << "), Altitude: " << altitude
         << " ft, Speed: " << speed << " knots, Heading: " << heading << " degrees" << endl;
}


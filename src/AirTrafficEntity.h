#ifndef AIRTRAFFICENTITY_H
#define AIRTRAFFICENTITY_H

#include <string>
using namespace std;

class AirTrafficEntity {
public:
    virtual string getId() const = 0;
    virtual void displayInfo() const = 0;
    virtual ~AirTrafficEntity() {}
};

#endif
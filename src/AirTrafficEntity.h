#ifndef AIRTRAFFICENTITY_H
#define AIRTRAFFICENTITY_H
#include <string>

// Abstract base class for all entities in the ATC system
class AirTrafficEntity
{
public:
    // Returns the unique identifier of this entity
    virtual std::string getId() const = 0;

    // Prints a formatted summary of this entity's current status to standard output
    virtual void displayInfo() const = 0;

    // Virtual destructor to ensure proper cleanup of derived class objects
    virtual ~AirTrafficEntity() {}
};

#endif
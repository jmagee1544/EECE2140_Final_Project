#include "Aircraft.h"
#include "Runway.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int main()
{
    // Create some aircraft
    Aircraft a1("A001", "Delta 123", "En Route", 40.7128, -74.0060, 30000, 500, 90);
    Aircraft a2("A002", "United 456", "En Route", 34.0522, -118.2437, 32000, 550, 270);
    Aircraft a3("A003", "American 789", "En Route", 41.8781, -87.6298, 28000, 480, 180);

    // Create some runways
    Runway r1("R001", 4000, 90);
    Runway r2("R002", 3500, 270);

    // Display initial information
    cout << "Initial Aircraft Information:" << endl;
    a1.displayInfo();
    a2.displayInfo();
    a3.displayInfo();

    cout << "\nInitial Runway Information:" << endl;
    r1.displayInfo();
    r2.displayInfo();

    // Assign aircraft to runways
    cout << "\nAssigning Aircraft to Runways..." << endl;
    if (r1.assignAircraft(a1.getFlightId()))
    {
        cout << "Assigned " << a1.getCalsign() << " to " << r1.getRunwayId() << endl;
    }
    else
    {
        cout << "Failed to assign " << a1.getCalsign() << " to" << r1.getRunwayId() << endl;
    }
    if (r2.assignAircraft(a2.getFlightId()))
    {
        cout << "Assigned " << a2.getCalsign() << " to " << r2.getRunwayId() << endl;
    }
    else
    {
        cout << "Failed to assign " << a2.getCalsign() << " to " << r2.getRunwayId() << endl;
    }
    return 0;
}

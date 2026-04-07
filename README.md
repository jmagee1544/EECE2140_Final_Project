# EECE 2140 Final Project
**Project Name:** *Air Traffic Control (ATC) Mini-System*\
**Team Members:** *Parker Higgins, Jack Magee, Kian Yik Hin Chan*

## Project Overview

The Air-Traffic Control (ATC) Mini-System is a simplified C++ simulation that models core air-traffic control operations. Using data from a CSV file, the system tracks aircraft in real-time and utilizes algorithms to manage runway assignments, enforce safety constraints, and generate alerts when violations occur. A controller is used to assign aircraft to available runways for landing or takeoff.

This project demonstrates object-oriented programming concepts such as encapsulation, inheritance, and polymorphism, while also applying data structures such as vectors and queues in a practical and systematic simulation. It illustrates how real-world ATC systems ensure safe and efficient aircraft movement in a collaborative development environment.

## Main Functionalities

* **Live Aircraft Tracking**\
Monitors the real-time state information (position, altitude, speed, heading, and status) for all active aircraft.

* **Runway Assignment**\
Allows the controller to assign aircraft to available runways for landing or takeoff, while ensuring safety constraints are met (ie, spacing conditions).

* **Runway Management**\
Tracks runway occupancy. Marks a runway as free once an aircraft has departed or landed.

* **Interactive Command System**
Supports controller commands such as assigning aircraft to a runway, denying a request, and viewing runway status.

* **Conflict Detection**\
Identifies and reports unsafe conditions when separation requirements are violated. Ensures that an incoming aircraft meets the minimum safe separation requirements before runway assignment is granted.

* **Information Display**\
Outputs detailed aircraft and runway status information for monitoring and simulation.
    * Aircraft: Flight ID, calsign, position, altitude, speed, heading, status, request type
    * Runway: Runway ID, occupancy status, assigned aircraft

## Object-Oriented Programming (OOP) Design Summary
The system follows an object-oriented modular design, abstraction, inheritance, and polymorphism to ensure scalability and maintainability. The base class `AirTrafficEntity` defines common behaviors shared by all other air traffic system objects. The two inherited classes, `Aircraft` and `Runway`, provide separate implementations of shared virtual functions.

Polymorphism is demonstrated in the main simulation by storing `Runway` and `Aircraft` objects as `AirTrafficEntity*` pointers and calling overridden methods such as `displayInfo()` and `getId()` through the base-class interface.

### 1. AirTrafficEntity Class

* Serves as an abstract base class for all major air traffic system entities.
* Defines a shared interface for derived classes such as `Aircraft` and `Runway`.
* Demonstrates abstraction and polymorphism in the project design.

Public Members:
| Attribute/Method  | Data Type | Description                                               |
|:----------------- |:--------- |:--------------------------------------------------------- |
| getId()           | string    | Virtual function that returns the unique ID of the entity |
| displayInfo()     | void      | Virtual function that displays the entity’s information   |

### 2. Aircraft Class

* Represents an individual aircraft in the ATC system. Inherits from `AirTrafficEntity`.
* Stores the attributes of individual aircraft such as position, altitude, speed, and status.
* Includes methods for updating position and displaying aircraft data.

Private Members:
| Attrubute/Method  | Data Type     | Description                                           |
|:----------------- |:------------- |:----------------------------------------------------- |
| id                | string        | Unique aircraft identifier                            |
| calsign           | string        | Airline callsign                                      |
| status            | string        | Status of aircraft (e.g., en route, landing, holding) |
| requestType       | string        | Specifies the type of request (landing or takeoff)    |
| x                 | double        | Aircraft x-coordinate position                        |
| y                 | double        | Aircraft y-coordinate position                        |
| altitude          | double        | Altitude (in feet)                                    |
| speed             | double        | Speed (in knots)                                      |
| heading           | int           | Heading degrees (0-360°)                              |

Public Members:
| Attrubute/Method  | Data Type     | Description                               |
|:----------------- |:------------- |:----------------------------------------- |
| getId()           | string        | Returns the aircraft's unique ID          |
| getCalsign()      | string        | Returns aircraft callsign                 |
| getStatus()       | string        | Returns aircraft's current status         |
| getX()            | double        | Returns x-coordinate position             |
| getY()            | double        | Returns y-coordinate position             |
| getAltitude()     | double        | Returns altitude (in feet)                |
| getSpeed()        | double        | Returns speed (in knots)                  |
| getHeading()      | int           | Returns heading (0-360°)                  |
| getRequestType()  | int           | Returns landing/takeoff request type      |
| updatePosition()  | void          | Updates x and y coordinate, and altitude  |
| updateStatus()    | void          | Updates aircraft status                   |
| displayInfo()     | void          | Prints all aircraft information           |

### 3. Runway Class

* Represents airport runways and manages their availability.
* Handles aircraft assignment and enforces spacing constraints through internal validation.

Private Members:
| Attrubute/Method  | Data Type     | Description                                                                           |
|:----------------- |:------------- |:------------------------------------------------------------------------------------- |
| runwayID          | string        | Unique runway identifier                                                              |
| assignedAircraftId| string        | Flight ID of aircraft currently assigned to runway                                    |
| length            | int           | Length of runway (in feet)                                                            |
| orientation       | int           | Runway heading/orientation (in degrees)                                               |
| isOccupied        | bool          | Checks if runway is currently in use                                                  |


Public Members:
| Attrubute/Method          | Data Type     | Description                                                                       |
|:------------------------- |:------------- |:--------------------------------------------------------------------------------- |
| getId()                   | string        | Returns runway unique ID                                                          |
| getRunwayId()             | string        | Returns runway ID                                                                 |
| getAssignedAircraftId()   | string        | Returns assigned aircraft ID                                                      |
| getLength()               | int           | Returns runway length                                                             |
| getOrientation()          | int           | Returns runway orienation                                                         |
| getIsAvailable()          | bool          | Returns runway occupancy                                                          |
| assignAircraft()          | bool          | Calls checkSpacing()— Assigns aircraft if requirements are met, rejects if not    |
| clearRunway()             | void          | Clears any assigned aircraft and marks runway as unoccupied                       |
| displayStatus()           | void          | Prints runway ID, occupancy, and its assigned aircraft                            |

### 4. Main Simulation Driver (main.cpp)

* The `main.cpp` file acts as the controller interface for the simulation.
* Loads aircraft data from the CSV file into a queue.
* Processes aircraft requests one at a time.
* Accepts user commands for runway assignment, denial, and status checks.
* Demonstrates polymorphism by interacting with `Aircraft` and `Runway` objects through `AirTrafficEntity` pointers.

## Tools and Technologies
* **Programming Language:** C++ (core system implementation using OOP principles)
* **IDE / Editor:** Visual Studio Code (for code editing and debugging)
* **Version Control:** Git / GitHub (track changes, branching, repository hosting)
* **Build System:** g++ (C++ compiler)
* **Testing Framwork:** Manual / Custom Test Cases
* **Documentation:** Markdown / PDF
* **Project Management:** GitHub Issues & Projects

## Folder Structure

```
EECE2140_AirTrafficControl/
│
├── README.md                               # Project documentation
├── Makefile                                # Build instructions
│
├── docs/                                   # Documentation files 
│   └── System_Design_Overview.pdf
|
├── pseudocode/                             # Pseudocode and design
│   ├── AirTrafficControl_Pseudocode.pdf
│   └── AirTrafficControl_Pseudocode.tex
│
├── src/                                    # Source files for implementation
│   ├── Aircraft.cpp
│   ├── Runway.cpp
│   └── main.cpp
│
├── include/                                # Header files
│   ├── Aircraft.h
│   ├── Runway.h
│   └── ATC.h
│
├── data/
│   └── BOS_flights.csv
│
└── .gitignore                              # For excluding build files
```

## Project Goals

#### Personal/Individual Objectives
* Build project management and collaboration skills
* Gain coding experience for real-world situations
* Improve proficiency in C++ and object-oriented design


#### Team Objectives
* Deliver a fully functional and integrated ATC Mini-System by the project deadline
* Ensure seamless integration between well-defined interfaces and modules
* Maintain clean, readable, and well-documented code throughout the project
* Collaborate effectively using version control workflows through GitHub
* Produce comprehensive project documentation for final submission


## GitHub Repository Purpose

The GitHub repository serves as the central hub for:
* **Project Management:** Tracking tasks and progress, identifying any issues
* **Version Control:** Managing code changes and revision history using Git
* **Collaboration:** Enabling a central hub for team contributions through branches and pull requests
* **Documentation:** Storing all project-related materials and deliverables
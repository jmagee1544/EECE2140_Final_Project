# EECE 2140 Final Project
**Project Name:** *Air Traffic Control (ATC) Mini-System*\
**Team Members:** *Parker Higgins, Jack Magee, Kian Yik Hin Chan*

## Project Overview

The Air-Traffic Control (ATC) Mini-System is a simplified C++ simulation that models core air-traffic control operations. The system tracks aircraft in real time and uses algorithms to manage runway assignments, enforce safety constraints, and generate alerts when violations occur.

This project demonstrates the practical application of object-oriented programming and other data structures, along with key system design principles in a collaborative development environment. It illustrates how real-world ATC systems ensure safe and efficient aircraft movement.

## Main Functionalities

* **Live Aircraft Tracking**\
Monitors the real-time state information (position, altitude, speed, heading, and status) for all active aircraft.

* **Runway Assignment**\
Assigns aircraft to available runways while ensuring safety constraints are met (ie, spacing conditions).

* **Runway Management**\
Tracks runway occupancy. Marks a runway as free once an aircraft has departed or landed.

* **Verification of Spacing Requirements**\
Ensures that an incoming aircraft meets the minimum safe separation requirements before runway assignment is granted.

* **Conflict Detection**\
Identifies and reports unsafe conditions when separation requirements are violated.

* **Information Display**\
Outputs detailed aircraft and runway status information for monitoring and safety checking.
    * Aircraft: Flight ID, position, altitude, speed, heading, status
    * Runway: Runway ID, occupancy status, assigned aircraft

## Object-Oriented Programming (OOP) Design Summary
The system follows an object-oriented modular design with three primary classes to ensure scalability and maintainability:

### 1. Aircraft Class

* Stores the attributes of individual aircraft such as position, altitude, speed, and status.
* Includes methods for updating position and displaying aircraft data.

Private Members:
| Attrubute/Method  | Data Type     | Description                                           |
|:----------------- |:------------- |:----------------------------------------------------- |
| flightID          | string        | Unique aircraft identifier                            |
| callsign          | string        | Airline callsign                                      |
| x                 | double        | Aircraft x-coordinate position                        |
| y                 | double        | Aircraft y-coordinate position                        |
| altitude          | double        | Altitude (in feet)                                    |
| speed             | double        | Speed (in knots)                                      |
| heading           | int           | Heading degrees (0-360°)                              |
| status            | string        | Status of aircraft (e.g., en route, landing, holding) |

Public Members:
| Attrubute/Method  | Data Type     | Description                               |
|:----------------- |:------------- |:----------------------------------------- |
| getFlightID()     | string        | Returns flight ID                         |
| getX()            | double        | Returns x-coordinate position             |
| getY()            | double        | Returns y-coordinate position             |
| getAltitude()     | double        | Returns altitude (in feet)                |
| getSpeed()        | double        | Returns speed (in knots)                  |
| getHeading()      | int           | Returns heading (0-360°)                  |
| getStatus()       | string        | Returns aircraft's current status         |
| setStatus()       | void          | Updates aircraft status                   |
| updatePosition()  | void          | Updates x and y coordinate, and altitude  |
| displayInfo()     | void          | Prints all aircraft information           |

### 2. Runway Class

* Represents airport runways and manages their availability.
* Handles aircraft assignment and enforces spacing constraints through internal validation.

Private Members:
| Attrubute/Method  | Data Type     | Description                                                                           |
|:----------------- |:------------- |:------------------------------------------------------------------------------------- |
| runwayID          | string        | Unique runway identifier                                                              |
| length            | int           | Length of runway (in feet)                                                            |
| isOccupied        | bool          | Checks if runway is currently in use                                                  |
| assignedAircraft  | string        | Flight ID of aircraft currently assigned to runway                                    |
| orientation       | int           | Runway heading/orientation (in degrees)                                               |
| checkSpacing()    | bool          | Checks if the incoming aircraft meets the spacing requirements from other aircrafts   |


Public Members:
| Attrubute/Method  | Data Type     | Description                                                                       |
|:----------------- |:------------- |:--------------------------------------------------------------------------------- |
| getRunwayID()     | string        | Returns runway ID                                                                 |
| isAvailable()     | bool          | Returns runway occupancy                                                          |
| assignAircraft()  | bool          | Calls checkSpacing()— Assigns aircraft if requirements are met, rejects if not    |
| clearRunway()     | void          | Clears any assigned aircraft and marks runway as unoccupied                       |
| displayStatus()   | void          | Prints runway ID, occupancy, and its assigned aircraft                            |

### 3. Air-Traffic-Controller (ATC) Class
* Acts as the central coordinator between Aircraft and Runway objects.
* Responsible for handling landing requests, delegating runway assignments, and ensuring system-wide consistency.

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
│   ├── ATC.cpp
│   └── main.cpp
│
├── include/                                # Header files
│   ├── Aircraft.h
│   ├── Runway.h
│   └── ATC.h
│
├── tests/                                  # Test cases
│   └── test_main.cpp
│
├── images/                                 # Project diagrams
│   └── system_diagram.png
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

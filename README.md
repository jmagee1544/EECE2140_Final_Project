# EECE 2140 Final Project
**Project Name:** *Air Traffic Control (ATC) Mini-System*\
**Team Members:** *Parker Higgins, Jack Magee, Kian Yik Hin Chan*

## Project Overview

The Air-Traffic Control (ATC) Mini-System is a simplified C++ simulation that models core air-traffic control operations. Using data from a CSV file, the system processes aircraft requests and manages runway assignments through an interactive controller interface. The system enforces operational constraints such as runway availability and cycle-based usage timing, while maintaining a structured log of controller actions throughout the session.

This project demonstrates object-oriented programming concepts such as encapsulation, inheritance, and polymorphism, while also applying data structures such as vectors and queues in a practical and systematic simulation. It illustrates how real-world ATC systems simulate key aspects of safe and efficient aircraft movement in a collaborative development environment.

## Main Functionalities

* **Flight Data Parsing**\
Reads flight data from a CSV file and converts each entry into an Aircraft object. Objects are stored in a queue using a first-in-first-out (FIFO) format to simulate the arrival of aircraft requests.

* **Cycle-Based Runway Assignment**\
Aircraft are assigned to one of three runways: `R01`, `R02`, `R03`. Each assignment locks the runway for a fixed number of processing cycles in the queue (2 cycles for takeoff, 1 cycle for landing). Runways cannot be cleared until their cycle count reaches zero.

* **Runway State Management**\
Tracks runway occupancy using a cycle-based system that simulate time progression. Runways remain occupied until they are manually cleared, while a runway becomes clearable after completing its required cycles.

* **Interactive Command System**
Provides a command-line interface (air-traffic controller) that responds to aircraft requests. Supports controller commands such as assigning/approving an aircraft, denying a request (re-queue), and clearing a runway. 
- `a` → approve aircraft  
- `d` → deny aircraft (re-queued to end of queue)  
- `a R01`, `a R02`, `a R03` → assign aircraft to a runway  
- `clear R01`, `clear R02`, `clear R03` → manually clear a runway  

* **Basic Spacing Validation**\
Performs a basic distance check between consecutive aircraft during runway assignment.

* **Session Logging**  
Records all controller actions (approvals, denials, and runway clears) and displays them at the end of the simulation.

* **Information Display**\
Outputs detailed aircraft and runway status information for monitoring and simulation.
    * Aircraft: callsign, ID, altitude, speed, request type
    * Runway: ID, occupancy status, remaining cycles

## Object-Oriented Programming (OOP) Design Summary
The system follows an object-oriented modular design, using abstraction, inheritance, and polymorphism to ensure scalability and maintainability. The base class `AirTrafficEntity` defines common behaviors shared by all other air traffic system objects. The two inherited classes, `Aircraft` and `Runway`, provide separate implementations of shared virtual functions.

Polymorphism is demonstrated in the main simulation by storing `Runway` and `Aircraft` objects as `AirTrafficEntity*` pointers and calling overridden methods such as `displayInfo()` and `getId()` through the base-class interface.

### 1. AirTrafficEntity Class

* Serves as an abstract base class for all major air traffic system entities.
* Defines a shared interface for derived classes such as `Aircraft` and `Runway`.
* Demonstrates abstraction and polymorphism in the project design.

Public Members:
| Attribute/Method  | Data Type | Description                           |
|:----------------- |:--------- |:------------------------------------- |
| getId()           | string    | Returns the unique ID of the entity   |
| displayInfo()     | void      | Displays the entity’s information     |

### 2. Aircraft Class

* Represents an individual aircraft in the ATC system. Inherits from `AirTrafficEntity`.
* Stores the attributes of individual aircraft such as position, altitude, speed, and status.
* Includes methods for updating position and displaying aircraft data.

Private Members:
| Attribute/Method  | Data Type     | Description                                           |
|:----------------- |:------------- |:----------------------------------------------------- |
| id                | string        | Unique aircraft identifier                            |
| callsign          | string        | Airline callsign                                      |
| status            | string        | Status of aircraft (e.g., en route, landing, holding) |
| requestType       | string        | Specifies the type of request (landing or takeoff)    |
| x, y              | double        | Aircraft coordinates                                  |
| altitude          | double        | Altitude (in feet)                                    |
| speed             | double        | Speed (in knots)                                      |
| heading           | int           | Heading direction (0-360°)                            |

Public Members:
| Attribute/Method  | Data Type     | Description                               |
|:----------------- |:------------- |:----------------------------------------- |
| getId()           | string        | Returns the aircraft's  ID                |
| getCallsign()     | string        | Returns aircraft callsign                 |
| getStatus()       | string        | Returns aircraft's current status         |
| getX(), getY()    | double        | Returns coordinate positions              |
| getAltitude()     | double        | Returns altitude (in feet)                |
| getSpeed()        | double        | Returns speed (in knots)                  |
| getHeading()      | int           | Returns heading (0-360°)                  |
| getRequestType()  | string        | Returns landing/takeoff request type      |
| updatePosition()  | void          | Updates x and y coordinate, and altitude  |
| updateStatus()    | void          | Updates aircraft status                   |
| displayInfo()     | void          | Prints all aircraft information           |

### 3. Runway Class

* Represents airport runways and manages their availability.
* Handles aircraft assignment and enforces spacing constraints through internal validation.

Private Members:
| Attribute/Method      | Data Type     | Description                                           |
|:--------------------- |:------------- |:----------------------------------------------------- |
| runwayId              | string        | Unique runway identifier                              |
| assignedAircraftId    | string        | Flight ID of aircraft currently assigned to runway    |
| length                | int           | Length of runway (in feet)                            |
| orientation           | int           | Runway heading/orientation (in degrees)               |
| isOccupied            | bool          | Checks if runway is currently in use                  |
| clearCountdown        | int           | Cycles remaining before runway can be cleared         |
| lastX, lastY          | double        | Previous aircraft coordinates                         |


Public Members:
| Attribute/Method          | Data Type     | Description                                                                       |
|:------------------------- |:------------- |:--------------------------------------------------------------------------------- |
| getId()                   | string        | Returns runway unique ID                                                          |
| getRunwayId()             | string        | Returns runway ID                                                                 |
| getAssignedAircraftId()   | string        | Returns assigned aircraft ID                                                      |
| getLength()               | int           | Returns runway length                                                             |
| getOrientation()          | int           | Returns runway orientation                                                        |
| getIsOccupied()           | bool          | Returns runway occupancy                                                          |
| isClearable()             | bool          | Checks if runway is ready to clear                                                |
| tick()                    | void          | Decrements cycle count after processing                                           |
| assignAircraft()          | bool          | Assigns aircraft and locks it to a runway for a number of cycles                  |
| clearRunway()             | void          | Clears any assigned aircraft and marks runway as unoccupied                       |
| displayInfo()             | void          | Prints runway ID, occupancy, and its assigned aircraft                            |

### 4. Main Simulation Driver (ATC.cpp)

* Acts as the controller interface for the simulation.
* Loads aircraft data from the CSV file into a queue.
* Processes aircraft requests sequentially
* Accepts user commands for runway assignment `a`, denial `d`, `clear`, and status checks.
* Demonstrates polymorphism by interacting with `Aircraft` and `Runway` objects through `AirTrafficEntity` pointers.

## Tools and Technologies
* **Programming Language:** C++ (core system implementation using OOP principles)
* **IDE / Editor:** Visual Studio Code (for code editing and debugging)
* **Version Control:** Git / GitHub (track changes, branching, repository hosting)
* **Build System:** g++ (C++ compiler)
* **Testing Framework:** Manual / Custom Test Cases
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
│   └── ATC.cpp
│
├── include/                                # Header files
│   ├── Aircraft.h
│   ├── Runway.h
│   └── AirTrafficEntity.h
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

## Compile and Run Commands

Compile:    `g++ ATC.cpp Aircraft.cpp Runway.cpp -o ATC`
Run:        `./ATC`

**Example Commands**
`a`
`a R01`
`clear R01`
`d`
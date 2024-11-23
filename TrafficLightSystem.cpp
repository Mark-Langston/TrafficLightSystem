/**
 * Implements the core functionality of the adaptive Traffic Light System.
 *
 * The `TrafficLightSystem` class is responsible for coordinating the behavior of
 * traffic lights, vehicle queues, error handling, and emergency event detection.
 * This file serves as the primary logic hub for managing traffic flow at a four-way
 * intersection.
 *
 * Key Responsibilities:
 * - Manage vehicle queues for each road using `QueueManager`.
 * - Control traffic light signals (red, yellow, green) for each road using `TrafficLight`.
 * - Detect and respond to emergency vehicles, prioritizing their passage by turning
 *   all signals red.
 * - Handle system errors using `ErrorHandler` and transition signals to blinking red
 *   during malfunctions.
 *
 */

#include "TrafficLightSystem.h"
#include <iostream>

// Constructor: Initializes the traffic light system with a max queue length
TrafficLightSystem::TrafficLightSystem(int maxQueueLength)
        : north("North"), south("South"), west("West"), east("East")
{
    queueLength = maxQueueLength;

    // Initialize queue managers for each road
    for (int i = 0; i < 4; ++i)
    {
        queues.push_back(QueueManager(maxQueueLength));
    }
}

// Handles a vehicle arriving at a specified road
void TrafficLightSystem::handleVehicle(Vehicle* vehicle, int road)
{
    int adjustedRoad = road - 1; // Adjust road index for array

    // Emergency vehicle handling
    if (vehicle->getType() == "Emergency Vehicle")
    {
        std::cout << "\n>>> Emergency vehicle detected on Road " << road << "! Turning all lights red.\n";
        eventFlag.setEmergencyDetected(true);
        setAllSignalsRed();
        return;
    }

    // Identify the corresponding light
    TrafficLight* light = nullptr;
    switch (road)
    {
        case 1: light = &north; break; // Road 1 -> North
        case 2: light = &south; break; // Road 2 -> South
        case 3: light = &west; break;  // Road 3 -> West
        case 4: light = &east; break;  // Road 4 -> East
        default:
            std::cout << "Invalid road number.\n";
            return;
    }

    // Handle normal vehicles
    // Ignore vehicles with a currently green light
    if (light->getSignalColor() == "Green")
    {
        std::cout << "Light is already green! Ignoring vehicle.";
    }
        // If the light isn't green, add it to a queue.
    else
    {
        std::cout << "\n>>> Adding " << vehicle->getType() << " to Road " << road << ".\n";
        queues[adjustedRoad].addVehicleToQueue(vehicle);
    }

    int currentQueueLength = queues[adjustedRoad].getQueueLength();
    std::cout << ">>> Queue length for Road " << road << ": " << currentQueueLength << " vehicles.\n";

    // Handle queue full
    if (queues[adjustedRoad].isQueueFull())
    {
        std::cout << ">>> Queue is full on Road " << road << "! Turning the light green to clear traffic.\n";
        handleFullQueue(road);
    }
}

// Handles actions when a queue becomes full for a specified road
void TrafficLightSystem::handleFullQueue(int road)
{
    if (road == 1 || road == 2) // North-South pair
    {
        changeSignalPair(1);
        queues[0].clearQueue();
        queues[1].clearQueue();
    }
    else if (road == 3 || road == 4) // West-East pair
    {
        changeSignalPair(2);
        queues[2].clearQueue();
        queues[3].clearQueue();
    }
}

// Sets all traffic lights to red, typically for emergencies
void TrafficLightSystem::setAllSignalsRed()
{
    std::cout << "Setting all signals to red...\n";
    north.changeSignal("Red", errorHandler, eventFlag);
    south.changeSignal("Red", errorHandler, eventFlag);
    west.changeSignal("Red", errorHandler, eventFlag);
    east.changeSignal("Red", errorHandler, eventFlag);
}

// Changes the traffic light signals for a specific road pair (e.g., North-South or West-East)
void TrafficLightSystem::changeSignalPair(int pair)
{
    errorHandler.generateError(); // Will create an error based on chance.

    if (pair == 1) // North-South signals
    {
        west.changeSignal("Red", errorHandler, eventFlag);
        east.changeSignal("Red", errorHandler, eventFlag);

        // North-South lights turn green
        north.changeSignal("Green", errorHandler, eventFlag);
        south.changeSignal("Green", errorHandler, eventFlag);

        // Clear queues for North and South roads
        queues[0].clearQueue(); // Road 1 (North)
        queues[1].clearQueue(); // Road 2 (South)
    }
    else if (pair == 2) // West-East signals
    {
        north.changeSignal("Red", errorHandler, eventFlag);
        south.changeSignal("Red", errorHandler, eventFlag);

        // West-East lights turn green
        west.changeSignal("Green", errorHandler, eventFlag);
        east.changeSignal("Green", errorHandler, eventFlag);

        // Clear queues for West and East roads
        queues[2].clearQueue(); // Road 3 (West)
        queues[3].clearQueue(); // Road 4 (East)
    }
    else
    {
        std::cout << "Invalid signal pair specified.\n";
    }
}

// Displays the current state of all traffic lights
void TrafficLightSystem::displayTrafficLightStates() const
{
    std::cout << "\n--- Current Traffic Light States ---\n";
    std::cout << "Road 1 (North): " << north.getSignalColor() << "\n";
    std::cout << "Road 2 (South): " << south.getSignalColor() << "\n";
    std::cout << "Road 3 (West): " << west.getSignalColor() << "\n";
    std::cout << "Road 4 (East): " << east.getSignalColor() << "\n";
}

// Displays the current length of all queues
void TrafficLightSystem::displayQueueLengths() const
{
    std::cout << "\n--- Current Queue Lengths ---\n";
    std::cout << "Road 1 (North): " << queues[0].getQueueLength() << " vehicles\n";
    std::cout << "Road 2 (South): " << queues[1].getQueueLength() << " vehicles\n";
    std::cout << "Road 3 (West): " << queues[2].getQueueLength() << " vehicles\n";
    std::cout << "Road 4 (East): " << queues[3].getQueueLength() << " vehicles\n";
}

// Handles a pedestrian crossing at a specified crosswalk
void TrafficLightSystem::handlePedestrian(char crosswalk)
{
    std::string direction;
    switch (crosswalk)
    {
        case 'N': direction = "North"; break;
        case 'S': direction = "South"; break;
        case 'E': direction = "East"; break;
        case 'W': direction = "West"; break;
        default: direction = "Unknown"; break;
    }

    if (direction != "Unknown")
    {
        std::cout << "Allowing pedestrians to cross at the " << direction << " crosswalk.\n";
        if (direction == "North" || direction == "South")
        {
            changeSignalPair(1); // Change North-South signals
        }
        else if (direction == "East" || direction == "West")
        {
            changeSignalPair(2); // Change East-West signals
        }
    }
    else
    {
        std::cout << "Invalid crosswalk direction.\n";
    }
}

// Public method to trigger an error in the system
void TrafficLightSystem::triggerError()
{
    errorHandler.generateError(); // Create an error based on chance.

    // Handle the case that an error was created.
    if (errorHandler.getErrorStatus())
    {
        std::cout << "Error triggered in the system!\n";
        setAllSignalsRed();
    }
    // Handle the case that an error failed to create, but lights are already in "Error" mode.
    if (!errorHandler.getErrorStatus() && north.getSignalColor() == "Blinking Red" && south.getSignalColor() == "Blinking Red" && west.getSignalColor() == "Blinking Red" && east.getSignalColor() == "Blinking Red")
    {
        std::cout << "Error has been fixed! Converting all lights to red.";
        setAllSignalsRed();
    }
    // Handle the case that an error failed to create.
    if (!errorHandler.getErrorStatus())
    {
        std::cout << "No error was generated. Systems are still operational.";
    }
}

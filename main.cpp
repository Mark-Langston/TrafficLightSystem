/**
 * Entry point for the Adaptive Traffic Light System simulation.
 *
 * This file serves as the user interface and main control loop for the Traffic Light System.
 * It handles user input, initializes the TrafficLightSystem, and processes actions like
 * vehicle arrivals, pedestrian crossings, and error simulations.
 *
 * Key Responsibilities:
 * - Initialize the TrafficLightSystem with a maximum queue length.
 * - Provide a user-friendly interface to simulate real-world traffic scenarios.
 * - Process user input to:
 *   1. Add vehicles (automobiles or emergency vehicles) to specific roads.
 *   2. Simulate pedestrian crossing events.
 *   3. Trigger errors in the system for testing error handling.
 * - Manage memory by dynamically creating and deleting Vehicle objects.
 *
 * Current Integration:
 * - Fully integrated with the TrafficLightSystem to handle vehicle queues, traffic signals,
 *   and emergency responses.
 * - Supports triggering errors through the ErrorHandler.
 *
 */

#include <iostream>
#include <limits>
#include "TrafficLightSystem.h"  // Header for the traffic light system
#include "Automobile.h"         // Header for Automobile class
#include "EmergencyVehicle.h"   // Header for EmergencyVehicle class

void displaySystemState(TrafficLightSystem& tls) {
    // Displays the current state of traffic lights and queues
    std::cout << "\n--- Current System State ---\n";
    tls.displayTrafficLightStates(); // Method to display traffic light colors
    tls.displayQueueLengths();      // Method to display queue lengths for each road
    std::cout << "-----------------------------\n";
}

int main()
{
    // Display program header
    std::cout << "CSC 300 Project Week#4 Deliverable\n";
    std::cout << "Team: Yellow Means Go\n";
    std::cout << "Adaptive Traffic Light\n\n";

    // Initialize the TrafficLightSystem with a maximum queue length of 10
    TrafficLightSystem tls(10);

    // Main loop to process user input and manage traffic system
    while (true)
    {
        char choice; // User choice for the type of action
        std::cout << "\n>>> Please choose an action:\n"
                  << "    'v' - Add a vehicle (automobile or emergency)\n"
                  << "    'p' - Simulate a pedestrian crossing\n"
                  << "    'e' - Trigger a system error\n"
                  << "    'q' - Quit the program\n"
                  << "Your choice: ";

        // Validate user input for main menu
        do
        {
            std::cin >> choice;
            choice = toupper(choice); // Convert input to uppercase for uniformity
            if (choice != 'Q' && choice != 'V' && choice != 'P' && choice != 'E')
            {
                std::cout << "Invalid Entry. Please Try Again.";
                std::cin.clear(); // Clear invalid input
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore excess input
            }
        } while (choice != 'Q' && choice != 'V' && choice != 'P' && choice != 'E');

        // Exit the program if the user chooses 'q'
        if (choice == 'Q')
        {
            std::cout << "Exiting program. Goodbye!\n";
            return 0;
        }

        // Trigger an error if the user chooses 'e'
        if (choice == 'E')
        {
            std::cout << "\n>>> Triggering a system error...\n";
            tls.triggerError(); // Call method to simulate an error
            displaySystemState(tls); // Show updated state
            continue; // Skip remaining code in this iteration
        }

        // Handle vehicle input if the user chooses 'v'
        if (choice == 'V')
        {
            char vehicleType; // User choice for type of vehicle
            std::cout << "\n>>> Enter 'a' for automobile or 'e' for emergency vehicle: ";

            // Validate user input for vehicle type
            do
            {
                std::cin >> vehicleType;
                vehicleType = toupper(vehicleType); // Convert to uppercase
                if (vehicleType != 'E' && vehicleType != 'A')
                {
                    std::cout << "Invalid Entry. Please Try Again.";
                    std::cin.clear(); // Clear invalid input
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore excess input
                }
            } while (vehicleType != 'E' && vehicleType != 'A');

            // Create the appropriate vehicle object based on user input
            Vehicle* vehicle;
            if (vehicleType == 'E')
            {
                vehicle = new EmergencyVehicle(); // Create an emergency vehicle
            }
            else if (vehicleType == 'A')
            {
                vehicle = new Automobile(); // Create an automobile
            }

            std::cout << "\n>>> Select road (1-4): ";
            int road; // User-selected road number

            // Validate user input for road number
            do
            {
                std::cin >> road;

                if (std::cin.fail() || road < 1 || road > 4)
                {
                    std::cout << "Invalid Entry. Please Try Again.";
                    std::cin.clear(); // Clear invalid input
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore excess input
                }
            } while (std::cin.fail() || road < 1 || road > 4);

            // Handle the vehicle arrival at the specified road
            tls.handleVehicle(vehicle, road);
            delete vehicle; // Free dynamically allocated memory
            displaySystemState(tls); // Show updated state
        }

            // Handle pedestrian input if the user chooses 'p'
        else if (choice == 'P')
        {
            std::cout << "\n>>> Select crosswalk (N for North, S for South, E for East, W for West): ";
            char crosswalk;
            do
            {
                std::cin >> crosswalk;
                crosswalk = toupper(crosswalk);
                if (crosswalk != 'N' && crosswalk != 'S' && crosswalk != 'E' && crosswalk != 'W')
                {
                    std::cout << "Invalid Entry. Please Try Again.";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            } while (crosswalk != 'N' && crosswalk != 'S' && crosswalk != 'E' && crosswalk != 'W');

            // Simulate pedestrian crossing
            std::cout << "\n>>> Pedestrian crossing button activated for the " << crosswalk << " crosswalk.\n";
            tls.handlePedestrian(crosswalk); // Handle pedestrian crossing logic
            displaySystemState(tls); // Show updated state
        }
    }

    return 0;
}

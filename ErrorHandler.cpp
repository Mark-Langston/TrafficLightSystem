/**
 * Implements error detection and handling for the Traffic Light System.
 *
 * This file defines the `ErrorHandler` class, which manages error states and generates 
 * error codes when a malfunction is detected. It is responsible for:
 * - Randomly determining if an error occurs.
 * - Generating and displaying error codes for specific system components (e.g., sensors, cameras).
 * - Providing the error status to other components, such as the Traffic Light System.
 *
 * Current Integration:
 * - The error status (`getErrorStatus`) is used by the Traffic Light System to determine if
 *   the system is in an error state and to handle it accordingly (e.g., setting all signals to red).
 *
 */

#include "ErrorHandler.h"

// Constructor: Initializes the error state and sets the default error code
ErrorHandler::ErrorHandler()
{
    error = false;
    errorCode = "No Error Detected\n";
    srand(time(0)); // Set RNG seed.
}

// Determines if an error is detected.
// Generates a random number to simulate a 10% chance of an error.
void ErrorHandler::errorDetected()
{
    int errorChance = rand() % 10; // Generate a random number between 0 and 9
    error = (errorChance < 1) ? true : false; // 10% chance of setting error to true
}

// Generates an error code if an error is detected.
// Uses a random number to assign a specific error to system components.
void ErrorHandler::generateError()
{
    errorDetected(); // Check if an error occurs

    std::string errorCode = "No Error Detected\n"; // Default error code
    if (error == true)
    {
        int errorGenerated = rand() % 13; // Randomly select an error case (0-12)
        switch (errorGenerated)
        {
            case 0:
                errorCode = "1001 North Sensor\n"; break;
            case 1:
                errorCode = "1002 East Sensor\n"; break;
            case 2:
                errorCode = "1003 West Sensor\n"; break;
            case 3:
                errorCode = "1004 South Sensor\n"; break;
            case 4:
                errorCode = "2001 North Camera\n"; break;
            case 5:
                errorCode = "2002 East Camera\n"; break;
            case 6:
                errorCode = "2003 West Camera\n"; break;
            case 7:
                errorCode = "2004 South Camera\n"; break;
            case 8:
                errorCode = "3001 North Pedestrian Button\n"; break;
            case 9:
                errorCode = "3002 East Pedestrian Button\n"; break;
            case 10:
                errorCode = "3003 West Pedestrian Button\n"; break;
            case 11:
                errorCode = "3004 South Pedestrian Button\n"; break;
            case 12:
                errorCode = "9999 Power Supply\n"; break;
            default:
                errorCode = "Unknown Error\n"; break;
        }
    }
    std::cout << errorCode; // Display the error code
}

// Returns the current error status (true if an error is active, false otherwise)
bool ErrorHandler::getErrorStatus()
{
    return error;
}

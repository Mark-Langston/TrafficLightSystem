/**
 * Implements the behavior of individual traffic lights.
 *
 * Current Integration:
 * - The `TrafficLightSystem` class uses this file to control signal transitions.
 * - Only red and green transitions seem to be actively used, bypassing yellow.
 *
 */
 
#include "TrafficLight.h"

TrafficLight::TrafficLight()
{
    color = "Red";
}

TrafficLight::TrafficLight(std::string direction)
{
    color = "Red";
    this->direction = direction;
}

// Returns the current signal color
std::string TrafficLight::getSignalColor() const
{
    return color;
}

void TrafficLight::changeToGreen()
{
    std::cout << "Changing " + direction + " signal to Green . . .\n";
    color = "Green";
    std::cout << direction + " Signal is now " + color + "!\n";
}

void TrafficLight::changeToYellow()
{
    std::cout << "Changing " + direction + " signal to Yellow . . .\n";
    countdown(3);
    color = "Yellow";
    std::cout << direction + " Signal is now " + color + "!\n";
}

void TrafficLight::changeToRed()
{
    std::cout << "Changing " + direction + " signal to Red . . .\n";
    countdown(3);
    color = "Red";
    std::cout << direction + " Signal is now " + color + "!\n";
}

void TrafficLight::countdown(int seconds)
{
    for (int i = seconds; i > 0; i--)
    {
        std::cout << i << "\n";
    }
}

void TrafficLight::changeSignal(std::string colorTarget, ErrorHandler errorHandle, EventFlag& event)
{
    bool error = errorHandle.getErrorStatus();

    if (error == true && color != "Blinking Red")
    {
        color = "Blinking Red";
        std::cout << "Error detected. Signals are blinking red!\n";
        return;
    }

    if (error == true && color == "Blinking Red")
    {
        std::cout << "New error detected! Signals remain blinking red!\n";
        return;
    }

    if (error == false && color == "Blinking Red")
    {
        color = "Red";
        std::cout << "No error detected anymore. Signals are now solid red.\n";
        return;
    }

    if (error == false && event.isEmergencyDetected() == true)
    {
        event.setEmergencyDetected(false);
        changeSignal("Red", errorHandle, event);
        return;
    }

    if (color == colorTarget)
    {
        std::cout << direction << " Signal is already the desired color. No change is needed.\n";
        return;
    }

    else if (colorTarget == "Red")
    {
        changeToYellow();
        changeToRed();
        return;
    }

    else if (colorTarget == "Green")
    {
        changeToGreen();
        return;
    }
}

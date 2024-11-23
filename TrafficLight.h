#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "ErrorHandler.h"
#include "EventFlag.h"
#include <string>

class TrafficLight
{
private:
    std::string color;      // Current signal color (e.g., Red, Yellow, Green)
    std::string direction;  // Direction of the traffic light (e.g., North, South)

public:
    TrafficLight();
    TrafficLight(std::string direction);

    // Returns the current signal color (now marked as const)
    std::string getSignalColor() const;

    void changeToGreen();
    void changeToYellow();
    void changeToRed();
    void countdown(int seconds);
    void changeSignal(std::string colorTarget, ErrorHandler errorHandle, EventFlag& event);
};

#endif // TRAFFICLIGHT_H

#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <iostream>
#include <string>

// Class to handle errors in the Traffic Light System
class ErrorHandler
{
public:
    // Constructor to initialize the error handler
    ErrorHandler();

    // Method to set error status when an error is detected
    void errorDetected();

    // Method to generate an error with a corresponding error code
    void generateError();

    // Method to check if an error has been detected
    bool getErrorStatus();

    // Method to set error status
    void setError(bool parameter);

private:
    bool error;          // Boolean to track the presence of an error
    std::string errorCode; // Stores the error code for detected issues
};

#endif // ERRORHANDLER_H

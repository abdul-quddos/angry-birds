#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include"mystring.h"

class Logger {
private:
    std::ofstream logFile;

public:
    Logger()
    {

    }
    Logger(const char* filename) {
        logFile.open(filename, std::ios::app);
    }

    ~Logger() {
        if (logFile.is_open())
            logFile.close();
    }

    void logInfo(const char* message) {
        if (logFile.is_open())
            logFile << "[INFO] " << message << '\n';
    }

    void logWarning(const char* message) {
        if (logFile.is_open())
            logFile << "[WARNING] " << message << '\n';
    }

    void logError(const char* message) {
        if (logFile.is_open())
            logFile << "[ERROR] " << message << '\n';
    }
};

#endif

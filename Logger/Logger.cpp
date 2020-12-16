//
// Created by Michal on 08-Dec-20.
//
#include <iostream>
#include <sstream>
#include <fstream>
#include "Logger.h"
#include <chrono>

const std::string path = "file.log";

void Logger::log(bool printToOutput, const std::string &component, const std::string &err)
{
    time_t now = time(nullptr);
    std::string currentTime = std::asctime(std::localtime(&now));

    currentTime = currentTime.erase(currentTime.length() - 1, 1);

    std::stringstream stream;
    stream << currentTime << "  " << component << ": " << err << std::endl;

    if (printToOutput) {
        std::cerr << stream.str();
    }

    std::ofstream logFile;
    logFile.open(path, std::ofstream::app);
    logFile << stream.str();
    logFile.flush();
    logFile.close();
}

void Logger::log(bool printToOutput, const std::string &component, const std::string &err, const std::string &cause)
{
    std::stringstream stream;
    stream << component << ": " << err << std::endl
           << "Cause: " << cause << std::endl;

    if (printToOutput) {
        std::cerr << stream.str();
    }

    std::ofstream logFile;
    logFile.open(path, std::ofstream::app);
    logFile << stream.str();
    logFile.flush();
    logFile.close();
}
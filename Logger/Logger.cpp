//
// Created by Michal on 08-Dec-20.
//
#include <iostream>
#include <sstream>
#include <fstream>
#include "Logger.h"

const std::string path = "file.log";

void Logger::log(bool printToOutput, const std::string &component, const std::string &err)
{
    std::stringstream stream;
    stream << component << ": " << err << std::endl;

    if (printToOutput) {
        std::cerr << stream.str();
    }

    std::ofstream logFile;
    logFile.open(path, std::ofstream::app);
    logFile << stream.str();
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
    logFile.close();
}
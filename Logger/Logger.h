//
// Created by Michal on 08-Dec-20.
//

#ifndef SOLARSERVER_LOGGER_H
#define SOLARSERVER_LOGGER_H
#include <iostream>
class Logger
{
  public:
    static void log(bool printToOutput, const std::string &component, const std::string &err);
    static void log(bool printToOutput, const std::string &component, const std::string &err, const std::string &cause);
};

#endif // SOLARSERVER_LOGGER_H

//
// Created by Michal on 15-Dec-20.
//

#ifndef SOLARSERVER_RESPONSEMANAGER_H
#define SOLARSERVER_RESPONSEMANAGER_H

#include <string>
#include "RequestParser.h"
#include "../ServerInstance.h"

class ResponseManager
{
  private:
    std::string httpOK();
    std::string mainPage(std::string arg);
    std::string GETRequest(Request &request);
    std::string POSTRequest(Request &request);
    void addRow(std::string &fileSoFar, size_t cellN, std::string *rowElement);
    ProgramOptions options;

  public:
    explicit ResponseManager(ProgramOptions &opt);
    std::string respond(Request &request);
};

#endif //SOLARSERVER_RESPONSEMANAGER_H

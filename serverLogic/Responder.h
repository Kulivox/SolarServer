//
// Created by Michal on 15-Dec-20.
//

#ifndef SOLARSERVER_RESPONDER_H
#define SOLARSERVER_RESPONDER_H

#include <string>
#include "RequestParser.h"

class Responder
{
  private:
    std::string httpOK();
    std::string mainPage(std::string arg);
    std::string GETRequest(Request &request);
    std::string POSTRequest(Request &request);
    void addRow(std::string &fileSoFar, size_t cellN, std::string *rowElement);

  public:
    std::string respond(Request &request);
};

#endif //SOLARSERVER_RESPONDER_H

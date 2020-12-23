//
// Created by Michal on 15-Dec-20.
//

#ifndef SOLARSERVER_RESPONSEBUFFERBUILDER_H
#define SOLARSERVER_RESPONSEBUFFERBUILDER_H

#include <string>
#include "RequestParser.h"
#include "../ServerInstance.h"

class ResponseBufferBuilder
{
  private:
    std::string httpOK();
    static const char *mainPage(size_t *len);
    const char *GETRequest(Request &request, size_t *len);
    const char *querylessRequest(Request &request, size_t *len);
    static const char *queryRequest(Request &request, size_t *len);
    std::string POSTRequest(Request &request);
    static void addRow(std::string &fileSoFar, size_t cellN, std::string *rowElement);
    ProgramOptions options;

  public:
    explicit ResponseBufferBuilder(ProgramOptions &opt);
    char *createResponseBuffer(Request &request, size_t *len);
};

#endif //SOLARSERVER_RESPONSEBUFFERBUILDER_H

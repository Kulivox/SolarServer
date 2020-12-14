//
// Created by Michal on 14-Dec-20.
//

#ifndef SOLARSERVER_REQUESTPARSER_H
#define SOLARSERVER_REQUESTPARSER_H
#include <string>
#include "InverterDataExtractor.h"
class RequestParser
{
  public:
    static std::string parseRequest(int8_t *buffer, size_t buffSize);
    static InverterDataExtractor *extractor;
};

#endif //SOLARSERVER_REQUESTPARSER_H

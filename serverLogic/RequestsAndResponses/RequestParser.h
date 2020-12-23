//
// Created by Michal on 14-Dec-20.
//

#ifndef SOLARSERVER_REQUESTPARSER_H
#define SOLARSERVER_REQUESTPARSER_H
#include <string>

#include "../../inveterExtractor/InverterDataExtractor.h"

struct Request
{
    std::string type;
    std::string path;
    std::string query;
    char *payload;
    size_t payloadSize;
};

class RequestParser
{
  public:
    static Request parseRequest(int8_t *buffer, size_t buffSize);
    static Request parseRequest(int8_t *buffer);
};

#endif //SOLARSERVER_REQUESTPARSER_H

//
// Created by Michal on 23-Dec-20.
//

#ifndef SOLARSERVER_QUERYRESPONSEBUILDER_H
#define SOLARSERVER_QUERYRESPONSEBUILDER_H
#include "../Response.h"
#include "../RequestParser.h"

class QueryResponseBuilder
{
  public:
    static Response *buildQueryResponse(Request &request);
};

#endif //SOLARSERVER_QUERYRESPONSEBUILDER_H

//
// Created by Michal on 23-Dec-20.
//

#ifndef SOLARSERVER_FILEBEARINGRESPONSEBUILDER_H
#define SOLARSERVER_FILEBEARINGRESPONSEBUILDER_H
#include "../RequestParser.h"
#include "../Response.h"
#include "../../../File.h"
#include "../../../Options/ProgramOptions.h"

class FileBearingResponseBuilder
{
  public:
    static Response *buildFileBearingResponse(Request &request, ProgramOptions *options);
};

#endif //SOLARSERVER_FILEBEARINGRESPONSEBUILDER_H

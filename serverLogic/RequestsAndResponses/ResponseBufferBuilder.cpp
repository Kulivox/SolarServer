//
// Created by Michal on 15-Dec-20.
//

#include "ResponseBufferBuilder.h"
#include "../../File.h"
#include "Response.h"
#include <cstring>
#include "PageResponses/FileBearingResponseBuilder.h"
#include "QueryResponses/QueryResponseBuilder.h"

char *ResponseBufferBuilder::createResponseBuffer(Request &request, size_t *len)
{
    char *result = nullptr;

    if (request.type == "GET") {
        result = const_cast<char *>(GETRequest(request, len));
    }
    return result;
}

//todo create function for post requests
std::string ResponseBufferBuilder::POSTRequest(Request &request)
{
    return std::string();
}

const char *ResponseBufferBuilder::GETRequest(Request &request, size_t *len)
{
    if (request.query.empty()) {
        Response *response = FileBearingResponseBuilder::buildFileBearingResponse(request, &options);
        char *responseString = response->getResponseBuffer();
        *len = response->getResponseLength();
        delete (response);
        return responseString;
    }

    Response *response = QueryResponseBuilder::buildQueryResponse(request);
    char *responseString = response->getResponseBuffer();
    *len = response->getResponseLength();
    delete (response);
    return responseString;
}

ResponseBufferBuilder::ResponseBufferBuilder(ProgramOptions &opt)
{
    options = opt;
}


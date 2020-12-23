//
// Created by Michal on 23-Dec-20.
//

#include "QueryResponseBuilder.h"
#include <map>
#include "MainPage/MainPageBuilder.h"
typedef const char *(*RequestFunction)(size_t *len);

Response *QueryResponseBuilder::buildQueryResponse(Request &request)
{
    std::map<std::string, RequestFunction> functionMap;
    functionMap["mainTable"] = MainPageBuilder::mainPage;
    std::string type = "html";
    std::string optional;
    size_t tempLen = 0;
    const char *buff = functionMap[request.query](&tempLen);

    auto *response = new Response(HTTP200, type, optional, buff, tempLen);
    delete buff;

    return response;
}

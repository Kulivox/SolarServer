//
// Created by Michal on 23-Dec-20.
//

#include "QueryResponseBuilder.h"
#include <map>
#include "MainPage/MainPageBuilder.h"
#include "MainPageChart/MainPageChartDataBuilder.h"
typedef char *(*RequestFunction)(size_t *len);

Response *QueryResponseBuilder::buildQueryResponse(Request &request)
{
    std::map<std::string, RequestFunction> functionMap;
    functionMap["mainTable"] = MainPageBuilder::mainPage;
    functionMap["activePowerUsageChart"] = MainPageChartDataBuilder::getChartDataAsString;
    std::string type = "html";
    std::string optional;
    size_t tempLen = 0;

    char *buff = new char[1];
    buff[0] = '\0';
    RequestFunction function = functionMap[request.query];
    if (function != nullptr) {
        delete[] buff;
        buff = function(&tempLen);
    }

    auto *response = new Response(HTTP200, type, optional, buff, tempLen);
    delete[] buff;

    return response;
}

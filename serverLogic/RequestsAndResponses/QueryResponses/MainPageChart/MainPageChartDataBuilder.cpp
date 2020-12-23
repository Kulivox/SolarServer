//
// Created by Michal on 23-Dec-20.
//

#include "MainPageChartDataBuilder.h"
#include "../../../../DataStorage/DataStorage.h"
#include "sstream"
#include <cstring>
#include <ctime>

char *MainPageChartDataBuilder::getChartDataAsString(size_t *len)
{
    // this function will generate dataset for last day
    auto *usage = new PowerUsage[8640];
    size_t extractedDataSize = DataStorage::getPowerUsageStats(86400, usage, 8640);
    std::stringstream labelStream;
    labelStream << "[";
    std::stringstream dataStream;
    dataStream << "[";

    std::string stringTime;

    for (size_t i = 0; i < extractedDataSize - 1; i++) {
        stringTime = std::asctime(std::localtime(&usage[i].timestamp));
        labelStream << "\"" << stringTime.substr(0, stringTime.length() - 2) << "\",";
        dataStream << usage[i].usage << ",";
    }

    stringTime = std::asctime(std::localtime(&usage[extractedDataSize - 1].timestamp));

    labelStream << "\"" << stringTime.substr(0, stringTime.length() - 2) << "\"]";
    dataStream << usage[extractedDataSize - 1].usage << "]";

    std::string resultString = "{\"labels\": " + labelStream.str() + ", \"data\": " + dataStream.str() + "}";
    char *result = new char[resultString.length()];
    memcpy(result, resultString.c_str(), resultString.length());
    *len = resultString.length();
    return result;
}

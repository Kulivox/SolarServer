//
// Created by Michal on 14-Dec-20.
//

#include "RequestParser.h"
#include "inverterComm.h"
#include <iostream>
#include "InverterDataExtractor.h"

std::string RequestParser::parseRequest(int8_t *buffer, size_t buffSize)
{
    auto info = RequestParser::extractor->getGeneralInfo();

    return std::string("HTTP/1.1 200 OK\n\n") + "Napatie na baterke: " + std::to_string(info->batteryVoltage) + "V Zatazenie menica: " + std::to_string(info->outputLoadPercent) + "%";
}

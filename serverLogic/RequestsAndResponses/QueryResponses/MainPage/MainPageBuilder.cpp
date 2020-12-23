//
// Created by Michal on 23-Dec-20.
//

#include "MainPageBuilder.h"
#include "../../../../inveterExtractor/InverterDataExtractor.h"
#include <sstream>
#include <cstring>

char *MainPageBuilder::mainPage(size_t *len)
{
    auto info = InverterDataExtractor::getGeneralInfo();

    std::string table;
    std::string gridVoltage[2] = { "Napätie verejnej siete: ", std::to_string(info->gridVoltage) + "V" };
    addRow(table, 2, gridVoltage);
    std::string inverterOutputVoltage[2] = { "AC napätie meniča: ", std::to_string(info->acOutput) + "V" };
    addRow(table, 2, inverterOutputVoltage);
    std::string pvOutputPower[2] = { "Výkon panelov: ", std::to_string(info->pvInputCurrentBattery * info->pvInputVoltage1) + "W" };
    addRow(table, 2, pvOutputPower);

    std::string voltage[2] = { "Napätie batérii:", std::to_string(info->batteryVoltage) + " V" };
    addRow(table, 2, voltage);
    std::string batteryChargingCurrent[2] = { "Nabíjací prúd batérie: ", std::to_string(info->batteryChargingCurrent) + "A" };
    addRow(table, 2, batteryChargingCurrent);
    std::string batteryDischargeCurrent[2] = { "Vybíjací prúd batérie: ", std::to_string(info->batteryDischargeCurrent) + "A" };
    addRow(table, 2, batteryDischargeCurrent);
    std::string batteryCapacity[2] = { "Batéria nabitá na: ", std::to_string(info->batteryCapacity) + "%" };
    addRow(table, 2, batteryCapacity);

    std::string acOutputpower[2] = { "Záťaž:", std::to_string(info->acOutputActivePower) + " W" };
    addRow(table, 2, acOutputpower);
    std::string outputLoadPercent[2] = { "Záťaž v percentách:", std::to_string(info->outputLoadPercent) + "%" };
    addRow(table, 2, outputLoadPercent);

    *len = table.length();
    char *res = new char[table.length() + 1];
    memcpy(res, table.c_str(), table.length());
    res[table.length()] = '\0';
    return res;
}
void MainPageBuilder::addRow(std::string &fileSoFar, size_t cellN, std::string *rowElement)
{
    std::stringstream stream;
    stream << "<tr>\n";
    for (size_t i = 0; i < cellN; i++) {
        stream << "<td>" + rowElement[i] + "</td>\n";
    }
    stream << "</tr>\n";

    fileSoFar = fileSoFar + stream.str();
}
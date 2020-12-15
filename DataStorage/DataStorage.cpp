//
// Created by Michal on 15-Dec-20.
//

#include "DataStorage.h"
#include <mutex>
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>

std::mutex fileMutex;

void DataStorage::storeData(generalInfo *info)
{
    std::stringstream stream;

    time_t currentTime;
    currentTime = time(nullptr);

    stream << currentTime << info->gridVoltage << "," << info->gridFrequency << "," << info->acOutput << ","
           << info->acOutFreq << "," << info->acOutputApparentPower << "," << info->acOutputActivePower << ","
           << info->outputLoadPercent << "," << info->busVoltage << "," << info->batteryChargingCurrent << ","
           << info->batteryCapacity << "," << info->heatSinkTemp << "," << info->pvInputCurrentBattery << ","
           << info->pvInputVoltage1 << "," << info->batteryVoltageSCC << "," << info->batteryChargingCurrent << "\n";

    std::lock_guard<std::mutex> guard(fileMutex);
    std::ofstream file;
    file.open("data.csv", std::ofstream::app);
    file << stream.str();
    file.flush();
    file.close();
}
void DataStorage::extractData(ExtractedData *data)
{
}

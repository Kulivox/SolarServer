//
// Created by Michal on 15-Dec-20.
//

#ifndef SOLARSERVER_DATASTORAGE_H
#define SOLARSERVER_DATASTORAGE_H
#include "../inverterComm.h"
#include <iostream>

//todo finish this struct, it should contain data retrieved from database / csv file
struct ExtractedData
{
    std::string timestamp;
    std::string gridVoltage;
    std::string gridFreq;
    std::string acOutput;
    std::string acOutFreq;
    std::string acOutApparentPower;
    std::string acOutputActivePower;
    std::string outputLoadPercent;
    std::string busVoltage;
    std::string batteryChargingCurrent;
    std::string batteryCapacity;
    std::string heatSinkTemp;
    std::string pvInputCurrentBattery;
    std::string pvInputVoltage1;
    std::string batteryVoltageSCC;
};

struct PowerUsage
{
    time_t timestamp;
    std::string usage;
};

class DataStorage
{
  private:
    static size_t extractData(ExtractedData **data, time_t leftBound, time_t rightBound, size_t maxAmountOfData);

  public:
    static void storeData(generalInfo *info);
    static size_t getPowerUsageStats(time_t timeRangeFromNow, PowerUsage *powerUsageArr, size_t maxArrLen);
};

#endif //SOLARSERVER_DATASTORAGE_H

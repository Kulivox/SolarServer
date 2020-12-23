//
// Created by Michal on 15-Dec-20.
//

#include "DataStorage.h"
#include <mutex>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>

std::mutex fileMutex;

void DataStorage::storeData(generalInfo *info)
{
    std::stringstream stream;

    time_t currentTime;
    currentTime = time(nullptr);

    stream << currentTime << "," << info->gridVoltage << "," << info->gridFrequency << "," << info->acOutput << ","
           << info->acOutFreq << "," << info->acOutputApparentPower << "," << info->acOutputActivePower << ","
           << info->outputLoadPercent << "," << info->busVoltage << "," << info->batteryChargingCurrent << ","
           << info->batteryCapacity << "," << info->heatSinkTemp << "," << info->pvInputCurrentBattery << ","
           << info->pvInputVoltage1 << "," << info->batteryVoltageSCC << "\n";

    std::ofstream file;
    fileMutex.lock();

    file.open("data.csv", std::ofstream::app);
    file << stream.str();
    file.flush();
    file.close();

    fileMutex.unlock();
}

void splitString(std::vector<std::string> &strings, std::string &str, std::string &delimiter)
{
    size_t pos = str.find(delimiter);

    while (pos != std::string::npos) {
        std::string substr = str.substr(0, pos);
        strings.push_back(substr);
        str.erase(0, substr.length() + delimiter.length());
        pos = str.find(delimiter);
    }
}

size_t DataStorage::extractData(ExtractedData **data, time_t leftBound, time_t rightBound, size_t maxAmountOfData)
{
    fileMutex.lock();
    std::ifstream file("data.csv");
    std::string line;
    time_t timestampNum = 0;

    *data = new ExtractedData[maxAmountOfData];
    size_t count = 0;
    while (!file.eof() && count < maxAmountOfData && timestampNum <= rightBound) {
        getline(file, line);
        std::string token = ",";
        size_t pos = line.find(token);
        std::string timestamp = line.substr(0, pos);

        timestampNum = atoi(timestamp.c_str());
        if (timestampNum >= leftBound && timestampNum <= rightBound) {
            std::vector<std::string> strings;

            splitString(strings, line, token);
            auto stringsIterator = strings.begin();

            (*data)[count].timestamp = strings[0];
            (*data)[count].gridVoltage = strings[1];
            (*data)[count].gridFreq = strings[2];
            (*data)[count].acOutput = strings[3];
            (*data)[count].acOutFreq = strings[4];
            (*data)[count].acOutApparentPower = strings[5];
            (*data)[count].acOutputActivePower = strings[6];
            (*data)[count].outputLoadPercent = strings[7];
            (*data)[count].busVoltage = strings[8];
            (*data)[count].batteryChargingCurrent = strings[9];
            (*data)[count].batteryCapacity = strings[10];
            (*data)[count].heatSinkTemp = strings[11];
            (*data)[count].pvInputCurrentBattery = strings[12];
            (*data)[count].pvInputVoltage1 = strings[13];
            count += 1;
        }
    }
    file.close();
    fileMutex.unlock();
    return count;
}
size_t DataStorage::getPowerUsageStats(time_t timeRangeFromNow, PowerUsage *powerUsageArr, size_t maxArrLen)
{
    ExtractedData *data;
    time_t rightBound = time(nullptr);
    time_t leftBound = rightBound - timeRangeFromNow;
    size_t sizeOfExtractedData = extractData(&data, leftBound, rightBound, maxArrLen);

    for (size_t i = 0; i < maxArrLen && i < sizeOfExtractedData; i++) {
        powerUsageArr[i].timestamp = atoi(data[i].timestamp.c_str());
        powerUsageArr[i].usage = data[i].acOutputActivePower;
    }

    delete[] data;
    return sizeOfExtractedData;
}

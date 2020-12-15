//
// Created by Michal on 15-Dec-20.
//

#ifndef SOLARSERVER_DATASTORAGE_H
#define SOLARSERVER_DATASTORAGE_H
#include "../inverterComm.h"

//todo finish this struct, it should contain data retrieved from database / csv file
struct ExtractedData
{
    void *data;
};

class DataStorage
{
    static void extractData(ExtractedData *data);

  public:
    static void storeData(generalInfo *info);
};

#endif //SOLARSERVER_DATASTORAGE_H

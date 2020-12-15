//
// Created by Michal on 14-Dec-20.
//

#ifndef SOLARSERVER_INVERTERDATAEXTRACTOR_H
#define SOLARSERVER_INVERTERDATAEXTRACTOR_H
#include "../inverterComm.h"
#include <pthread.h>

class InverterDataExtractor
{
  private:
    static void *extractAndSetData(void *);
    static const uint8_t SLEEP_LEN_IN_SEC = 10;
    static generalInfo *info;
    pthread_t tid;

  public:
    generalInfo *getGeneralInfo();
    pthread_t getTID();
    InverterDataExtractor();
    ~InverterDataExtractor();
};

#endif //SOLARSERVER_INVERTERDATAEXTRACTOR_H

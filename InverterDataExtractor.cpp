//
// Created by Michal on 14-Dec-20.
//

#include "InverterDataExtractor.h"
#include "Logger.h"

struct DataForThread
{
    inverterCommContext *context;
    bool *run;
    generalInfo *info;
};

void *InverterDataExtractor::extractAndSetData(void *arg)
{
    auto data = (DataForThread *) arg;

    while (*data->run) {
        getState(data->context, data->info);
        sleep(InverterDataExtractor::SLEEP_LEN_IN_SEC);
    }

    return nullptr;
}
InverterDataExtractor::InverterDataExtractor(bool *run)
{
    inverterCommContext *context = createContext("/dev/ttyUSB0");
    info = (generalInfo *) calloc(1, sizeof(generalInfo));

    tid = 0;
    auto data = (DataForThread *) calloc(1, sizeof(DataForThread));
    data->context = context;
    data->run = run;
    data->info = info;

    int result = pthread_create(&tid, nullptr, InverterDataExtractor::extractAndSetData, (void *) data);
    if (result != 0) {
        Logger::log(true, "InverterDataExtractor", "Failed to create new thread");
        exit(1);
    }
}
generalInfo *InverterDataExtractor::getGeneralInfo()
{
    return this->info;
}
InverterDataExtractor::~InverterDataExtractor()
{
    pthread_join(this->tid, nullptr);
    free(info);
}

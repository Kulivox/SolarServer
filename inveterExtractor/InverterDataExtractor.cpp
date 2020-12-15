//
// Created by Michal on 14-Dec-20.
//

#include "InverterDataExtractor.h"
#include "../Logger/Logger.h"

#include <mutex>
#include <csignal>
#include <iostream>
#include <ctime>
#include "../DataStorage/DataStorage.h"
#include <cerrno>
#include <cstring>

generalInfo *InverterDataExtractor::info;

struct DataForThread
{
    inverterCommContext *context;
};

void handler(int signo)
{
    std::cout << "Turning off extractor..";
    std::cout.flush();
}

void *InverterDataExtractor::extractAndSetData(void *arg)
{
    sigset_t signalSet;
    sigemptyset(&signalSet);
    sigaddset(&signalSet, SIGALRM);
    signal(SIGALRM, handler);

    auto data = (DataForThread *) arg;
    timespec waitLen = { 10, 0 };

    while (true) {
        getState(data->context, InverterDataExtractor::info);
        DataStorage::storeData(InverterDataExtractor::info);

        int resultOfWait = sigtimedwait(&signalSet, nullptr, &waitLen);

        if (resultOfWait == SIGALRM || errno == SIGALRM) {
            break;
        }

        if (errno != EAGAIN) {
            perror("wtf");
            exit(1);
        }
    }

    return nullptr;
}
InverterDataExtractor::InverterDataExtractor()
{
    inverterCommContext *context = createContext("/dev/ttyUSB0");
    info = (generalInfo *) calloc(1, sizeof(generalInfo));

    tid = 0;
    auto data = (DataForThread *) calloc(1, sizeof(DataForThread));
    data->context = context;

    int result = pthread_create(&tid, nullptr, InverterDataExtractor::extractAndSetData, (void *) data);
    if (result != 0) {
        Logger::log(true, "InverterDataExtractor", "Failed to create new thread");
        exit(1);
    }
}
generalInfo *InverterDataExtractor::getGeneralInfo()
{
    return InverterDataExtractor::info;
}
InverterDataExtractor::~InverterDataExtractor()
{
    pthread_join(this->tid, nullptr);
    free(info);
}

pthread_t InverterDataExtractor::getTID()
{
    return tid;
}

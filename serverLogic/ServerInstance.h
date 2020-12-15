//
// Created by Michal on 08-Dec-20.
//

#ifndef SOLARSERVER_SERVERINSTANCE_H
#define SOLARSERVER_SERVERINSTANCE_H
#include <sys/socket.h>

#include <string>
#include "../Logger/Logger.h"
#include <cstdint>
#include "../inveterExtractor/InverterDataExtractor.h"

class ServerInstance
{
  private:
    int sockFD;

  public:
    ServerInstance(const std::string &address, uint16_t port);
    int32_t start(bool *run, InverterDataExtractor &extractor);
    static void *startProcessing(void *sockFD);
    ~ServerInstance();
};
#endif // SOLARSERVER_SERVERINSTANCE_H

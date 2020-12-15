//
// Created by Michal on 14-Dec-20.
//

#ifndef SOLARSERVER_USERINTERFACE_H
#define SOLARSERVER_USERINTERFACE_H
#include <pthread.h>
#include "../Logger/Logger.h"

class UserInterface
{
  private:
    static void *interface(void *);
    static bool run;
    pthread_t tid;

  public:
    static bool *getRunPointer();
    explicit UserInterface(pthread_t pid);
    ~UserInterface();
};

#endif //SOLARSERVER_USERINTERFACE_H

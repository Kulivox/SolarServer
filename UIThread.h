//
// Created by Michal on 14-Dec-20.
//

#ifndef SOLARSERVER_UITHREAD_H
#define SOLARSERVER_UITHREAD_H
#include <pthread.h>
#include "Logger.h"

class UIThread
{
  private:
    static void *interface(void *);
    static bool run;
    pthread_t tid;

  public:
    static bool *getRunPointer();
    UIThread();
    ~UIThread();
};

#endif //SOLARSERVER_UITHREAD_H

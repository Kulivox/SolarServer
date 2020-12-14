//
// Created by Michal on 14-Dec-20.
//

#include "UIThread.h"
#include <iostream>
#include <string>

bool UIThread::run = true;

void *UIThread::interface(void *)
{
    while (run) {
        std::string line = std::string();
        getline(std::cin, line);
        if (line == "EXIT") {
            run = false;
        } else {
            std::cout << "I only know EXIT\n";
        }
    }

    return nullptr;
}

UIThread::UIThread()
{
    this->tid = 0;
    int result = pthread_create(&this->tid, nullptr, UIThread::interface, nullptr);
    if (result != 0) {
        Logger::log(true, "UIThread", "cant create Thread");
    }
}

UIThread::~UIThread()
{
    pthread_join(this->tid, nullptr);
}

bool *UIThread::getRunPointer()
{
    return &run;
}

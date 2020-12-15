//
// Created by Michal on 14-Dec-20.
//

#include "UserInterface.h"
#include <iostream>
#include <string>
#include <csignal>

bool UserInterface::run = true;

void *UserInterface::interface(void *arg)
{
    auto extractorTID = (pthread_t) arg;

    while (run) {
        std::string line = std::string();
        getline(std::cin, line);
        if (line == "EXIT") {
            pthread_kill(extractorTID, SIGALRM);
            run = false;

        } else {
            std::cout << "I only know EXIT\n";
        }
    }

    return nullptr;
}

UserInterface::UserInterface(pthread_t extractorTID)
{
    this->tid = 0;
    int result = pthread_create(&this->tid, nullptr, UserInterface::interface, (void *) extractorTID);
    if (result != 0) {
        Logger::log(true, "UserInterface", "cant create Thread");
    }
}

UserInterface::~UserInterface()
{
    pthread_join(this->tid, nullptr);
}

bool *UserInterface::getRunPointer()
{
    return &run;
}

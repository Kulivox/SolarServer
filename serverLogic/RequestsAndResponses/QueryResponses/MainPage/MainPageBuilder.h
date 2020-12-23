//
// Created by Michal on 23-Dec-20.
//

#ifndef SOLARSERVER_MAINPAGEBUILDER_H
#define SOLARSERVER_MAINPAGEBUILDER_H
#include <iostream>

class MainPageBuilder
{
    static void addRow(std::string &fileSoFar, size_t cellN, std::string *rowElement);

  public:
    static char *mainPage(size_t *len);
};

#endif //SOLARSERVER_MAINPAGEBUILDER_H

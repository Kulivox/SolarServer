//
// Created by Michal on 21-Dec-20.
//
#include "RequestParserTests.h"
#include <iostream>
#include "tests.h"

int runTests()
{
    int failedTests = 0;

    failedTests += requestParserTests();

    std::cout << "\n\n";
    if (failedTests == 0) {
        std::cout << "All tests OK\n";
        return 0;
    }

    std::cout << failedTests << " tests Failed\n";

    return 1;
}
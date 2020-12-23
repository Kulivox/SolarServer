//
// Created by Michal on 21-Dec-20.
//

#include "RequestParserTests.h"
#include "../serverLogic/RequestsAndResponses/RequestParser.h"
#include <iostream>

int testBadRequest()
{
    std::string request = "GET??1haramalej\n";
    Request req = RequestParser::parseRequest((int8_t *) request.c_str());
    bool badBehaviour = !req.query.empty() ||
            !req.path.empty() ||
            !req.type.empty() ||
            req.payload != nullptr ||
            req.payloadSize != 0;

    if (badBehaviour) {
        std::cout << "Test BadRequest FAILED\n";
        return 1;
    }

    return 0;
}

int testGoodRequestNoQuery()
{
    std::string request = "GET /styles/styles.css enncoding asdasd afiasfjaisnfnasf";
    Request req = RequestParser::parseRequest((int8_t *) request.c_str());
    bool badBehaviour = !req.query.empty() ||
            req.path != "/styles/styles.css" ||
            req.type != "GET" ||
            req.payload != nullptr ||
            req.payloadSize != 0;

    if (badBehaviour) {
        std::cout << "Test GoodRequestNoQuery FAILED\n";
        return 1;
    }

    return 0;
}

int testGoodRequestQuery()
{
    std::string request = "GET /table/inverterState?all=true enncoding asdasd afiasfjaisnfnasf";
    Request req = RequestParser::parseRequest((int8_t *) request.c_str());
    bool badBehaviour = req.query != "all=true" ||
            req.path != "/table/inverterState" ||
            req.type != "GET" ||
            req.payload != nullptr ||
            req.payloadSize != 0;

    if (badBehaviour) {
        std::cout << "Test GoodRequestQuery FAILED\n";
        return 1;
    }

    return 0;
}

int testGoodRequestJustGetAndQuery()
{
    std::string request = "GET /table/inverterState?all=true";
    Request req = RequestParser::parseRequest((int8_t *) request.c_str());
    bool badBehaviour = req.query != "all=true" ||
            req.path != "/table/inverterState" ||
            req.type != "GET" ||
            req.payload != nullptr ||
            req.payloadSize != 0;

    if (badBehaviour) {
        std::cout << "Test GoodRequestJustGetAndQuery FAILED\n";
        return 1;
    }

    return 0;
}
int requestParserTests()
{
    int (*tests[])() = { testBadRequest, testGoodRequestNoQuery, testGoodRequestQuery, testGoodRequestJustGetAndQuery };
    int failedTests = 0;
    for (int (*test)() : tests) {
        failedTests += test();
    }

    return failedTests;
}

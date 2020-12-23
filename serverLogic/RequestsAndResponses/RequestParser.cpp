//
// Created by Michal on 14-Dec-20.
//

#include "RequestParser.h"
#include "../../inverterComm.h"
#include <iostream>
#include <regex>

Request RequestParser::parseRequest(int8_t *buffer, size_t buffSize)
{
    //    auto info = RequestParser::extractor->getGeneralInfo();
    //    std::ifstream myFile("../index.html");
    //    std::stringstream stream;
    //    std::string text;
    //
    //    while (getline(myFile, text)) {
    //        stream << text;
    //    }
    //
    //    return "HTTP/1.2 200 OK\n"
    //           "Content-Type: text/html; charset=UTF-8\n\n" + stream.str();
    return Request{};
}

Request RequestParser::parseRequest(int8_t *buffer)
{
    const std::string requestString((char *) buffer);
    //    std::cout << requestString;
    std::regex requestRegex(R"(([A-Z]+) (\S+)\?(\S+))");
    std::smatch match;
    Request requestStruct = { std::string(), std::string(), std::string(), nullptr, 0 };

    if (std::regex_search(requestString.begin(), requestString.end(), match, requestRegex)) {
        requestStruct.type = match[1];
        requestStruct.path = match[2];
        requestStruct.query = match[3];

        return requestStruct;
    }

    requestRegex = std::regex(R"(([A-Z]+) (\S+))");
    if (std::regex_search(requestString.begin(), requestString.end(), match, requestRegex)) {
        requestStruct.type = match[1];
        requestStruct.path = match[2];

        return requestStruct;
    }

    return requestStruct;
}

//
// Created by Michal on 14-Dec-20.
//

#include "RequestParser.h"
#include "../inverterComm.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "../inveterExtractor/InverterDataExtractor.h"

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
    std::string request((char *) buffer);
    std::string delimiter = " ";
    Request req;

    req.type = "GET";
    req.path = "/";
    req.payload = "";

    return req;
}

//
// Created by Michal on 14-Dec-20.
//

#include "RequestParser.h"
#include "../../inverterComm.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "../../inveterExtractor/InverterDataExtractor.h"

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

    size_t pos = request.find(delimiter);
    std::string token = request.substr(0, pos);
    req.type = token;
    request = request.erase(0, pos + delimiter.length());
    pos = request.find(delimiter);
    token = request.substr(0, pos);
    req.path = token.erase(0, 1);

    if (req.path.empty()) {
        req.path = "index.html";
    }

    req.payload = "";

    return req;
}

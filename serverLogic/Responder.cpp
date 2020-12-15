//
// Created by Michal on 15-Dec-20.
//

#include "Responder.h"
#include <fstream>
#include <sstream>

std::string Responder::respond(Request &request)
{
    std::string result;

    if (request.type == "GET") {
        result = GETRequest(request);
    }
    return result;
}

//todo create function for post requests
std::string Responder::POSTRequest(Request &request)
{
    return std::string();
}

std::string Responder::GETRequest(Request &request)
{
    std::string mainPageString;
    if (request.path == "/" || request.path == "index.html") {
        mainPageString = mainPage();
    } else if (request.path == "/favicon.ico") {
        printf("requested favicon");
    } else {
        std::ifstream myFile("../error.html");
        std::stringstream stream;
        std::string text;

        while (getline(myFile, text)) {
            stream << text;
        }
        mainPageString = stream.str();
    }

    return httpOK() + mainPageString;
}

std::string Responder::mainPage()
{
    auto info = RequestParser::extractor->getGeneralInfo();

    std::ifstream myFile("../index.html");
    std::stringstream stream;
    std::string text;

    while (getline(myFile, text)) {
        stream << text;
    }

    text = stream.str();

    std::string delimiter = "<table>";
    size_t pos = text.find(delimiter);

    std::string table;
    std::string rowElements1[2] = { "Napätie:", std::to_string(info->batteryVoltage) };
    addRow(table, 2, rowElements1);
    std::string rowElements2[2] = { "Záťaž:", std::to_string(info->acOutputActivePower) + "W" };
    addRow(table, 2, rowElements2);
    std::string rowElements3[2] = { "Záťaž v percentách:", std::to_string(info->outputLoadPercent) + "%" };
    addRow(table, 2, rowElements3);

    text.insert(pos + delimiter.size(), table);

    return text;
}
void Responder::addRow(std::string &fileSoFar, size_t cellN, std::string *rowElement)
{
    std::stringstream stream;
    stream << "<tr>\n";
    for (size_t i = 0; i < cellN; i++) {
        stream << "<td>" + rowElement[i] + "</td>\n";
    }
    stream << "</tr>";

    fileSoFar = fileSoFar + stream.str();
}
std::string Responder::httpOK()
{
    return "HTTP/2 200 OK\ncontent-type: text/html; charset=utf-8\n\n";
}

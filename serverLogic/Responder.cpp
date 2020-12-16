//
// Created by Michal on 15-Dec-20.
//

#include "Responder.h"
#include <fstream>
#include <sstream>
#include "../File.h"
#include "Response.h"

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

//int loadFile(char ** buffer, )
//todo you will need to change return type of this function because image requests wont work otherwise
std::string Responder::GETRequest(Request &request)
{
    std::string response;
    if (request.path == "/") {
        request.path = "../index.html";
    } else {
        request.path = ".." + request.path;
    }

    try {
        File file = File(request.path);

        if (file.getFileType() == "html" || file.getFileType() == "css") {
            Response responseObj = Response(HTTP200, "text/" + file.getFileType(), "", "");
            if (request.path == "../index.html") {
                responseObj.changeBody(mainPage(file.getFileAsString()));
                response = responseObj.getStringResponse();
            } else {
                responseObj.changeBody(file.getFileAsString());
                response = responseObj.getStringResponse();
            }

        } else if (file.getFileType() == "png" || file.getFileType() == "jpg") {
            Response responseObj = Response(HTTP200, "image/" + file.getFileType(), "", "");
            response = responseObj.getStringResponse();
        }

    } catch (FileException &e) {
        std::string err = "../error.html";
        File noPage = File(err);

        Response responseObj = Response(HTTP404, "text/html", "", noPage.getFileAsString());
        response = responseObj.getStringResponse();
    }

    std::cout << response;
    return response;
}

std::string Responder::mainPage(std::string text)
{
    auto info = RequestParser::extractor->getGeneralInfo();

    std::string delimiter = "<table>";
    size_t pos = text.find(delimiter);

    std::string table;
    std::string rowElements1[2] = { "Napätie:", std::to_string(info->batteryVoltage) + " V" };
    addRow(table, 2, rowElements1);
    std::string rowElements2[2] = { "Záťaž:", std::to_string(info->acOutputActivePower) + " W" };
    addRow(table, 2, rowElements2);
    std::string rowElements3[2] = { "Záťaž v percentách:", std::to_string(info->outputLoadPercent) + "%" };
    addRow(table, 2, rowElements3);

    text.insert(pos + delimiter.length(), table);

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

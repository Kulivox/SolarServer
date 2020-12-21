//
// Created by Michal on 15-Dec-20.
//

#include "ResponseManager.h"
#include <fstream>
#include <sstream>
#include "../../File.h"
#include "Response.h"

std::string ResponseManager::respond(Request &request)
{
    std::string result;

    if (request.type == "GET") {
        result = GETRequest(request);
    }
    return result;
}

//todo create function for post requests
std::string ResponseManager::POSTRequest(Request &request)
{
    return std::string();
}

//int loadFile(char ** buffer, )
//todo you will need to change return type of this function because image requests wont work otherwise
std::string ResponseManager::GETRequest(Request &request)
{
    std::string strResponse = std::string();
    std::string optionalParams = std::string();
    std::string body = std::string();
    std::string fileType = std::string();

    //this will create correct path to the website files, necessary for correct function
    request.path = ResponseManager::options.serverFilesPath + "/" + request.path;

    try {
        File file = File(request.path);

        fileType = file.getFileType();
        Response response = Response(HTTP200, fileType, optionalParams, body);

        if (request.path.find("index.html") != std::string::npos) {
            body = mainPage(file.getFileAsString());
            response.changeBody(body);
        } else {
            body = file.getFileAsString();
            response.changeBody(body);
        }

        strResponse = response.getStringResponse();

    } catch (FileException &e) {
        std::string err = "error.html";
        File noPage = File(err);
        std::string type = noPage.getFileType();
        body = noPage.getFileAsString();

        Response response = Response(HTTP404, type, optionalParams, body);
        strResponse = response.getStringResponse();
    }

    //    std::cout << strResponse;
    return strResponse;
}

std::string ResponseManager::mainPage(std::string text)
{
    auto info = InverterDataExtractor::getGeneralInfo();

    std::string delimiter = "<table>";
    size_t pos = text.find(delimiter);

    std::string table;
    std::string voltage[2] = { "Napätie:", std::to_string(info->batteryVoltage) + " V" };
    addRow(table, 2, voltage);
    std::string acOutputpower[2] = { "Záťaž:", std::to_string(info->acOutputActivePower) + " W" };
    addRow(table, 2, acOutputpower);
    std::string outputLoadPercent[2] = { "Záťaž v percentách:", std::to_string(info->outputLoadPercent) + "%" };
    addRow(table, 2, outputLoadPercent);
    std::string pvOutputPower[2] = { "Výkon panelov: ", std::to_string(info->pvInputCurrentBattery * info->pvInputVoltage1) };
    addRow(table, 2, pvOutputPower);

    text.insert(pos + delimiter.length(), table);

    return text;
}
void ResponseManager::addRow(std::string &fileSoFar, size_t cellN, std::string *rowElement)
{
    std::stringstream stream;
    stream << "<tr>\n";
    for (size_t i = 0; i < cellN; i++) {
        stream << "<td>" + rowElement[i] + "</td>\n";
    }
    stream << "</tr>";

    fileSoFar = fileSoFar + stream.str();
}
std::string ResponseManager::httpOK()
{
    return "HTTP/2 200 OK\ncontent-type: text/html; charset=utf-8\n\n";
}
ResponseManager::ResponseManager(ProgramOptions &opt)
{
    options = opt;
}

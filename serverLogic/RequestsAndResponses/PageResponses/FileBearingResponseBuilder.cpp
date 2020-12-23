//
// Created by Michal on 23-Dec-20.
//

#include "FileBearingResponseBuilder.h"

Response *FileBearingResponseBuilder::buildFileBearingResponse(Request &request, ProgramOptions *options)
{
    std::string optionalParams = std::string();
    std::string body = std::string();
    std::string fileType = std::string();

    if (request.path == "/") {
        request.path = "/index.html";
    }

    //this will add user defined path prefix to the path of requested file

    request.path = options->serverFilesPath + request.path;

    try {
        File file(request.path);
        fileType = file.getFileType();
        auto *response = new Response(HTTP200, fileType, optionalParams, file.getFileAsPointerToBytes(), file.getFileSize());
        return response;

    } catch (FileException &exception) {
        std::string err = options->serverFilesPath + "/error.html";
        File noPage(err);
        std::string type = noPage.getFileType();
        body = noPage.getFileAsString();
        auto *response = new Response(HTTP404, type, optionalParams, body);
        return response;
    }
}

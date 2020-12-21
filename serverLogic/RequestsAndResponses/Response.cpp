//
// Created by Michal on 16-Dec-20.
//

#include "Response.h"
#include <sstream>
#include <exception>

Response::Response(HTTPCodes code, std::string &type, std::string &optionalParams, std::string &body)
{
    MIMETypes["html"] = "text/html";
    MIMETypes["css"] = "text/css";
    MIMETypes["jpg"] = "images/jpg";
    MIMETypes["png"] = "images/png";
    MIMETypes["js"] = "text/javascript";
    MIMETypes["ico"] = "image/png";

    std::stringstream response;
    switch (code) {
    case HTTP200:
        response << "HTTP/2 200 OK\n";
        codeString = response.str();
        break;
    case HTTP500:
        response << "HTTP/2 500 Internal Server Error\n";
        codeString = response.str();
        break;
    case HTTP404:
        response << "HTTP/2 404 Not Found\n";
        codeString = response.str();
        break;
    }

    MIMETypeString = "content-type: " + MIMETypes[type] + "; charset=utf-8\n";
    optionalString = optionalParams + "\n\n";
    bodyString = body + "\n";

    response << MIMETypeString << optionalString << bodyString;
    responseString = response.str();
    responseLength = responseString.length();
    responseBytes = responseString.c_str();
}
std::string Response::getStringResponse()
{
    return responseString;
}
void Response::changeBody(std::string newBody)
{
    bodyString = newBody;
    std::stringstream response;
    response << codeString << MIMETypeString << optionalString << "\n"
             << newBody;
    responseString = response.str();
    responseBytes = responseString.c_str();
}

//todo finish this constructor
Response::Response(HTTPCodes code, std::string &type, std::string &optionalParams, char *body, size_t bodyLen)
{
    MIMETypes["html"] = "text/html";
    MIMETypes["css"] = "text/css";
    MIMETypes["jpg"] = "images/jpg";
    MIMETypes["png"] = "images/jpg";
    MIMETypes["js"] = "text/javascript";

    std::stringstream response;
    switch (code) {
    case HTTP200:
        response << "HTTP/2 200 OK\n";
        codeString = response.str();
        break;
    case HTTP500:
        response << "HTTP/2 500 Internal Server Error\n";
        codeString = response.str();
        break;
    case HTTP404:
        response << "HTTP/2 404 Not Found\n";
        codeString = response.str();
        break;
    default:
        response << "HTTP/2 404 Not Found\n";
        codeString = response.str();
    }

    MIMETypeString = "content-type: " + MIMETypes[type] + "; charset=utf-8\n";
    optionalString = optionalParams + "\n\n";
    bodyString = std::string(body) + "\n";

    response << MIMETypeString << optionalString << bodyString;
    responseString = response.str();
}

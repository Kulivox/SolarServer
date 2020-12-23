//
// Created by Michal on 16-Dec-20.
//

#include <exception>
#include "Response.h"
#include <cstring>

Response::Response(HTTPCodes code, std::string &type, std::string &optionalParams, std::string &body)
{
    std::stringstream responseStringStream;
    MIMETypes["html"] = "text/html; charset=utf-8\n";
    MIMETypes["css"] = "text/css; charset=utf-8\n";
    MIMETypes["jpg"] = "images/jpg";
    MIMETypes["png"] = "images/png";
    MIMETypes["ico"] = "images/png";
    MIMETypes["js"] = "text/javascript; charset=utf-8\n";

    switch (code) {
    case HTTP200:
        responseStringStream << "HTTP/2 200 OK\n";
        codeString = responseStringStream.str();
        break;
    case HTTP500:
        responseStringStream << "HTTP/2 500 Internal Server Error\n";
        codeString = responseStringStream.str();
        break;
    case HTTP404:
        responseStringStream << "HTTP/2 404 Not Found\n";
        codeString = responseStringStream.str();
        break;
    default:
        responseStringStream << "HTTP/2 404 Not Found\n";
        codeString = responseStringStream.str();
    }

    MIMETypeString = "content-type: " + MIMETypes[type];
    optionalString = optionalParams + "\n\n";
    bodyString = body + "\n";

    responseStringStream << MIMETypeString << optionalString << bodyString;
    responseString = responseStringStream.str();
    responseLength = responseString.length();
    response = new char[responseLength];
    memcpy(response, responseString.c_str(), responseLength);
}

Response::Response(HTTPCodes code, std::string &type, std::string &optionalParams, const char *body, size_t bodyLen)
{
    MIMETypes["html"] = "text/html; charset=utf-8\n";
    MIMETypes["css"] = "text/css; charset=utf-8\n";
    MIMETypes["jpg"] = "images/jpg";
    MIMETypes["png"] = "images/png";
    MIMETypes["ico"] = "images/png";
    MIMETypes["js"] = "text/javascript; charset=utf-8\n";

    std::stringstream responseStringStream;

    switch (code) {
    case HTTP200:
        responseStringStream << "HTTP/2 200 OK\n";
        codeString = responseStringStream.str();
        break;
    case HTTP500:
        responseStringStream << "HTTP/2 500 Internal Server Error\n";
        codeString = responseStringStream.str();
        break;
    case HTTP404:
        responseStringStream << "HTTP/2 404 Not Found\n";
        codeString = responseStringStream.str();
        break;
    default:
        responseStringStream << "HTTP/2 404 Not Found\n";
        codeString = responseStringStream.str();
    }

    MIMETypeString = "content-type: " + MIMETypes[type];
    optionalString = optionalParams + "\n\n";

    responseStringStream << MIMETypeString << optionalString;
    size_t streamLen = codeString.length() + MIMETypeString.length() + optionalString.length();
    responseLength = streamLen + bodyLen;

    response = new char[responseLength + 1];
    memcpy(response, responseStringStream.str().c_str(), streamLen);

    char *tempResponsePointer = response + streamLen;
    memcpy(tempResponsePointer, body, bodyLen);
    response[responseLength] = '\0';
    responseString = response;
}

std::string Response::getStringResponse()
{
    return responseString;
}

char *Response::getResponseBuffer()
{
    return response;
}

void Response::changeBody(std::string newBody)
{
    std::stringstream responseStringStream;
    bodyString = newBody;
    responseStringStream << codeString << MIMETypeString << optionalString << "\n"
                         << newBody;
    responseString = responseStringStream.str();
}

void Response::changeBody(const char *newBody, size_t len)
{
    std::stringstream responseStringStream;
    responseStringStream << codeString << MIMETypeString << optionalString;

    size_t streamLen = codeString.length() + MIMETypeString.length() + optionalString.length();
    responseLength = streamLen + len;

    delete response;
    response = new char[responseLength + 1];
    memcpy(response, responseStringStream.str().c_str(), streamLen);

    char *tempResponsePointer = response + streamLen;
    memcpy(tempResponsePointer, newBody, len);

    response[responseLength] = '\0';
    responseString = response;
}
size_t Response::getResponseLength()
{
    return responseLength;
}

//
// Created by Michal on 16-Dec-20.
//

#ifndef SOLARSERVER_RESPONSE_H
#define SOLARSERVER_RESPONSE_H
#include <iostream>
#include <sstream>
#include <map>

enum HTTPCodes
{
    HTTP200 = 200,
    HTTP404 = 404,
    HTTP500 = 500
};

class Response
{
  private:
    std::string responseString;
    std::string codeString;
    std::string MIMETypeString;
    std::string optionalString;
    std::string bodyString;
    char *response;
    size_t responseLength;

    std::map<std::string, std::string> MIMETypes;

  public:
    Response(HTTPCodes code, std::string &type, std::string &optionalParams, std::string &body);
    Response(HTTPCodes code, std::string &type, std::string &optionalParams, const char *body, size_t bodyLen);
    std::string getStringResponse();
    char *getResponseBuffer();
    void changeBody(std::string newBody);
    void changeBody(const char *newBody, size_t len);
    size_t getResponseLength();
};

#endif //SOLARSERVER_RESPONSE_H

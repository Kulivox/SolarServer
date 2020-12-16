//
// Created by Michal on 16-Dec-20.
//

#ifndef SOLARSERVER_RESPONSE_H
#define SOLARSERVER_RESPONSE_H
#include <iostream>
enum HTTPCodes
{
    HTTP200,
    HTTP404,
    HTTP500
};

class Response
{
  private:
    std::string responseString;
    std::string codeString;
    std::string MIMETypeString;
    std::string optionalString;
    std::string bodyString;
    const char *responseBytes;
    size_t responseLength;

  public:
    Response(HTTPCodes code, std::string MIMEType, std::string optionalParams, std::string body);
    Response(HTTPCodes code, std::string MIMEType, std::string optionalParams, char *body, size_t bodyLen);
    std::string getStringResponse();
    void changeBody(std::string newBody);
};

#endif //SOLARSERVER_RESPONSE_H

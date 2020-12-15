#include "inverterComm.h"
#include "serverLogic/ServerInstance.h"
#include "UI/UserInterface.h"
#include "serverLogic/RequestParser.h"
#include "inveterExtractor/InverterDataExtractor.h"

InverterDataExtractor *RequestParser::extractor;

int main()
{
    InverterDataExtractor extractor = InverterDataExtractor();
    UserInterface interface = UserInterface(extractor.getTID());

    RequestParser::extractor = &extractor;

    ServerInstance instance = ServerInstance("192.168.1.20", 8005);

    instance.start(UserInterface::getRunPointer(), extractor);

    return 0;
}

#include <iostream>
#include "inverterComm.h"
#include "ServerInstance.h"
#include "UIThread.h"
#include "RequestParser.h"
#include "InverterDataExtractor.h"

InverterDataExtractor *RequestParser::extractor;

int main()
{
    UIThread thread = UIThread();
    InverterDataExtractor extractor = InverterDataExtractor(UIThread::getRunPointer());
    RequestParser::extractor = &extractor;

    ServerInstance instance = ServerInstance("192.168.1.20", 8089);

    instance.start(UIThread::getRunPointer(), extractor);

    return 0;
}

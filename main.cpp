#include <iostream>
#include "inverterComm.h"
#include "ServerInstance.h"
#include "UIThread.h"
#include "InverterDataExtractor.h"
int main()
{
    UIThread thread = UIThread();
    InverterDataExtractor extractor = InverterDataExtractor(UIThread::getRunPointer());
    ServerInstance instance = ServerInstance("192.168.1.20", 8089);

    instance.start(UIThread::getRunPointer(), extractor);

    return 0;
}

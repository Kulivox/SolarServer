#include "inverterComm.h"
#include "serverLogic/ServerInstance.h"
#include "UI/UserInterface.h"
#include "serverLogic/RequestsAndResponses/RequestParser.h"
#include "inveterExtractor/InverterDataExtractor.h"
#include "File.h"
#include <map>

void loadArgs(ProgramOptions *options, int argc, char **argv)
{
    //todo change this to getopt()
    if (argc <= 1 || argc > 2) {
        std::cerr << "Incorrect number of args\n";
        exit(1);
    }

    options->serverFilesPath = std::string(argv[1]);
}

int main(int argc, char **argv)
{
    InverterDataExtractor extractor = InverterDataExtractor();
    UserInterface interface = UserInterface(extractor.getTID());

    ProgramOptions options;
    loadArgs(&options, argc, argv);

    ServerInstance instance = ServerInstance("192.168.1.20", 8888, options);

    instance.start(UserInterface::getRunPointer(), extractor);

    return 0;
}

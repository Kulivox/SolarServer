//
// Created by Michal on 08-Dec-20.
//

#include "ServerInstance.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <cerrno>
#include "../inveterExtractor/InverterDataExtractor.h"
#include "Responder.h"
#include "RequestParser.h"

struct ThreadData
{
    int sockFD;
    InverterDataExtractor *extractor;
};

ServerInstance::ServerInstance(const std::string &address, uint16_t port)
{
    this->sockFD = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFD < 0) {
        Logger::log(true, "ServerInstance", "socket creation, exiting");
        exit(1);
    }

    auto *serverAddr = (sockaddr_in *) calloc(1, sizeof(sockaddr_in));
    serverAddr->sin_family = AF_INET;
    serverAddr->sin_addr.s_addr = inet_addr(address.c_str());
    serverAddr->sin_port = htons(port);

    if (bind(this->sockFD, (struct sockaddr *) serverAddr, sizeof(sockaddr_in)) < 0) {
        Logger::log(true, "ServerInstance", "could not bind socket, exiting");
        exit(1);
    }
}
int ServerInstance::start(bool *run, InverterDataExtractor &extractor)
{
    if (listen(this->sockFD, 5) != 0) {
        Logger::log(true, "ServerInstance", "listening on socket was not successful");
        exit(1);
    }

    int status = fcntl(this->sockFD, F_SETFL, fcntl(this->sockFD, F_GETFL, 0) | O_NONBLOCK);
    if (status < 0) {
        Logger::log(true, "ServerInstance", "fcntl error");
        exit(1);
    }

    uint16_t runningThreads = 0;
    const uint16_t MAX_THREADS = 5;
    pthread_t threadIDs[MAX_THREADS] = { 0 };

    // run is pointer shared between server thread and UI thread, if user wishes to stop the server, UI thread will change the value of run which will cause this loop to end
    while (true) {
        if (!*run) {
            break;
        }

        auto *clientAddr = (sockaddr_in *) calloc(1, sizeof(sockaddr_in));
        size_t addrSize = sizeof(sockaddr_in);

        // this loop limits the number of concurrently processed requests, it will block until at least one thread ends
        while (runningThreads >= MAX_THREADS) {
            for (unsigned long threadID : threadIDs) {
                int32_t *retVal;
                if (pthread_tryjoin_np(threadID, (void **) &retVal) == 0) {
                    runningThreads--;
                }
            }
        }
        int childFD = accept(sockFD, (struct sockaddr *) clientAddr, (socklen_t *) &addrSize);

        if (childFD < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
            continue;
        }

        int8_t buff[INET_ADDRSTRLEN + 1] = { 0 };
        inet_ntop(AF_INET, &(clientAddr->sin_addr), (char *) buff, INET_ADDRSTRLEN);
        Logger::log(false, "ServerInstance, client connecting", "IP:" + std::string((char *) buff));
        free(clientAddr);

        auto *data = new ThreadData{ childFD, &extractor };

        //        ThreadData data = {childFD, &extractor};

        if (pthread_create(&threadIDs[runningThreads], nullptr, ServerInstance::startProcessing, (void *) data) != 0) {
            Logger::log(true, "ServerInstance", "thread creation failed.");
            exit(1);
        }

        runningThreads += 1;
    }

    for (unsigned long threadID : threadIDs) {
        pthread_join(threadID, nullptr);
    }

    close(this->sockFD);
    return 0;
}

void *ServerInstance::startProcessing(void *arg)

{
    auto data = (ThreadData *) arg;
    auto sockFD = data->sockFD;
    Responder responder = Responder();

    size_t maxRequestSize = 1u << 20u;
    auto *buffer = (int8_t *) calloc(maxRequestSize, sizeof(int8_t));

    int32_t result = read(sockFD, buffer, maxRequestSize - 1);
    if (result <= 0) {
        Logger::log(false, "Server Instance: Processing", "could not read from socket / no data");
        close((int32_t) sockFD);
        return (void *) 1;
    }

    //    printf("BUFFER: %s\n", buffer);

    Request req = RequestParser::parseRequest(buffer);
    std::string response = responder.respond(req);
    free(buffer);

    if (write(sockFD, response.c_str(), response.length()) != response.length()) {
        Logger::log(false, "ServerInstance: Processing", "could not respond, connection closed at clients side");
        close((int32_t) sockFD);
        return (void *) 1;
    }

    delete data;
    close(sockFD);
    return (void *) 0;
}

ServerInstance::~ServerInstance()
{
    close(this->sockFD);
}
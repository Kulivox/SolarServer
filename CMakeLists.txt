cmake_minimum_required(VERSION 3.6)
project(SolarServer)

set(CMAKE_CXX_STANDARD 14)
add_executable(SolarServer main.cpp serverLogic/ServerInstance.cpp Logger/Logger.cpp
        serverLogic/RequestsAndResponses/RequestParser.cpp
        UI/UserInterface.cpp
        inveterExtractor/InverterDataExtractor.cpp
        DataStorage/DataStorage.cpp
        serverLogic/RequestsAndResponses/ResponseBufferBuilder.cpp
        serverLogic/RequestsAndResponses/Response.cpp
        File.cpp File.h tests/tests.cpp tests/RequestParserTests.cpp tests/RequestParserTests.h
        serverLogic/RequestsAndResponses/PageResponses/FileBearingResponseBuilder.cpp
        serverLogic/RequestsAndResponses/QueryResponses/MainPage/MainPageBuilder.cpp
        serverLogic/RequestsAndResponses/QueryResponses/QueryResponseBuilder.cpp
        serverLogic/RequestsAndResponses/QueryResponses/MainPageChart/MainPageChartDataBuilder.cpp)


target_link_libraries(SolarServer SolarConverterConnectionLib -pthread)
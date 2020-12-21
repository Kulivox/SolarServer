cmake_minimum_required(VERSION 3.6)
project(SolarServer)

set(CMAKE_CXX_STANDARD 14)
add_executable(SolarServer main.cpp serverLogic/ServerInstance.cpp Logger/Logger.cpp Logger/Logger.h serverLogic/RequestsAndResponses/RequestParser.cpp serverLogic/RequestsAndResponses/RequestParser.h inveterExtractor/InverterDataExtractor.cpp inveterExtractor/InverterDataExtractor.h UI/UserInterface.cpp UI/UserInterface.h DataStorage/DataStorage.cpp DataStorage/DataStorage.h serverLogic/RequestsAndResponses/ResponseManager.cpp serverLogic/RequestsAndResponses/ResponseManager.h serverLogic/RequestsAndResponses/Response.cpp serverLogic/RequestsAndResponses/Response.h File.cpp File.h)
target_link_libraries(SolarServer SolarConverterConnectionLib -pthread)
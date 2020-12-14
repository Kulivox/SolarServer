cmake_minimum_required(VERSION 3.6)
project(SolarServer)

set(CMAKE_CXX_STANDARD 14)
add_executable(SolarServer main.cpp ServerInstance.cpp Logger.cpp Logger.h RequestParser.cpp RequestParser.h InverterDataExtractor.cpp InverterDataExtractor.h UIThread.cpp UIThread.h)
target_link_libraries(SolarServer SolarConverterConnectionLib -pthread)
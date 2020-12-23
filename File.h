//
// Created by Michal on 16-Dec-20.
//

#ifndef SOLARSERVER_FILE_H
#define SOLARSERVER_FILE_H

#include <string>
#include <exception>

class FileException : std::exception
{
};

class File
{
  private:
    std::string name;
    std::string type;
    size_t size;
    char *contents;
    std::string extractTypeFromFileName();

  public:
    explicit File(std::string path);
    std::string getFileAsString();
    char *getFileAsPointerToBytes();
    size_t getFileSize();
    std::string getFileType();
    std::string getFileName();
    ~File();
};

#endif //SOLARSERVER_FILE_H

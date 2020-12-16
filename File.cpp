//
// Created by Michal on 16-Dec-20.
//

#include "File.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

size_t File::getFileSize()
{
    return size;
}

File::File(std::string path)
{
    std::ifstream file(path, std::ifstream::binary);
    if (file.fail()) {
        throw FileException();
    }

    std::streampos begin, end;
    begin = file.tellg();
    file.seekg(0, std::ios::end);
    end = file.tellg();

    size = end - begin;
    file.seekg(0);
    name = path;
    type = extractTypeFromFileName();
    if (type.empty()) {
        throw FileException();
    }

    contents = new char[size + 1];
    file.read(contents, size);
    contents[size] = '\0';
}

std::string File::extractTypeFromFileName()
{
    std::string result;
    for (size_t i = name.length() - 1; name[i] != '/'; i--) {
        if (name[i] == '.' && i - 1 >= 0 && name[i - 1] != '/') {
            std::reverse(result.begin(), result.end());
            return result;
        }
        result += name[i];
    }

    return "";
}

std::string File::getFileType()
{
    return type;
}
std::string File::getFileName()
{
    return name;
}
char *File::getFileAsPointerToBytes()
{
    return contents;
}
std::string File::getFileAsString()
{
    return std::string(contents);
}

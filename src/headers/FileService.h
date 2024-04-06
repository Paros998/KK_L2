//
// Created by part4 on 13.03.2024.
//

#ifndef FILEREADER_H
#define FILEREADER_H

#include "Libraries.h"
#include "Arguments.h"

namespace files {
class FileService {
public:
    static int readKey(const char* file);

    static std::ifstream getInputHandle(const char* file);

    static std::ofstream getOutputHandle(const char* file);
};

} // files

#endif //FILEREADER_H

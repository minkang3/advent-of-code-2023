#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include "pipes.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

PipeMatrix parse_file(const std::string& file_name) {
    PipeMatrix mat;
    std::ifstream in{file_name};
    std::string line;

    while (std::getline(in, line)) {
        mat.add_line(line);
    }
    return mat;
}

#endif

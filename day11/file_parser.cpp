#ifndef FILE_PARSER_CPP
#define FILE_PARSER_CPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> parse_file_to_matrix(std::string file_name) {
    std::ifstream in{file_name};
    std::vector<std::string> matrix;

    std::string line;
    while (std::getline(in, line)) {
        matrix.push_back(line);
    }
    return matrix;
}

#endif

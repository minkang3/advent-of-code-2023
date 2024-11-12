#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <vector>
#include <regex>

#include "readings.h"

std::vector<int32_t> parse_line_to_vec(const std::string&);

Readings parse_file(std::string file_name) {
    Readings readings;
    std::ifstream in{file_name};
    std::string line;

    while (std::getline(in, line)) {
        std::vector<int32_t> val_history = parse_line_to_vec(line);
        readings.push_back(val_history);
    }
    return readings;
}

std::vector<int32_t> parse_line_to_vec(const std::string& line) {
    std::vector<int32_t> result;
    std::regex re(R"( )");
    std::sregex_token_iterator it{line.begin(), line.end(), re, -1}, end;

    for (; it != end; ++it) {
        result.emplace_back(std::stoi(*it));
    }
    return result;
}

#endif

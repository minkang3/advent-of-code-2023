#ifndef FILE_PARSER_CPP
#define FILE_PARSER_CPP

#include "hand.cpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

Hand parse_line_to_hand(std::string line);

std::vector<Hand> parse_file(std::string file_name) {
    std::vector<Hand> hands;
    std::ifstream in{file_name};
    std::string line;

    while (std::getline(in, line)) {
        hands.push_back(parse_line_to_hand(line));
    }
    return hands;
}

Hand parse_line_to_hand(std::string line) {
    std::istringstream iss{line};
    std::string cards, bid;
    iss >> cards >> bid;
    Hand result{cards, std::stoi(bid)};

    return result;
}

#endif

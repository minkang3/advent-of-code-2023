#ifndef FILE_PARSER_CPP
#define FILE_PARSER_CPP

#include "dir_map.cpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>

std::pair<std::string, Node>
parse_line_to_node(std::string line);

DirMap parse_file(std::string file_name) {
    DirMap dir_map;
    std::ifstream in{file_name};
    std::string line;

    std::getline(in, dir_map.LR_instructions);
    std::getline(in, line); // voids empty line

    //while (std::getline(in, line)) {

    //}
    while (std::getline(in, line)) {
        std::pair<std::string, Node> key_node_pair = parse_line_to_node(line);
        dir_map.node_network.insert(key_node_pair);
    }
    return dir_map;
}

std::pair<std::string, Node>
parse_line_to_node(std::string line) {
    //std::regex re(R"([\s=(),]+)");
    std::regex re(R"([A-Z1-9]+)");
    std::sregex_token_iterator it{line.begin(), line.end(), re, 0};

    std::string key = *it;
    std::string left = *++it;
    std::string right = *++it;
    Node node{left, right};

    return {key, node};
}









#endif

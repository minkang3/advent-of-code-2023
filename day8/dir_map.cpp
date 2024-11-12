#ifndef DIR_MAP_CPP
#define DIR_MAP_CPP

#include "lcm.cpp"

#include <iostream>
#include <string>
#include <unordered_map>
#include <regex>

struct Node {
    std::string left, right;
};

struct DirMap {
    std::string LR_instructions;
    std::unordered_map<std::string, Node> node_network;

    int follow_instructions() {
        int i = 0;
        int num_steps = 0;
        bool found = false;
        std::string location = "AAA";
        while (!found) {
            Node directions = node_network[location];
            char inst = LR_instructions[i];
            if (inst == 'L')
                location = directions.left;
            else if (inst == 'R')
                location = directions.right;
            else
                throw "Not L or R instruction";

            ++num_steps;

            if (location == "ZZZ")
                found = true;

            i = (i + 1) % LR_instructions.length();
        }
        return num_steps;
    }

    std::vector<std::string>
    initialize_ghost_positions() {
        std::vector<std::string> positions; 
        std::regex pattern(R"(..A)");
        for (auto e : node_network) {
            if (std::regex_match(e.first, pattern)) {
                positions.push_back(e.first);
            }
        }
        return positions;
    }


    size_t follow_instructions_as_ghost() {
        std::vector<std::string> start_positions = initialize_ghost_positions();
        std::vector<size_t> num_steps_per_pos(start_positions.size(), 0);

        int instruction_size = LR_instructions.size();

        for (int pos_index = 0; pos_index < start_positions.size(); ++pos_index) {
            std::string location = start_positions[pos_index];
            bool found = false;

            int num_steps = 0;
            int i = 0;
            while (!found) {
                Node directions = node_network[location];
                char inst = LR_instructions[i];
                if (inst == 'L')
                    location = directions.left;
                else if (inst == 'R')
                    location = directions.right;
                else
                    throw "Not L or R";

                ++num_steps;

                if (location[2] == 'Z')
                    found = true;

                i = (i+1) % instruction_size;
            }
            num_steps_per_pos[pos_index] = num_steps;
        }
        return lcm_all(num_steps_per_pos);
    }


    void test_map() {
        std::string loc = "AAA";
        Node directions = node_network[loc];
        std::cout << loc << ": " << directions.left << ' ' << directions.right << '\n';

        loc = directions.left;
        directions = node_network[loc];
        std::cout << loc << ": " << directions.left << ' ' << directions.right << '\n';

        loc = directions.left;
        directions = node_network[loc];
        std::cout << loc << ": " << directions.left << ' ' << directions.right << '\n';

        loc = directions.right;
        directions = node_network[loc];
        std::cout << loc << ": " << directions.left << ' ' << directions.right << '\n';

        loc = directions.left;
        directions = node_network[loc];
        std::cout << loc << ": " << directions.left << ' ' << directions.right << '\n';

        loc = directions.left;
        directions = node_network[loc];
        std::cout << loc << ": " << directions.left << ' ' << directions.right << '\n';

        loc = directions.right;
        directions = node_network[loc];
        std::cout << loc << ": " << directions.left << ' ' << directions.right << '\n';

        if (loc == "ZZZ")
            std::cout << "Success!\n";
    }
};






#endif

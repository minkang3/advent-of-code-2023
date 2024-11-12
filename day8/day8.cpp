#include "file_parser.cpp"

#include <iostream>

int main() {

//    std::vector<std::string> positions{"BLZ", "LXZ", "RLZ", "BLZ", "CMZ", "LXZ", "ZZZ", "BBB"};
//    bool found = true;
//    for (std::string& pos : positions) {
//        if (pos[2] != 'Z')
//            found = false;
//    }
//    std::cout << std::boolalpha << found << '\n';

    
    DirMap dir_map = parse_file("input.txt");
    //DirMap dir_map = parse_file("ghost_test_input.txt");

    size_t num_steps = dir_map.follow_instructions_as_ghost();

    std::cout << "Number of steps: " << num_steps << '\n';
    
}

#include "file_parser.h"

#include <iostream>

void recursiveFunction(int count) {
    std::cout << "Recursion depth: " << count << std::endl;
    recursiveFunction(count + 1);
}

/*
int main() {
    try {
        recursiveFunction(1);
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
*/


int main() {
    //PipeMatrix mat = parse_file("test_pipes_2.txt");
    PipeMatrix mat = parse_file("input.txt");
    for (auto s : mat.per_matrix) {
        std::cout << s << '\n';
    }
    std::cout << '\n';
    for (std::string line : mat ) {
        std::cout << line << '\n';
    }
    mat.find_start_pos();
    std::cout << "Starting Pos: (" << mat.posX << ", " << mat.posY << ")" << '\n';
    try {
        int steps = mat.find_steps_to_furthest_pipe();
        std::cout << "Num Steps: " << steps << '\n';
    } catch (std::string s) {
        std::cerr << "Error: " << s << '\n';
    }
    mat.output_per_mat_to_file("output.txt");
}


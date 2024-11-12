#include <iostream>
#include <fstream>
#include <string>


bool isNum(char c) {
    return (48 <= c && c <= 57);
}

int parse_file(std::string file_name) {
    std::ifstream in{file_name};
    std::string line;
    int sum;
    while (std::getline(in, line)) {
        auto l = line.begin();
        auto r = --line.end();

//        while (!isNum(*l) && !isNum(*r)) {
//            if (!(48 <= *l && *l <= 57))
//                ++l;
//            if (!(48 <= *r && *r <= 57))
//                --r;
//        }

        while (!isNum(*l))
            ++l;
        while (!isNum(*r))
            --r;
        
        if (!isNum(*l) || !isNum(*r))
            continue;

        sum += (*l-48) * 10 + (*r-48);
    }
    return sum;
}


int main() {
    int result = parse_file("input.txt");
    std::cout << result << std::endl;
}

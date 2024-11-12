#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

bool isNum(char c) {
    return (48 <= c && c <= 57);
}

// {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"}
bool isStr(std::string::iterator it, std::string::iterator end, std::string needle) {
    // feel like there is more optimal way to check if it went to end of needle
    int i;
    for (i=0;i<needle.length()&&it!=end;++i, ++it) {
        if (*it != needle[i])
            return false;
    }
    if (i == needle.length())
        return true;
    else
        return false;
}

// Returns 0 if not found
int findNumAlpha(std::string::iterator it, std::string::iterator end) {
    std::map<std::string, int> numbers{
        {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, 
        {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}
    };
    for (auto [alp, num] : numbers) {
        if (isStr(it, end, alp))
            return num;
    }
    return 0;
}

int parse_file(std::string file_name) {
    std::ifstream in{file_name};
    std::string line;
    int sum = 0;
    while (std::getline(in, line)) {
//        auto l = line.begin();
//        auto r = --line.end();

//        while (!isNum(*l))
//            ++l;
//        while (!isNum(*r))
//            --r;
//        
//        if (!isNum(*l) || !isNum(*r))
//            continue;
//
//        sum += (*l-48) * 10 + (*r-48);
        int left_int;
        for (auto l=line.begin();l!=line.end();++l) {
            if (isNum(*l)) {
                left_int = *l - 48;
                break;
            } else if ( (left_int = findNumAlpha(l, line.end())) )
                break;
        }
        int right_int;
        for (auto r=line.end()-1;r>=line.begin();--r) {
            if (isNum(*r)) {
                right_int = *r - 48;
                break;
            } else if ( (right_int = findNumAlpha(r, line.end())) )
                break;
        }
        sum += left_int*10 + right_int;
    }
    return sum;
}


int main() {
    int result = parse_file("input.txt");
    std::cout << result << std::endl;
    
}

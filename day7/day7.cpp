#include "file_parser.cpp"
#include "hands_sorter.cpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>


int main() {
    std::vector<Hand> hands = parse_file("input.txt");
    
    sort_hands(hands);
    size_t total_winnings = 0;
    for (int i = 0; i < hands.size(); ++i) {
        total_winnings += hands[i].bid * (i+1);
    }
    std::cout << "Total Winnings: " << total_winnings << '\n';
}

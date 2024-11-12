#ifndef HANDS_SORTER_CPP
#define HANDS_SORTER_CPP

#include "hand.cpp"
#include <vector>
#include <algorithm>
#include <map>

std::map<char, int> map_card_strengths();

void sort_hands(std::vector<Hand>& hands) {
    std::map<char, int> card_strengths = map_card_strengths();
    auto greater_than = [&card_strengths](Hand h1, Hand h2) {
        //std::cout << "in greater than\n";
        if (h1.type != h2.type) {
            return h1.type < h2.type;
        }
        // Types Equal
        int hand_size = 5;
        for (int i = 0; i < hand_size; ++i) {
            char c1 = h1.cards[i], c2 = h2.cards[i];
            if (c1 == c2) 
                continue;
            return card_strengths[c1] < card_strengths[c2];
        }
        return false;
    };
    std::ranges::sort(hands, greater_than);
}

std::map<char, int> map_card_strengths() {
    std::map<char, int> card_strengths;
    card_strengths['J'] = 0;
    card_strengths['2'] = 1;
    card_strengths['3'] = 2;
    card_strengths['4'] = 3;
    card_strengths['5'] = 4;
    card_strengths['6'] = 5;
    card_strengths['7'] = 6;
    card_strengths['8'] = 7;
    card_strengths['9'] = 8;
    card_strengths['T'] = 9;
    card_strengths['Q'] = 10;
    card_strengths['K'] = 11;
    card_strengths['A'] = 12;

    return card_strengths;
}



#endif

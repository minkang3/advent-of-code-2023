#ifndef HAND_CPP
#define HAND_CPP

#include <iostream>
#include <string>
#include <map>

enum HandTypes {
    FIVE_KIND  = 6,
    FOUR_KIND  = 5,
    FULL_HOUSE = 4,
    THREE_KIND = 3,
    TWO_PAIR   = 2,
    ONE_PAIR   = 1,
    HIGH_CARD  = 0
};

struct Hand{
    std::string cards;
    int bid;
    int type;

    Hand(std::string cards, int bid)
    : cards(cards), bid(bid), type{get_type()} {}

    static void update_card_counts_with_joker(std::map<char, int>& card_counts);

    int get_type() {
        std::map<char, int> card_counts;
        for (char card : cards) {
            ++card_counts[card];
        }

        if (card_counts.find('J') != card_counts.end()) {
            //return get_type_with_joker(card_counts);
            update_card_counts_with_joker(card_counts);
        }
        int size = card_counts.size();
        if (size == 1) {
            return FIVE_KIND;
        }
        // Four of a Kind or Full House
        else if (size == 2) {
            auto [key, value] = *card_counts.begin();
            if (value == 4 || value == 1)
                return FOUR_KIND;
            else if (value == 3 || value == 2)
                return FULL_HOUSE;
            else
                throw "Not Four Kind or Full House";
        }
        else if (size == 3) {
            int num_pairs = 0;
            for (auto e : card_counts) {
                if (e.second == 3)
                    return THREE_KIND;
                else {
                    if (e.second == 2)
                        ++num_pairs;
                }
            }
            if (num_pairs == 2)
                return TWO_PAIR;
            else
                throw "Not three kind or two pair";
        }
        else if (size == 4)
            return ONE_PAIR;
        else
            return HIGH_CARD;
    }


    static void test_update_card_counts_with_joker() {
        std::string test_cards{"JJKKA"};
        std::map<char, int> card_counts;
        for (char card : test_cards) {
            ++card_counts[card];
        }
        update_card_counts_with_joker(card_counts);
        for (auto e : card_counts) {
            std::cout << e.first << ": " << e.second << '\n';
        }
    }


    friend std::ostream& operator<<(std::ostream& out, Hand h) {
        out << h.cards << ' ' << h.type;
        return out;
    }
};
void Hand::update_card_counts_with_joker(std::map<char, int>& card_counts) {
    auto it = card_counts.begin(), end = card_counts.end();
    while (it->first == 'J' && it != end)
        ++it;
    if (it == end) {
        return;
    }
    std::pair<char, int> most_freq_card = *it;
        for (++it; it != end; ++it) {
            if (it->first != 'J' && it->second > most_freq_card.second) {
                most_freq_card = *it;
            }
        }
    card_counts[most_freq_card.first] += card_counts['J'];
    card_counts.erase('J');
}
/*
bool Hands::is_five_kind() {
    for (int i=1; i<cards.length(); ++i) {
        if (cards[i] != cards[0])
            return false;
    }
    return true;
}

bool is_four_kind() {

}

bool is_full_house();
bool is_three_kind();
bool is_two_pair();
bool is_one_pair();

*/



#endif

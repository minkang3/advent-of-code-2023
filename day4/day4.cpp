#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>

struct Card {
    int card_id;
    std::vector<int> winning_nums;
    std::vector<int> nums;
    int points = 0;
};

std::vector<int> parse_number_str_to_vector(const std::string& number_str) {
    std::vector<int> result;
    std::istringstream iss{number_str};
    std::string int_str;

    while (iss >> int_str) {
        result.push_back(std::stoi(int_str));
    }
    return result;
}


void calculate_score(Card& card) {
    for (int num : card.nums) {
        if (std::find(card.winning_nums.begin(), card.winning_nums.end(), num) == card.winning_nums.end())
            continue;

        if (card.points == 0)
            card.points = 1;
        else
            card.points *= 2;
    }
}

int calc_num_matches(Card& card) {
    int matches = 0;
    for (int num : card.nums) {
        if (std::find(card.winning_nums.begin(),
                    card.winning_nums.end(), num) == card.winning_nums.end())
            continue;

        matches += 1;
    }
    return matches;
}

std::pair<std::vector<Card>, std::map<int, int>>
parse_file(std::string file_name) {
    std::vector<Card> card_vector;
    std::map<int, int> card_counts;
    std::ifstream in{file_name};
    std::string line;

    while (std::getline(in, line)) {
        Card card;
        std::istringstream iss{line};
        std::string id_as_str;

        iss >> id_as_str >> id_as_str; // Double >> to skip first word which is "Card"
        card.card_id = std::stoi(id_as_str.substr(0, id_as_str.size()-1));

        card_counts[card.card_id] += 1;

        std::string winning_nums_str;
        std::string nums_str;
        std::getline(iss, winning_nums_str, '|');
        std::getline(iss, nums_str, '|');
        card.winning_nums = parse_number_str_to_vector(winning_nums_str);
        card.nums         = parse_number_str_to_vector(nums_str);

        calculate_score(card);
        int num_matches = calc_num_matches(card);

        std::cout << "ID: " << card.card_id << ", Card count: " << card_counts[card.card_id] << "\n";

        for (int num_cards = card_counts[card.card_id];
                num_cards > 0;
                --num_cards) {
            for (int i = card.card_id + 1; i <= card.card_id + num_matches; ++i) {
                card_counts[i] += 1;
            }
        }

        card_vector.push_back(card);
    }
    return { card_vector, card_counts };
}

int main() {
    auto [ cards, card_counts ] = parse_file("input.txt");
    int total_score = 0;
    for (Card c : cards) {
        total_score += c.points;
    }
    std::cout << "Total points: " << total_score << '\n';
    int total_cards = 0;
    for (auto [id, num_cards] : card_counts) {
        total_cards += num_cards;
    }
    std::cout << "Total number of cards: " << total_cards << '\n';
}

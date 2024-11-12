#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>

struct RaceStats {
    size_t time, distance;

    static size_t calc_distance(size_t time_pressed, size_t total_time) {
        size_t speed = time_pressed;
        size_t time_to_move = total_time - time_pressed;
        return time_to_move * speed;
    }

    std::pair<size_t, size_t>
    find_margin() {
        size_t race_time = time;
        size_t distance_to_beat = distance;

        size_t low = std::numeric_limits<size_t>::max(), high = 0;
        for (size_t time_pressed=0;time_pressed<race_time;++time_pressed) {
            size_t distance_traveled = calc_distance(time_pressed, race_time);
            if (distance_traveled > distance_to_beat) {
                if (time_pressed < low) low = time_pressed;
                if (time_pressed > high) high = time_pressed;
            }
        }
        return {low, high};
    }

    int find_result() {
        auto result = find_margin();
        return result.second - result.first + 1;
    }
    /*

    std::vector<std::pair<int,int>>
    find_all_margins() {
        std::vector<std::pair<int,int>> margins_vec;
        for (int race_id=0; race_id<times.size(); ++race_id) {
            margins_vec.push_back(find_margin(race_id));
        }
        return margins_vec;
    }

    std::vector<int>
    find_num_ways_to_win_from_margins(std::vector<std::pair<int,int>> margins_vec) {
        std::vector<int> num_ways_to_win_vec;
        for (auto p : margins_vec) {
            num_ways_to_win_vec.push_back(p.second - p.first + 1);
        }
        return num_ways_to_win_vec;
    }

    int find_multiple_of_ways_to_win(std::vector<int> num_ways_to_win_vec) {
        int result = 1;
        for (int i : num_ways_to_win_vec) {
            result *= i;
        }
        return result;
    }

    int find_result_from_all_races() {
        auto margins = find_all_margins();
        auto ways_to_win = find_num_ways_to_win_from_margins(margins);
        int result = find_multiple_of_ways_to_win(ways_to_win);
        return result;
    }
    */
};

size_t conv_line_to_size_t(const std::string& line);

RaceStats parse_file(std::string file_name) {
    std::ifstream in{file_name};
    std::string time_line, distance_line;
    std::getline(in, time_line);
    std::getline(in, distance_line);

    size_t time = conv_line_to_size_t(time_line);
    size_t distance = conv_line_to_size_t(distance_line);

    return {time, distance};
}

size_t conv_line_to_size_t(const std::string& line) {
    std::istringstream iss{line};
    std::string token, result_string = "";
    iss >> token; // voids first word which is "Time:" and "Distance:"

    while (iss >> token) {
        result_string += token;
    }
    return std::stoul(result_string);
}

int main() {
    RaceStats races = parse_file("input.txt");
    size_t num_ways_beat_record = races.find_result();
    std::cout << "Total ways to beat record: " << num_ways_beat_record << '\n';
//    int multiple_of_wins = races.find_result_from_all_races();
//    std::cout << "Result: " << multiple_of_wins << '\n';
}

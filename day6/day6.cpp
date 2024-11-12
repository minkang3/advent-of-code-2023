#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <climits>

struct RaceStats {
    std::vector<int> times, distances;

    static int calc_distance(int time_pressed, int total_time) {
        int speed = time_pressed;
        int time_to_move = total_time - time_pressed;
        return time_to_move * speed;
    }

    std::pair<int, int>
    find_margin(int race_id) {
        int race_time = times[race_id];
        int distance_to_beat = distances[race_id];

        int low = INT_MAX, high = 0;
        for (int time_pressed=0;time_pressed<race_time;++time_pressed) {
            int distance_traveled = calc_distance(time_pressed, race_time);
            if (distance_traveled > distance_to_beat) {
                if (time_pressed < low) low = time_pressed;
                if (time_pressed > high) high = time_pressed;
            }
        }
        return {low, high};
    }

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
};

std::vector<int> conv_line_to_int_vector(const std::string& line) {
    std::vector<int> result_vec;
    std::istringstream iss{line};
    std::string token;
    iss >> token; // voids first word which is "Time:" and "Distance:"
    
    while (iss >> token) {
        result_vec.push_back(std::stoi(token));
    }
    return result_vec;
}

RaceStats parse_file(std::string file_name) {
    std::ifstream in{file_name};
    std::string time_line, distance_line;
    std::getline(in, time_line);
    std::getline(in, distance_line);

    std::vector<int> times_vec = conv_line_to_int_vector(time_line);
    std::vector<int> distances_vec = conv_line_to_int_vector(distance_line);

    return {times_vec, distances_vec};
}


int main() {
    RaceStats races = parse_file("input.txt");
    int multiple_of_wins = races.find_result_from_all_races();
    std::cout << "Result: " << multiple_of_wins << '\n';
}

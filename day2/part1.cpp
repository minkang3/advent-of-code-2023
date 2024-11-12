#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string_view>

struct GameInfo {
    int game_id;
    int max_red   = 0;
    int max_green = 0;
    int max_blue  = 0;
};

struct intString {
    int num;
    std::string color;
};

intString tokenize_numColor(std::string numColor) {
    std::istringstream iss{numColor};
    intString is;
    std::string temp;
    iss >> temp;
    is.num = std::stoi(temp);
    iss >> is.color;
    return is;
}

void parse_set(GameInfo& cube, std::string set) {
    std::istringstream iss{set};
    std::string numColor;
    while (std::getline(iss, numColor, ',')) {
        auto [num, color] = tokenize_numColor(numColor);
        if (color == "red" && num > cube.max_red)
            cube.max_red = num;
        else if (color == "green" && num > cube.max_green)
            cube.max_green = num;
        else if (color == "blue" && num > cube.max_blue)
            cube.max_blue = num;
    }
}

std::vector<GameInfo>
parse_file(const std::string& file_name) {
    std::ifstream in{file_name};
    std::string line;

    std::vector<GameInfo> cubes_vec;

    while (std::getline(in, line)) {
        GameInfo cube;
        std::istringstream iss{line};
        iss.ignore(5); // ignores "Game " part of string

        std::string game_id;
        iss >> game_id;
        cube.game_id = std::stoi(game_id.substr(0, game_id.length()-1)); // Extracts number from "<number>:" and converts to int

        std::string set;
        while (std::getline(iss, set, ';')) {
            parse_set(cube, set);
        }
        cubes_vec.push_back(cube);
    }
    return cubes_vec;
}


std::vector<int>
get_viable_games(std::vector<GameInfo> games, int red, int green, int blue) {
    std::vector<int> viable_games;
    for (GameInfo gi : games) {
        if (red >= gi.max_red &&
                green >= gi.max_green &&
                blue >= gi.max_blue)
            viable_games.push_back(gi.game_id);
    }
    return viable_games;
}


int compute_powers(std::vector<GameInfo> games) {
    int sum = 0;
    for (auto gi : games) {
        sum += gi.max_red * gi.max_green * gi.max_blue;
    }
    return sum;
}


int main() {
    auto games = parse_file("input.txt");

//    for (auto gi : games) {
//        std::cout << gi.max_red << ' ' << gi.max_blue << ' ' << gi.max_green << '\n';
//    }

    auto viable_games = get_viable_games(games, 12, 13, 14);
    int sum = 0;
    for (int i : viable_games)
        sum += i;
    std::cout << sum << '\n';
    int powers = compute_powers(games);
    std::cout << powers << '\n';
    std::cout << "Done!\n";
}

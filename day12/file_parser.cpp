#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

#include "arrange_springs.cpp"

std::vector<Springs> parse_file(const std::string& file_name);

std::vector<Springs> parse_file(const std::string& file_name) {
	std::vector<Springs> result;

	std::ifstream in {file_name};
	std::string line;

	std::regex whitespace("\\s");
	std::regex comma(",");

	while (std::getline(in, line)) {
		//std::istringstream iss{line};
		std::sregex_token_iterator line_it(line.begin(), line.end(), whitespace, -1);

		std::string s_row = *line_it++;
		std::string nums_str = *line_it;

		std::vector<int> nums_vec;

		std::sregex_token_iterator nums_it(nums_str.begin(), nums_str.end(), comma, -1), end;
		while (nums_it != end) {
			nums_vec.push_back(std::stoi(*nums_it++));
		}

		result.push_back({s_row, nums_vec});
	}
	return result;
}

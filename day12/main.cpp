#include "file_parser.cpp"

int main() {
	auto springs_list = parse_file("input.txt");
	int result = calc_total_arrangements(springs_list);

	std::cout << "\nTotal valid combinations: " << result << '\n';

	
	/* std::cout << std::boolalpha << validate_springs("##.##.#", {3,2,1}) << '\n'; */
}

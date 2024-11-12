#include "file_parser.cpp"
#include "matrix_operations.cpp"
#include "galaxy_dist.cpp"

int main() {
    auto matrix = parse_file_to_matrix("input.txt");
    /* auto matrix = parse_file_to_matrix("test_input.txt"); */
    /* auto matrix = parse_file_to_matrix("test_input_small.txt"); */
    expand_matrix(matrix);
    std::cout << "\nExpanded matrix:\n";
    std::cout << " 0123456789012\n";
    int col = 0;
    for (auto line : matrix) {
        std::cout << col++ << line << '\n';
    }
    auto mp = map_all_galaxies(matrix);
    for (auto e : mp) {
        std::cout << e.first.first << ", " << e.first.second << ": " << e.second << '\n';
    }
    auto galaxy_pairs = find_all_pairs(matrix, mp);
    int sum = sum_distances_of_pairs(galaxy_pairs);
    std::cout << "\nSum of distances: " << sum << '\n';
}

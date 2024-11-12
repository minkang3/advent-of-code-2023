#include "file_parser.h"

#include <iostream>


int main() {
    Readings readings = parse_file("input.txt");
    int64_t result = readings.find_sum_of_extrapolated_values();
    std::cout << "Sum: " << result << '\n';

    //std::vector<int32_t> vals{10, 13, 16, 21, 30, 45};
    //auto i = extrapolate_val_p2(vals);
    //std::cout << i << '\n';
}

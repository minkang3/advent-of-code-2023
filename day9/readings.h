#ifndef READINGS_H
#define READINGS_H

#include <iostream>
#include <vector>
#include <cstdint>

std::vector<int32_t> find_differences(std::vector<int32_t> vec);
int32_t extrapolate_val_p1(std::vector<int32_t> vec);
int32_t extrapolate_val_p2(std::vector<int32_t> vec);

struct Readings : public std::vector<std::vector<int32_t>> {
    std::vector<int32_t> extrapolate_all_values() {
        std::vector<int32_t> extrapolated_values;
        for (auto history : *this) {
            int32_t val = extrapolate_val_p2(history);
            extrapolated_values.push_back(val);
        }
        return extrapolated_values;
    }

    int64_t find_sum_of_extrapolated_values() {
        auto extrapolated_values = extrapolate_all_values();
        int64_t sum = 0;
        for (int32_t i : extrapolated_values) {
            sum += i;
        }
        return sum;
    }
};

std::vector<int32_t> find_differences(std::vector<int32_t> vec) {
    std::vector<int32_t> diffs(vec.size()-1);
    for (int i = 0; i+1 < vec.size(); ++i) {
        diffs[i] = vec[i + 1] - vec[i];
    }
    return diffs;
}

bool isAllZeroes(std::vector<int32_t> vec) {
    for (int32_t i : vec)
        if (i != 0)
            return false;
    return true;
}

int32_t extrapolate_val_p1(std::vector<int32_t> vec) {
    if (isAllZeroes(vec))
        return 0;
    return vec[vec.size() - 1] + extrapolate_val_p1(find_differences(vec));
}

int32_t extrapolate_val_p2(std::vector<int32_t> vec) {
    if (isAllZeroes(vec))
        return 0;
    return vec[0] - extrapolate_val_p2(find_differences(vec));
}


#endif

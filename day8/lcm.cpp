#include <iostream>
#include <cstdint>
#include <vector>

size_t gcd(size_t a, size_t b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

size_t lcm(size_t a, size_t b) {
    return (a * b) / gcd(a, b);
}

size_t lcm_all(std::vector<size_t> nums) {
    size_t result = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
        result = lcm(result, nums[i]);
    }
    return result;
}

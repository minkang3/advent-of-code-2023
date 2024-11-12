#ifndef ARRANGE_SPRINGS_CPP
#define ARRANGE_SPRINGS_CPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>


struct Springs {
	std::string unknown_str;
	std::vector<int> nums;

	friend std::ostream& operator<<(std::ostream& out, const Springs& s) {
		out << s.unknown_str << " ";
		for (int i : s.nums)
			out << i << ",";
		return out;
	}
};


int calc_total_arrangements(const std::vector<Springs> spring_list);
int calc_num_arrangements(const Springs& s);
bool validate_springs(const std::string& copy, const std::vector<int>& nums);
int min(int, int);

int calc_total_arrangements(const std::vector<Springs> spring_list) {
	int result{0};
	for (const Springs& s : spring_list) {
		result += calc_num_arrangements(s);
	}
	return result;
}

int calc_num_arrangements(const Springs& s) {
       std::cout << '\n';
	for (int n : s.nums)
		std::cout << n << ' ';
	std::cout << "\n";

	const std::string &str = s.unknown_str;
	int sum = std::accumulate(s.nums.begin(), s.nums.end(), 0);
	int num_pounds = std::count(str.begin(), str.end(), '#');
	sum -= num_pounds;

	int result = 0;

	std::vector<bool> bitmask;
	std::vector<int> index_map;

	for (int i = 0, j = sum; i < str.size(); ++i) {
		if (str[i] == '?') {
			bitmask.push_back((sum-- > 0) ? 1 : 0);
			index_map.push_back(i);
		}
	}

	do {
		std::string copy = str;
		for (int i = 0; i < bitmask.size(); ++i) {
			copy[index_map[i]] = bitmask[i] ? '#' : '.';
		}
		std::cout << copy << "   ";
		result += validate_springs(copy, s.nums);
		if (validate_springs(copy, s.nums)) std::cout << "Valid.\n";
		else std::cout << "Not valid.\n";
	} while (std::prev_permutation(bitmask.begin(), bitmask.end()));

	return result;
}

bool validate_springs(const std::string& copy, const std::vector<int>& nums) {
	int i = 0;
	for (int n : nums) {
		while (copy[i] != '#') ++i;
		for (int j = n; j > 0; --j) {
			if (copy[i++] != '#')
				return false;
		}
		if (i < copy.length() && copy[i] != '.') return false;
	}
	return true;
}

int min(int a, int b) {
	return (a < b) ? a : b;
}




#endif




/*

Idea 1: Permutations.
Try every permutation of possible arrangements, if the arrangement is valid, add one to result.
Essentially brute force.
Non-recurssive.

Use prev_permutation() on a string or bitmask. The string size would be
the number of question marks, and the number of 1's would be the total
number of damanged springs.
So for example:
??.??.????? 1,1,3
The generated string would be:
111110000

Then we would iterate through the permutations, so first the above string, then:
111101000,
111100100,
...
For each of those strings, we would iterate through each question mark and 
reference the bitmask to see whether a pound is entered or a period is entered.

Is there a better way to map the bitmask to the original string?

-  Array of pairs<boolean, index>
> Parallel arrays, one bitmask, one array where each index of the bitmask is mapped
to the corresponding ? in the original string.
 

Uh oh!
Our solution doesn't work because the sum of the nums don't actually correspond to
the number of strings, since the springs can be already revealed.

To fix this, we can add the number of #'s and subtract this from our sum
*/

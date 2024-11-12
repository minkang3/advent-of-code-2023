// Idea: Build a 2d matrix with the file, just as is. Then, whenver you find a
// number, you look to left and right, and around the top and around the bottom
// if there is a symbol, add the number
// Idea 2: Look for symbols, and look around the symbol. If there are numbers,
// add the number. This way may be more efficient, but harder.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> conv_file_to_matrix(const std::string& file_name) {
    std::ifstream in{file_name};
    std::vector<std::string> matrix;

    std::string line;
    while (std::getline(in, line)) {
        matrix.push_back(line);
    }
    return matrix;
}

bool isNum(char c) {
    return (c >= 48 && c <= 57);
}

bool isSymbol(char c) {
    return (c != '.' && !isNum(c));
}

//bool checkAdjacentRows();

bool isSymbolAdjacent(int left_index, int right_index, int row,
                          const std::vector<std::string>& matrix) {
    //bool isAdj = false;
    if (left_index > 0 && isSymbol(matrix[row][left_index-1]))
        return true;
    if (right_index < matrix[row].size()-1 && 
            isSymbol(matrix[row][right_index+1]))
        return true;
//    std::cout << "in isSymbolAdjacent: ";
//    std::cout << matrix[row].substr(left_index, right_index+1-left_index) << '\n';
    // Go through above and below row, while not going out of bounds
    for (int i=row-1;i<=row+1;i+=2) {
        if (i < 0 || i >= matrix.size())
            continue;
//        std::cout << "i: " << i << '\n';
//        std::cout << "j: ";
        for (int j=left_index-1;
                j<=right_index+1;
                ++j) {
            if (j < 0 || j >= matrix[i].size())
                continue;
 //           std::cout << j << ' ';
            if (isSymbol(matrix[i][j]))
                return true;
        }
    }
    return false;
}

std::vector<int> parse_matrix(const std::vector<std::string>& matrix) {
    std::vector<int> valid_nums;
    for (int row=0;row<matrix.size();++row) {
        for (int col=0;col<matrix[row].size();++col) {
            char c = matrix[row][col];
            if (isNum(c)) {
                int left_index = col;
                while (col < matrix[row].size() && isNum(matrix[row][++col]));
                int right_index = col - 1;
                //std::cout << "left_index: " << left_index << ", right_index: " << right_index << '\n';
//                std::cout << "in parse_matrx: ";
//                std::cout << matrix[row].substr(left_index, right_index + 1 - left_index) << '\n';
                // Funciton call
                if (isSymbolAdjacent(left_index, right_index, row, matrix)) {
                    int num = stoi(matrix[row].substr(left_index,right_index+1-left_index));
                    valid_nums.push_back(num);
                }
            }
        }
    }
    return valid_nums;
}


int findNum(int row, int col, const std::vector<std::string>& matrix) {
    // Go left until no num, go right until no num
    // What to return if no number found? Prob -1
    if (!isNum(matrix[row][col]))
        return -1;
    int left_index = col;
    int right_index = col;
    while (left_index-1 >= 0 && isNum(matrix[row][left_index-1])) 
        --left_index;
    while (right_index+1 < matrix[row].size() && isNum(matrix[row][right_index+1]))
        ++right_index;
    std::string num_str = matrix[row].substr(left_index, right_index+1-left_index);
    return std::stoi(num_str);
}


std::vector<int> find_adjacent_numbers(int row, int col, const std::vector<std::string>& matrix) {
    // Search around tnen call func if isNum
    std::vector<int> adj_nums;
    if (col-1 >= 0 && isNum(matrix[row][col-1])) {
        int num = findNum(row, col-1, matrix);
        adj_nums.push_back(num);
    }
    if (col+1 < matrix[row].size() && isNum(matrix[row][col+1])) {
        int num = findNum(row, col+1, matrix);
        adj_nums.push_back(num);
    }
    // TODO: search above and below
    //
    // How to not find same number twice?
    // Check directly above, if not found, then left and right
    // Guarentees not finding the same number twice
    for (int i=row-1; i<=row+1; i+=2) {
        if (i < 0 || i >= matrix.size())
            continue;
        // First check directly above/below
        if (isNum(matrix[i][col])) {
            int num = findNum(i, col, matrix);
            adj_nums.push_back(num);
        } else { // If not directly above, check to left and right
            for (int j=col-1; j<=col+1; j+=2) {
                if (j < 0 || j >= matrix[i].size())
                    continue;
                if (isNum(matrix[i][j])) {
                    int num = findNum(i, j, matrix);
                    adj_nums.push_back(num);
                }
            }
        }
    }

    return adj_nums;
}


int find_gear_ratios(const std::vector<std::string>& matrix) {
    int sum = 0;
    for (int row=0; row<matrix.size(); ++row) {
        for (int col=0; col<matrix[row].size(); ++col) {
            if (matrix[row][col] == '*') {
                auto adj_nums = find_adjacent_numbers(row, col, matrix);
                if (adj_nums.size() != 2)
                    continue;
                sum += adj_nums[0] * adj_nums[1];
            }
        }
    }
    return sum;
}


int main() {
    std::vector<std::string> matrix = conv_file_to_matrix("input.txt");

    int result = find_gear_ratios(matrix);
    std::cout << "Gear ratios: " << result << '\n';
}

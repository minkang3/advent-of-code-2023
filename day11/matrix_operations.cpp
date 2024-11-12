#ifndef MAT_OPP_CPP
#define MAT_OPP_CPP

//#include <iostream>
#include <vector>
#include <string>

// ***** HEADERS ***** //
void expand_matrix(std::vector<std::string>& matrix);
void insert_row_copy(std::vector<std::string>& matrix, int index);
void insert_col_copy(std::vector<std::string>& matrix, int index);
void copy_col(std::vector<std::string>& matrix, int target, int src);

// ***** DEFINITIONS ***** //
void expand_matrix(std::vector<std::string>& matrix) {
    
    for (int row = matrix.size() - 1; row >= 0; --row) {
        if (matrix[row].find('#') != std::string::npos)
            continue;
        insert_row_copy(matrix, row);
    }
    
    for (int col = matrix[0].size() - 1; col >= 0; --col) {
        // Checks if column has '#'
        bool hasGalaxy = false;
        for (int row = 0; row < matrix.size(); ++row) {
            if (matrix[row][col] == '#') {
                hasGalaxy = true;
                break;
            }
        }
        if (hasGalaxy) {
            continue;
        }
        // If column has no '#'
        insert_col_copy(matrix, col);
    }
}

void insert_row_copy(std::vector<std::string>& matrix, int index) {
    matrix.push_back(matrix[matrix.size() - 1]);
    for (int i = matrix.size() - 2; i > index; --i) {
        matrix[i] = matrix[i-1];
    }
}

void insert_col_copy(std::vector<std::string>& matrix, int index) {
    // Copy last column
    for (std::string& line : matrix) {
        line.push_back(line[line.size()-1]);
    }
    for (int col = matrix[0].size() - 2; col > index; --col) {
        copy_col(matrix, col, col-1);
    }
}

void copy_col(std::vector<std::string>& matrix, int target, int src) {
    for (std::string& line : matrix) {
        line[target] = line[src];
    }
}

#endif

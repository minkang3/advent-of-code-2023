#ifndef PIPES_H
#define PIPES_H

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <cstdlib>
#include <cassert>
#include <fstream>


struct PipeTraverser {
    int posX, posY;
    int prevX, prevY;

    PipeTraverser(int posX, int posY, int prevX, int prevY)
    : posX(posX), posY(posY), prevX(prevX), prevY(prevY) {}

    std::pair<int,int> traverse(char c) {
        int tempX = posX, tempY = posY;
        std::cout << "traverse called" << '\n';
        if (c == '|') {
            if (posY-1 == prevY) ++posY;
            else if (posY+1 == prevY) --posY;
            else throw "|";
        } else if (c == '-') {
            if (posX-1 == prevX) ++posX;
            else if (posX+1 == prevX) --posX;
            else throw "-";
        } else if (c == 'L') {
            if (posY-1 == prevY) ++posX;
            else if (posX+1 == prevX) --posY;
            else throw "L";
        } else if (c == 'J') {
            if (posY-1 == prevY) --posX;
            else if (posX-1 == prevX) --posY;
            else throw "J";
        } else if (c == '7') {
            if (posX-1 == prevX) ++posY;
            else if (posY+1 == prevY) --posX;
            else throw "7";
        } else if (c == 'F') {
            if (posX+1 == prevX) ++posY;
            else if (posY+1 == prevY) ++posX;
            else { throw "F - " + std::to_string(posX) + ", " + std::to_string(posY); }
        } else throw ".";

        prevX = tempX;
        prevY = tempY;
        return {posX, posY};
    }

    bool isAdjOrSame(PipeTraverser other) {
        if ((std::abs(posX - other.posX) <= 1 && posY == other.posY) ||
            (std::abs(posY - other.posY) <= 1 && posX == other.posX)) 
            return true;
        return false;
    }
    
};


struct DotTraverser {

};


struct PerimeterMatrix : public std::vector<std::string> {
    std::set<char> top_entry_pipes{'L', 'J'};

    bool isElim(int x, int y) {
        return (*this)[y][x] == '~';
    }

    bool isDot(int x, int y) {
        return (*this)[y][x] == '.';
    }

    void eliminatePos(int x, int y) {
        (*this)[y][x] = '~';
    }

    void eliminateDots(int x, int y) {
        // If out of bounds
        if (x < 0 || y < 0 || y >= this->size() || x >= (*this)[y].length())
            return;
        if (isElim(x, y)) 
            return;
        if (!isDot(x,y)) {
            return;
        }
        eliminatePos(x, y);
        // Check above
        if (y-1 >= 0) {
            if (isDot(x, y-1))
                eliminateDots(x, y-1);
            else {
                char above = (*this)[y-1][x];
                if (above == 'L' || above == 'J') {
                    
                }
            }
        }

        /*
        {
            eliminatePos(x, y);
            eliminateDots(x, y-1); // eliminate above
            eliminateDots(x, y+1); // eliminate below
            eliminateDots(x-1, y); // eliminate left
            eliminateDots(x+1, y); // eliminate right
            return;
        }
        */

    }
};


struct PipeMatrix : public std::vector<std::string> {
    int posX, posY;
    PerimeterMatrix per_matrix;

    void mirror(int x, int y) {
        per_matrix[y][x] = (*this)[y][x];
    }

    void add_line(std::string line) {
        this->push_back(line);
        per_matrix.emplace_back(line.length(), '.');
    }

    void find_start_pos() {
        for (int y=0; y<this->size(); ++y) {
            for (int x=0; x<(*this)[y].length(); ++x) {
                if ((*this)[y][x] == 'S') {
                    posX = x;
                    posY = y;
                    mirror(x,y);
                    return; } } }
    }

    std::vector<std::pair<int, int>> find_pipes_conn_to_start_point() {
        std::vector<std::pair<int, int>> pipes;
        // Check to left of start pos
        if ((*this)[posY][posX-1] == '-' ||
            (*this)[posY][posX-1] == 'L' ||
            (*this)[posY][posX-1] == 'F') {
            pipes.emplace_back(posX-1, posY);
        }
        // Check to right of start pos
        if ((*this)[posY][posX+1] == '-' ||
            (*this)[posY][posX+1] == 'J' ||
            (*this)[posY][posX+1] == '7') {
            pipes.emplace_back(posX+1, posY);
        }
        // Check above start pos
        if ((*this)[posY-1][posX] == '|' ||
            (*this)[posY-1][posX] == 'F' ||
            (*this)[posY-1][posX] == '7') {
            pipes.emplace_back(posX, posY-1);
        }
        // Check below start pos
        if ((*this)[posY+1][posX] == '|' ||
            (*this)[posY+1][posX] == 'J' ||
            (*this)[posY+1][posX] == 'L') {
            pipes.emplace_back(posX, posY+1);
        }
        assert(pipes.size() == 2 && "Size of starting number of pipes was not 2");
        return pipes;
    }

    int find_steps_to_furthest_pipe() {
        //find_start_pos();
        std::vector<std::pair<int, int>> connected_pipes = find_pipes_conn_to_start_point();
        auto [pt1_x, pt1_y] = connected_pipes[0];
        PipeTraverser pt1(pt1_x, pt1_y, posX, posY);
        auto [pt2_x, pt2_y] = connected_pipes[1];
        PipeTraverser pt2(pt2_x, pt2_y, posX, posY);

        mirror(pt1_x, pt1_y);
        mirror(pt2_x, pt2_y);

        int steps_away = 1;
        while (!pt1.isAdjOrSame(pt2)) {
            auto [x1, y1] = pt1.traverse((*this)[pt1.posY][pt1.posX]);
            auto [x2, y2] = pt2.traverse((*this)[pt2.posY][pt2.posX]);
            mirror(x1, y1);
            mirror(x2, y2);
            ++steps_away;
        }
        return steps_away;
    }

    void output_per_mat_to_file(std::string file_name) {
        std::ofstream out{file_name};
        for (auto s : per_matrix) {
            out << s << '\n';
        }
    }
};




#endif

/*
    Idea 1:
    The idea is to track the points in an array or perhaps another matrix
    of the perimeter when i traverse.

    Idea 2:
    Determine which side is the "inside". Then, when traversing, whenever there
    is an open space on the inside, add that space.

    Could work if I search all sides on two way junctions like L, J, F, just
    the sides that are inside.

    Idea 3:
    Parallel Matrix to mark the perimeter
    Basically copy the perimeter to another matrix
    Then check each opening, see if it's inside.
    How to see if it's inside?
    First let's make the parallel matrix.

    I know where the outside is.
    Start from the outside and convert all '.' to ','
    If it encounters an opening, follow it in and delete the '.' that is leads
    to.

    Issue:
    When probing the perimeter, how to keep track of which side is the "outside"?
    Idea 1:
    Keep track of two of the pipes while probing.
    Issue:
    There can be pipes within the perimeter which are not a part of the perimeter
    Making this solution not possible


*/

#ifndef GALAXY_DIST_CPP
#define GALAXY_DIST_CPP

#include "traverser.cpp"

#include <vector>
#include <string>
#include <map>
#include <queue>
#include <set>
#include <algorithm>

using galaxy_num = int;

// ***** HEADERS ***** //
std::map<std::pair<int,int>,galaxy_num>
map_all_galaxies(const std::vector<std::string>& matrix);

std::set<std::tuple<int,int,int>>
find_all_pairs(
    const std::vector<std::string>& matrix,
    std::map<std::pair<int,int>,galaxy_num>& mp);

int sum_distances_of_pairs(const std::set<std::tuple<int,int,int>>& galaxy_pairs);


// ***** DEFINITIONS ***** //
std::map<std::pair<int,int>,galaxy_num>
map_all_galaxies(const std::vector<std::string>& matrix) {
    std::map<std::pair<int,int>,galaxy_num> mp;
    int curr_galaxy_num = 1;
    for (int row=0; row<matrix.size(); ++row) {
        for (int col=0; col<matrix[row].size(); ++col) {
            if (matrix[row][col] != '#') continue;
            mp[{row,col}] = curr_galaxy_num++;
        }
    }
    return mp;
}

std::set<std::tuple<int,int,int>>
find_all_pairs(
        const std::vector<std::string>& matrix,
        std::map<std::pair<int,int>,galaxy_num>& mp) {
    std::set<std::tuple<int,int,int>> galaxy_pairs;

    auto oob = [&](int row, int col) {
        return (row < 0 || row >= matrix.size()) || (col < 0 || col >= matrix[row].size());
    };

    auto bfs = [&](Traverser trav) {
        std::queue<Traverser> q;

        galaxy_num curr_gal_num = mp[{trav.row,trav.col}];
        std::vector<std::vector<bool>> traversed(
            matrix.size(), std::vector<bool>(matrix[0].size(), false)
        );
        traversed[trav.row][trav.col] = true;

        q.push({trav.row+1, trav.col  , 1});
        q.push({trav.row-1, trav.col  , 1});
        q.push({trav.row  , trav.col-1, 1});
        q.push({trav.row  , trav.col+1, 1});

        std::set<galaxy_num> found_galaxies;
        while (found_galaxies.size() < mp.size() - 1) {
            Traverser t = q.front();
            q.pop();
            if (oob(t.row, t.col)) continue;
            if (traversed[t.row][t.col]) continue;

            traversed[t.row][t.col] = true;

            if (matrix[t.row][t.col] == '#') {
                galaxy_num found_gal_num = mp[{t.row,t.col}];
                if (found_galaxies.find(found_gal_num) == found_galaxies.end()) {
                    found_galaxies.insert(mp[{t.row,t.col}]);
                    std::cout << "Found galaxy at (" << t.row << ", " << t.col << ")\n";
                    galaxy_pairs.insert({std::min(curr_gal_num, found_gal_num), std::max(curr_gal_num, found_gal_num), t.dist_traveled});
                }
            }
            std::vector<std::pair<int,int>> diffs{{1,0},{-1,0},{0,-1},{0,1}};
            for (auto diff : diffs) {
                Traverser t_next = t;
                t_next.row += diff.first;
                t_next.col += diff.second;
                ++t_next.dist_traveled;
                q.push(t_next);
            }
        }

    };

    for (auto e : mp) {
        auto [row, col] = e.first;
        galaxy_num n = e.second;
        Traverser t{row, col, 0};
        bfs(t);
    }

    for (auto e : galaxy_pairs) {
        auto [g1, g2, dist] = e;
        std::cout << "(" << g1 << ", " << g2 << "): " << dist << '\n';
    }
    std::cout << "Total Pairs: " << galaxy_pairs.size() << '\n';

    return galaxy_pairs;
}

int sum_distances_of_pairs(const std::set<std::tuple<int,int,int>>& galaxy_pairs) {
    int sum = 0;
    for (auto e : galaxy_pairs) {
        sum += std::get<2>(e);
    }
    return sum;
}



#endif

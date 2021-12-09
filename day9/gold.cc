#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Point {
    int row, col;
    int n;
};

// bounds-checking
Point get_neighbor(const vector<vector<Point>> &mat, int r, int c) {
    auto last_r = mat.size()-1;
    auto last_c = mat[0].size()-1;

    if (r < 0 || r > last_r || c < 0 || c > last_c)
        return {.row = -1, .col = -1, .n = INT32_MAX};
    return mat[r][c];
}

// returns true if the vector v holds a point with the same coordinates as p
bool point_in_vec(const vector<Point> &v, const Point &p) {
    return any_of(begin(v), end(v), [&](Point other){ return other.row == p.row && other.col == p.col;});
}

void add_neighbors(vector<Point> &basin, const vector<vector<Point>> &h, int row, int col) {
    basin.push_back(h[row][col]);

    auto above = get_neighbor(h, row-1, col);
    auto below = get_neighbor(h, row+1, col);
    auto left = get_neighbor(h, row, col-1);
    auto right = get_neighbor(h, row, col+1);

    if (above.n < 9 && !point_in_vec(basin, above)) {
        add_neighbors(basin, h, row-1, col);
    }
    if (below.n < 9 && !point_in_vec(basin, below)) {
        add_neighbors(basin, h, row+1, col);
    }
    if (left.n < 9 && !point_in_vec(basin, left)) {
        add_neighbors(basin, h, row, col-1);
    }
    if (right.n < 9 && !point_in_vec(basin, right)) {
        add_neighbors(basin, h, row, col+1);
    }
}

// 736920
int main() {
    string str;
    vector<vector<Point>> h;
    int r = 0, c = 0;
    while (getline(cin, str)) {
        vector<Point> line;
        for (const auto &n : str) {
            line.push_back({.row = r, .col = c++, .n = n-'0'});
        }
        h.push_back(line);
        r++;
    }
    
    vector<vector<Point>> basins;
    vector<pair<int, int>> d = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    for (int row = 0; row < h.size(); ++row) {
        for (int col = 0; col < h[row].size(); ++col) {
            Point p = h[row][col];

            // local min
            if (all_of(begin(d), end(d), [&](auto d){return get_neighbor(h, row+d.first, col+d.second).n > p.n;})){
                vector<Point> basin;
                add_neighbors(basin, h, row, col);
                basins.push_back(basin);
            }
        }
    }

    sort(begin(basins), end(basins), [](auto a, auto b){return a.size() > b.size();});
    cout << "three largest basin sizes: " << basins.at(0).size() << " " << basins.at(1).size() << " " << basins.at(2).size() << "\n";
    cout << "product: " << basins.at(0).size()*basins.at(1).size()*basins.at(2).size() << "\n";
    return 0;
}

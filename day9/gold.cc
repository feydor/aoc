#include <algorithm>
#include <cmath>
#include <cstring>
#include <numeric>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <numeric>
#include <sstream>
using namespace std;

struct Point {
    int row, col;
    int x;
    friend ostream &operator<<(ostream &os, const Point &p) {
        os << "(" << p.row << "," << p.col << ")" << ": " << p.x;
        return os;
    }
};

// v is a square matrix
int check_neighbor(vector<vector<Point>> &v, int r, int c) {
    auto last_r = v.size()-1;
    auto last_c = v[0].size()-1;
    
    // topleft corner -> bottom-right corner
    if (r < 0 && c < 0) {
        return v[last_r][last_c].x;
    }
    // topright corner -> bottomleft corner
    else if(r < 0 && c > last_c) {
        return v[last_r][0].x;
    }
    // bottomleft corner -> topright corner
    else if (r > last_r && c < 0) {
        return v[0][last_c].x;
    }
    // bottomright corener -> topleft corner
    else if (r > last_r && c > last_c) {
        return v[0][0].x;
    }
    // top -> bottom
    else if (r < 0) {
        // return v[last_r][c];
        return v[0][c].x;
    }
    // bottom -> top
    else if (r > last_r) {
        // return v[0][c];
        return v[last_r][c].x; // no wrapping
    }
    // left -> right
    else if (c < 0) {
        // return v[r][last_c];
        return v[r][0].x;
    }
    // right -> left
    else if (c > last_c) {
        // return v[r][0];
        return v[r][last_c].x;
    }

    // normal
    return v[r][c].x;
}

vector<string> split(const string &s, char delimiter = ' ') {
    vector<string> splits;
    string split;
    istringstream ss(s);
    while (getline(ss, split, delimiter)) {
        if (split.empty()) continue;
        splits.push_back(split);
    }
    return splits;
}

// v is a square matrix
// no wrapping, only bounds-checking
Point get_neighbor(const vector<vector<Point>> &v, int r, int c) {
    auto last_r = v.size()-1;
    auto last_c = v[0].size()-1;

    // bounds checking for top, bottom, left, right
    if (r < 0 || r > last_r || c < 0 || c > last_c)
        return {.row = -1, .col = -1, .x = INT32_MAX};
    return v[r][c];
}

// returns true if the vector v holds a point with the same coordinates as p
bool point_coord_in_vector(const vector<Point> &v, const Point &p) {
    return any_of(begin(v), end(v), [&](Point other){ return other.row == p.row && other.col == p.col;});
}

void add_neighbors(vector<Point> &basin, const vector<vector<Point>> &h, int row, int col) {
    auto x = h[row][col];
    basin.push_back(x);

    Point left, right, above, below;
    above = get_neighbor(h, row-1, col);
    below = get_neighbor(h, row+1, col);
    left = get_neighbor(h, row, col-1);
    right = get_neighbor(h, row, col+1);

    // cout << "up: " << above << " right: " << right << " below: " << below <<  " left: " << left << endl;

    if (above.x < 9 && !point_coord_in_vector(basin, above)) {
        add_neighbors(basin, h, row-1, col);
    }

    if (below.x < 9 && !point_coord_in_vector(basin, below)) {
        add_neighbors(basin, h, row+1, col);
    }
    // left
    if (left.x < 9 && !point_coord_in_vector(basin, left)) {
        add_neighbors(basin, h, row, col-1);
    }
    // right
    if (right.x < 9 && !point_coord_in_vector(basin, right)) {
        add_neighbors(basin, h, row, col+1);
    }
}

// 736920
int main() {
    string str;
    int lows = 0; 
    vector<vector<Point>> h;
    int r = 0, c = 0;
    while (getline(cin, str)) {
        vector<Point> line;
        for (const auto &n : str) {
            line.push_back({.row = r, .col = c, .x = n-'0'});
            c++;
        }
        h.push_back(line);
        r++;
    }
    
    int last_row = h.size()-1;
    int last_col = h[0].size()-1;
    // row
    vector<vector<Point>> basins;
    for (int row = 0; row < h.size(); ++row) {
        // col
        for (int col = 0; col < h[row].size(); ++col) {
            Point p = h[row][col];
            int less_than = 0;
            int n_neighbors = 4;

            // corners have 2 neighbors, topleft then clockwise
            if (row == 0 && col == 0 ||
                row == 0 && col == last_col ||
                row == last_row && col == last_col ||
                row == last_row && col == 0) {
                n_neighbors = 2;
            }
            // top,bottom,leftmost, rightmost have 3 neighbors
            else if (row-1 < 0 || row+1 > last_row ||
                     col-1 < 0 || col+1 > last_col) {
                n_neighbors = 3;
            }
            
            // top, then clockwise
            if (p.x < check_neighbor(h, row-1, col)) ++less_than;
            if (p.x < check_neighbor(h, row, col+1)) ++less_than;
            if (p.x < check_neighbor(h, row+1, col)) ++less_than;
            if (p.x < check_neighbor(h, row, col-1)) ++less_than;

            if (n_neighbors == less_than) {
                // cout << "lowpoint found: " << p << endl;
                vector<Point> basin;
                add_neighbors(basin, h, row, col);
                // cout << "basin: ";
                // for (auto &m : basin) cout << m << " ";
                // cout << endl;
                basins.push_back(basin);
            }
        }
    }

    vector<int> sizes;
    for (const auto &basin : basins) {
        sizes.push_back(basin.size());
    }
    sort(begin(sizes), end(sizes), [](auto a, auto b){return a > b;});
    cout << "three largest basin sizes: " << sizes.at(0) << " " << sizes.at(1) << " " << sizes.at(2) << "\n";
    cout << "product: " << sizes.at(0)*sizes.at(1)*sizes.at(2) << "\n";
    return 0;
}

#include <algorithm>
#include <cmath>
#include <cstring>
#include <numeric>
#include <map>
#include <vector>
#include <iostream>
#include <numeric>
#include <sstream>
using namespace std;


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
int check_neighbor(vector<vector<int>> &v, int r, int c) {
    auto last_r = v.size()-1;
    auto last_c = v[0].size()-1;
    
    // topleft corner -> bottom-right corner
    if (r < 0 && c < 0) {
        return v[last_r][last_c];
    }
    // topright corner -> bottomleft corner
    else if(r < 0 && c > last_c) {
        return v[last_r][0];
    }
    // bottomleft corner -> topright corner
    else if (r > last_r && c < 0) {
        return v[0][last_c];
    }
    // bottomright corener -> topleft corner
    else if (r > last_r && c > last_c) {
        return v[0][0];
    }
    // top -> bottom
    else if (r < 0) {
        // return v[last_r][c];
        return v[0][c];
    }
    // bottom -> top
    else if (r > last_r) {
        // return v[0][c];
        return v[last_r][c]; // no wrapping
    }
    // left -> right
    else if (c < 0) {
        // return v[r][last_c];
        return v[r][0];
    }
    // right -> left
    else if (c > last_c) {
        // return v[r][0];
        return v[r][last_c];
    }

    // normal
    return v[r][c];
}

// 539
int main() {
    string str;
    int lows = 0; 
    vector<vector<int>> h;
    while (getline(cin, str)) {
        vector<int> line;
        for (const auto &c : str)
            line.push_back(c - '0');
        h.push_back(line);
    }
    cout << "rows: " << h.size() << endl;
    cout << "cols: " << h[0].size() << endl;
    for (int i = 0; i < h.size(); ++i) {
        for (auto j = 0; j < h[i].size(); ++j) {
            cout << h[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    int last_row = h.size()-1;
    int last_col = h[0].size()-1;
    // row
    // map<pair<int, int>, int> pos_map;
    vector<int> lows_;
    for (int row = 0; row < h.size(); ++row) {
        // col
        for (int col = 0; col < h[row].size(); ++col) {
            auto x = h[row][col];
            cout << x << " ";
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

            // if (x == 0) {
            //     cout << "\n@0 " << check_neighbor(h, row+1, col+1) << endl;
            // }
            
            // top, then clockwise
            if (x < check_neighbor(h, row-1, col)) ++less_than;
            // if (x < check_neighbor(h, row-1, col+1)) ++less_than;
            if (x < check_neighbor(h, row, col+1)) ++less_than;
            // if (x < check_neighbor(h, row+1, col+1)) ++less_than;
            if (x < check_neighbor(h, row+1, col)) ++less_than;
            // if (x < check_neighbor(h, row+1, col-1)) ++less_than;
            if (x < check_neighbor(h, row, col-1)) ++less_than;
            // if (x < check_neighbor(h, row-1, col-1)) ++less_than;

            if (n_neighbors == less_than) {
                cout << "\nlowpoint found: " << x << endl;
                lows_.push_back(x);
            }
        }
        cout << endl;
    }

    int sum = 0;
    for (const auto& h : lows_)
        sum += (h + 1);

    cout << sum << endl;
    return 0;
}

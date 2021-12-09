#include <algorithm>
#include <numeric>
#include <vector>
#include <iostream>
using namespace std;

vector<pair<int, int>> d = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

vector<int> get_neighbors(const vector<vector<int>> &mat, int row, int col) {
    vector<int> neighbors;
    for (const auto &[dy, dx] : d) {
        int y = row+dy, x = col+dx;
        if (x >= 0 && x < mat[0].size() && y >= 0 && y < mat.size())
            neighbors.push_back(mat[y][x]);
    }
    return neighbors;
}

// 539
int main() {
    string str;
    vector<vector<int>> mat;
    while (getline(cin, str)) {
        vector<int> line;
        transform(begin(str), end(str), back_inserter(line), [](char c){return c-'0';});
        mat.push_back(line);
    }
    
    vector<int> sinks;
    for (int row = 0; row < mat.size(); ++row) {
        for (int col = 0; col < mat[row].size(); ++col) {
            auto x = mat[row][col];
            auto neighbors = get_neighbors(mat, row, col);
            if (all_of(begin(neighbors), end(neighbors), [&](auto n){return n > x;}))
                sinks.push_back(x);
        }
    }

    cout << reduce(begin(sinks), end(sinks), 0, [](auto a, auto b){return a+b+1;}) << endl;
    return 0;
}

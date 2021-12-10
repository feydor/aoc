#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef pair<int, int> Point;

// bounds-checking
int get_neighbor(const vector<string> &mat, int row, int col) {
    auto last_r = mat.size()-1;
    auto last_c = mat[0].size()-1;

    if (row < 0 || (unsigned)row > last_r || col < 0 || (unsigned)col > last_c)
        return INT32_MAX;
    return mat[row][col]-'0';
}

// returns true if the vector v holds a point with the same coordinates as p
bool point_in_vec(const vector<Point> &v, int row, int col) {
    return any_of(begin(v), end(v), [&](Point other){ return other.first == row && other.second == col;});
}

void add_neighbors(vector<Point> &basin, const vector<string> &mat, int row, int col) {
    basin.push_back({row, col});

    auto above = get_neighbor(mat, row-1, col);
    auto below = get_neighbor(mat, row+1, col);
    auto left = get_neighbor(mat, row, col-1);
    auto right = get_neighbor(mat, row, col+1);

    if (above < 9 && !point_in_vec(basin, row-1, col)) {
        add_neighbors(basin, mat, row-1, col);
    }
    if (below < 9 && !point_in_vec(basin, row+1, col)) {
        add_neighbors(basin, mat, row+1, col);
    }
    if (left < 9 && !point_in_vec(basin, row, col-1)) {
        add_neighbors(basin, mat, row, col-1);
    }
    if (right < 9 && !point_in_vec(basin, row, col+1)) {
        add_neighbors(basin, mat, row, col+1);
    }
}

// 736920
int main() {
    string str;
    vector<string> mat;
    while (getline(cin, str)) {
        mat.push_back(str);
    }
    
    vector<uint64_t> basin_sizes;
    vector<pair<int, int>> dir = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    for (int row = 0; (unsigned)row < mat.size(); ++row) {
        for (int col = 0; (unsigned)col < mat[row].size(); ++col) {
            int p = mat[row][col]-'0';

            // local min
            if (all_of(begin(dir), end(dir), [&](auto d){return get_neighbor(mat, row+d.first, col+d.second) > p;})){
                vector<Point> basin;
                add_neighbors(basin, mat, row, col);
                basin_sizes.push_back(basin.size());
            }
        }
    }

    sort(begin(basin_sizes), end(basin_sizes), [](auto a, auto b){return a > b;});

    cout << "three largest basin sizes: " << basin_sizes.at(0) << " " << basin_sizes.at(1) << " " << basin_sizes.at(2) << "\n";
    cout << "product: " << basin_sizes.at(0)*basin_sizes.at(1)*basin_sizes.at(2) << "\n";
    return 0;
}

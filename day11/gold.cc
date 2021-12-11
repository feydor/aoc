#include <algorithm>
#include <numeric>
#include <vector>
#include <map>
#include <iostream>
#include <stack>
using namespace std;

#define STEPS 400

// 8 directions
vector<pair<int, int>> d = {{-1, -1}, {-1, 0}, {-1, 1},
							{0, 1}, {1, 1}, {1, 0},
							{1, -1}, {0, -1}};

vector<pair<int, int>> get_neighbors(const vector<string> &mat, int row, int col) {
    vector<pair<int, int>> neighbors;
    for (const auto &[dy, dx] : d) {
        int y = row+dy, x = col+dx;
        if (x >= 0 && (unsigned)x < mat[0].size() && y >= 0 && (unsigned)y < mat.size())
            neighbors.push_back(make_pair(y, x));
    }
    return neighbors;
}

void print_mat(const vector<string> &mat) {
	for (const auto &line : mat) {
		for (const char &c : line) {
			cout << c-'0' << ",";
		}
		cout << endl;
	}
}

char inc_char_num(char c) {
	return c-'0' + 1 + '0';
}

// returns true if the vector v holds a point with the same coordinates as p
bool in_vec(const vector<pair<int, int>> &v, int row, int col) {
    return any_of(begin(v), end(v), [&](auto other){ return other.first == row && other.second == col;});
}

void flash(vector<pair<int, int>> &flashed, vector<string> &mat, uint64_t &flashes, int row, int col) {
	flashed.push_back(make_pair(row, col));
	auto neighbors = get_neighbors(mat, row, col);
	for (auto &[nrow, ncol] : neighbors) {
		if (!in_vec(flashed, nrow, ncol)) {
			mat[nrow][ncol] = mat[nrow][ncol]-'0' + 1 + '0';
			if (mat[nrow][ncol]-'0' > 9) {
				flashes++;
				flash(flashed, mat, flashes, nrow, ncol);
				mat[nrow][ncol] = '0';
			}
		}
	}
}

int main() {
    string str;
    vector<string> mat(istream_iterator<string>(cin), istream_iterator<string>(), {});

	print_mat(mat);
	
	uint64_t flashes = 0;
	for (size_t step = 0; step < STEPS; ++step) {
		// increment each energy by 1
		// then any energy > 9 flashes, this increases the energy of every neighbor by 1 (even diagonally adjacent ones)
		// if that causes an energy to be greater than 9, it also flashes
		// then any energy that flashed is set to 0
		vector<pair<int, int>> flashed; // each energgy can only flash once per turn
		for (auto &line : mat)
			transform(begin(line), end(line), begin(line), [](char c){ return '0' + ((c-'0') + 1); });
		
		for (size_t row = 0; row < mat.size(); ++row) {
			for (size_t col = 0; col < mat[row].size(); ++col) {
				if (mat[row][col]-'0' > 9) {
					if (!in_vec(flashed, row, col)) {
						flash(flashed, mat, flashes, row, col);
						++flashes;
					}
					mat[row][col] = '0';
				}
			}
		}

		// get the step where all energies flash (if change in flash == #of energies)
		if (all_of(begin(mat), end(mat), [](string line){
			return all_of(begin(line), end(line), [](char c){return c == '0';});
		})) {
			cout << "step: " << step+1 << endl;
			break;
		}

		flashed.clear();
		cout << "after flash: \n";
		print_mat(mat);
		cout << flashes << endl;
	}

	cout << flashes << endl;

    return 0;
}

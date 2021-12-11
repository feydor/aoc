/** day 11 part 2 - find the first step during which all octopuses flash */
#include <algorithm>
#include <numeric>
#include <vector>
#include <iostream>
using namespace std;

#define STEPS 400
#define ALL 100
#define plus_one(c) (c-'0'+1+'0')

// 8 directions
vector<pair<int, int>> d = {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}};

vector<pair<int, int>> get_neighbors(const vector<string> &mat, int row, int col) {
    vector<pair<int, int>> neighbors;
    for (const auto &[dy, dx] : d) {
        int y = row+dy, x = col+dx;
        if (x >= 0 && (unsigned)x < mat[0].size() && y >= 0 && (unsigned)y < mat.size())
            neighbors.push_back(make_pair(y, x));
    }
    return neighbors;
}

bool visited(const vector<pair<int, int>> &v, int row, int col) {
    return any_of(begin(v), end(v), [&](auto other){ return other.first == row && other.second == col;});
}

uint64_t flash(vector<pair<int, int>> &flashed, vector<string> &mat, int row, int col) {
	flashed.push_back(make_pair(row, col));
	uint64_t flashes = 0;
	for (auto &[nrow, ncol] : get_neighbors(mat, row, col)) {
		if (!visited(flashed, nrow, ncol)) {
			mat[nrow][ncol] = plus_one(mat[nrow][ncol]);
			if (mat[nrow][ncol]-'0' > 9) {
				++flashes;
				flashes += flash(flashed, mat, nrow, ncol);
				mat[nrow][ncol] = '0';
			}
		}
	}
	return flashes;
}

int main() {
    vector<string> mat(istream_iterator<string>(cin), istream_iterator<string>(), {});

	uint64_t flashes = 0;
	for (size_t step = 0; step < STEPS; ++step) {
		vector<pair<int, int>> flashed;
		for (auto &line : mat)
			transform(begin(line), end(line), begin(line), [](char c){ return plus_one(c); });
		
		for (size_t row = 0; row < mat.size(); ++row) {
			for (size_t col = 0; col < mat[row].size(); ++col) {
				if (mat[row][col]-'0' > 9) {
					++flashes;
					flashes += flash(flashed, mat, row, col);
					mat[row][col] = '0';
				}
			}
		}

		// get the step where all energies flash
		if (flashed.size() == ALL) {
			cout << "step: " << step+1 << endl;
			break;
		}
	}

	cout << "flashes: " << flashes << endl;
    return 0;
}

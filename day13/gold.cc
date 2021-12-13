/** day13 - Transparent Origami */
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
using namespace std;
#define SIZE 1312 // the maximum value of the input + padding

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

bool get(bool *mat, int row, int col) {
	return mat[row + col*SIZE];
}

void set(bool *mat, int row, int col) {
	mat[row + col*SIZE] = true;
}

void clear(bool *mat, int row, int col) {
	mat[row + col*SIZE] = false;
}

void fold_x(bool *mat, int n) {
	// start at fold line
	// shift left
	for (size_t row = 0; row < SIZE; ++row) {
		int col_count = 0;
		for (size_t col = n; col < SIZE; ++col) {
			bool is_set = get(mat, row, col);
			if (is_set) {
				clear(mat, row, col);
				set(mat, row , col-col_count);
			}
			col_count +=2;
		}
	}
}

void fold_y(bool *mat, int n) {
	// start at fold line
	// shift up
	int row_count = 0;
	for (size_t row = n; row < SIZE; ++row) {
		for (size_t col = 0; col < SIZE; ++col) {
			if (get(mat, row, col)) {
				clear(mat, row, col);
				set(mat, row-row_count, col);
			}
		}
		row_count += 2;
	}
}

void print_mat(bool *mat) {
	for (size_t row = 0; row < 10; ++row) {
		for (size_t col = 0; col < 50; ++col) {
			cout << (get(mat, row, col) ? "X" : ".");
		}
		cout << "\n";
	}
}

int n_visible(bool *mat) {
	int count = 0;
	for (size_t r = 0; r < SIZE; ++r) {
		for (size_t c = 0; c < SIZE; ++c) {
			count += get(mat, r, c) ? 1 : 0;
		}
	}
	return count;
}

// silver: 716
// gold: RPCKFBLR
int main() {
	string line;
	bool *mat = new bool[SIZE*SIZE];
	vector<string> instructions;
	while (getline(cin, line)) {
		if (line.empty()) continue;
		if (line[0] == 'f') {
			instructions.push_back(line);
		} else {
			auto coord = split(line, ',');
			set(mat, stoi(coord[1]), stoi(coord[0]));
		}
	}

	for (auto& instr : instructions) {
		auto tokens = split(instr);
		auto equals_sign = tokens[2].find('=');
		int n = stoi(tokens[2].substr(equals_sign+1));
		
		if (tokens[2][0] == 'y') {
			fold_y(mat, n);
		} else {
			fold_x(mat, n);
		}
	}

	cout << "dots: " << n_visible(mat) << endl;
	print_mat(mat);

	delete[] mat;
	return 0;
}

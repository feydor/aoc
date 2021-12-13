/** day13 - Transparent Origami */
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
#include "bit_matrix.h"
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

// silver: 716
// gold: RPCKFBLR
int main() {
	string line;
	bit_matrix mat(SIZE);
	vector<string> instructions;
	while (getline(cin, line)) {
		if (line.empty()) continue;
		if (line[0] == 'f') {
			instructions.push_back(line);
		} else {
			auto coord = split(line, ',');
			mat.set(stoi(coord[1]), stoi(coord[0]));
		}
	}

	for (auto& instr : instructions) {
		auto tokens = split(instr);
		auto equals_sign = tokens[2].find('=');
		int n = stoi(tokens[2].substr(equals_sign+1));

		if (tokens[2][0] == 'y') {
			mat.fold_y(n);
		} else {
			mat.fold_x(n);
		}
	}

	cout << "dots: " << mat.n_set() << endl;
	cout << mat << endl;

	return 0;
}

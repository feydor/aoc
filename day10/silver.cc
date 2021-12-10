#include <algorithm>
#include <numeric>
#include <vector>
#include <map>
#include <iostream>
#include <stack>
using namespace std;

#define MAXLINESIZE 1000

map<char, int> illegals = {{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
map<char, char> closers = {{'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'}};

// 539
int main() {
    string str;
    vector<string> mat;
    while (getline(cin, str)) {
        mat.push_back(str);
    }

	int error_score = 0;
	stack<int> loc;
	for (const auto &line : mat) {
		for (unsigned cp = 0; cp < line.size(); ++cp) {
			if (line[cp] == '[' || line[cp] == '(' || line[cp] == '{' || line[cp] == '<') {
				loc.push(cp); // store location of opening
			}
			if (line[cp] == ']' || line[cp] == ')' || line[cp] == '}' || line[cp] == '>') {
				if (loc.empty()) {
					// TODO: incomplete pair
				} else {
					char opener = line[loc.top()];
					loc.pop();
					if (closers[opener] != line[cp]) {
						cout << "syntax error: expected " << closers[opener] << " but found " << line[cp] << " : pos " << cp << "\n";
						error_score += illegals[line[cp]];
						break; // only count the first error in each line
					}
				}
			}
		}
	}
	if (loc.size() > 0) {
		cout << "unmatched pairs remaining\n";
	}

	cout << error_score << endl;
    return 0;
}

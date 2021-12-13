#include <algorithm>
#include <vector>
#include <map>
#include <iostream>
#include <stack>
using namespace std;

map<char, int> score_mismatch = {{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
map<char, char> closer = {{'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'}};
map<char, int> score_closer = {{')', 1}, {']', 2}, {'}', 3}, {'>', 4}};

int main() {
    string l;
    vector<string> mat;
    while (getline(cin, l)) {
        mat.push_back(l);
    }

    int error_score = 0;
    stack<int> loc;
    vector<uint64_t> completion_scores;
    for (const auto &line : mat) {
        for (size_t cp = 0; cp < line.size(); ++cp) {
            if (line[cp] == '[' || line[cp] == '(' || line[cp] == '{' || line[cp] == '<') {
                loc.push(cp);
            }
            if (line[cp] == ']' || line[cp] == ')' || line[cp] == '}' || line[cp] == '>') {
                if (loc.empty()) {
                    throw invalid_argument("Unmatched opener.");
                } else {
                    char opener = line[loc.top()];
                    loc.pop();
                    if (closer[opener] != line[cp]) {
                        error_score += score_mismatch[line[cp]];
                        while (loc.size()) loc.pop(); // clean up stack
                        break; // ignore further errors on this line
                    }
                }
            }
        }

        // complete and score unmatched pairs
        if (loc.size() > 0) {
            string unmatched;
            while (loc.size()) {
                unmatched += line[loc.top()];
                loc.pop();
            }

            uint64_t score = 0;
            for (const auto &c : unmatched)
                score = score * 5 + score_closer[closer[c]];
            completion_scores.push_back(score);
        }
    }

    sort(begin(completion_scores), end(completion_scores));
    cout << "silver: " << error_score << endl;
    cout << "gold: " << completion_scores[completion_scores.size()/2] << endl;
    return 0;
}

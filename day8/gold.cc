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

#define OUTPUT_SIZE 4 

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

bool is_anagram(string a, string b) {
    if (a.size() == b.size()) {
        sort(begin(a), end(a));
        sort(begin(b), end(b));
        return a == b;
    }
    return false;
}

// 908067
int main() {
    string line;
    char missing_segment_of_nine;
    char missing_segment_of_six;

    uint64_t total_sum = 0;
    while (getline(cin, line)) {
        auto delim = line.find('|');
        if (delim == string::npos) throw invalid_argument("'|' not found.");

        auto input_data = line.substr(0, delim-1);
        auto output_data = line.substr(delim+2);
        auto inputs = split(input_data);

        // sort by len sizes: 2, 3, 4, 5, 5, 5, 6, 6, 6, 7
        sort(begin(inputs), end(inputs), [](auto a, auto b){ return a.size() < b.size(); });
 
        // get the uniques [num, len] ([n: 1, l: 2], [n: 7, l: 3], [n: 4, l: 4], and [n: 8, l: 7])
        map<int, string> digits;
        digits[1] = inputs[0];
        digits[4] = inputs[2];
        digits[7] = inputs[1];
        digits[8] = inputs[9];

        // move the rest (non-uniques) to the front and erase the uniques
        auto pivot = stable_partition(begin(inputs), end(inputs),
        [](string s){ return s.size() == 5 || s.size() == 6; });
        inputs.erase(pivot, end(inputs));

        // inputs: 5, 5, 5, 6, 6, 6
        // work on len 6 strings
        for (size_t i = 3; i < inputs.size(); ++i) {
            // get the set difference between "abcdefg" and current 6-len input
            string str = inputs[i];
            sort(begin(str), end(str));
            string legend = "abcdefg";
            string missing_segment; // should be char, but char doesn't have back_inserter
            set_difference(begin(legend), end(legend), begin(str), end(str), back_inserter(missing_segment));

            // 0 is the one whose missing segment is in all three len 5 nums
            // 6 is the one whose missing segment is in exactly two len 5 nums
            // 9 is the one whose missing segment is in exactly one len 5 num
            int matches = 0;
            for (auto j = 0; j < 3; ++j) {
                auto six_len = inputs[j];
                auto result = find(begin(six_len), end(six_len), missing_segment[0]);
                if (result != six_len.end()) {
                    matches++;
                }
            }

            if (matches == 3) {
                digits[0] = str;
            } else if (matches == 2) {
                digits[6] = str;
                missing_segment_of_six = missing_segment[0];
            } else if (matches == 1) {
                digits[9] = str;
                missing_segment_of_nine = missing_segment[0];
            }
        }

        // resize inputs vector to hold only three remaining 5 lens
        inputs.resize(3);

        // inputs: 5, 5, 5
        // work on 5 len nums
        // 2 is the one that containes the missing segment of 9
        auto res_1 = find(begin(inputs[0]), end(inputs[0]), missing_segment_of_nine);
        auto res_2 = find(begin(inputs[1]), end(inputs[1]), missing_segment_of_nine);
        auto res_3 = find(begin(inputs[2]), end(inputs[2]), missing_segment_of_nine);

        if (res_1 != end(inputs[0])) {
            digits[2] = inputs[0];
        } else if (res_2 != end(inputs[1])) {
            digits[2] = inputs[1];
        } else if (res_3 != end(inputs[2])) {
            digits[2] = inputs[2];
        }

        // remove two from inputs
        remove(begin(inputs), end(inputs), digits[2]);
        inputs.resize(2);

        if (inputs.size() != 2) throw invalid_argument("vector is not size 2 after finding two.");
        // inputs: 5, 5
        // 3 is the one that is not 2 and contains the missing segment of 6
        // 5 is the last remaining one
        auto r1 = find(begin(inputs[0]), end(inputs[0]), missing_segment_of_six);
        auto r2 = find(begin(inputs[1]), end(inputs[1]), missing_segment_of_six);
        if (r1 != end(inputs[0])) {
            digits[3] = inputs[0];
            digits[5] = inputs[1];
        } else if (r2 != end(inputs[1])) {
            digits[3] = inputs[1];
            digits[5] = inputs[0];
        }

        // interpret outputs with digits map
        uint64_t sum = 0;
        int pos = OUTPUT_SIZE-1;
        for (const auto &output : split(output_data)) {
            for (const auto &[n, segments] : digits) {
                if (is_anagram(output, segments)) {
                    sum += (pow(10, pos) * n);
                    pos--;
                    break;
                }
            }
        }
        total_sum += sum;
    }

    cout << total_sum << endl;
    return 0;
}

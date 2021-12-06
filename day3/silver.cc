#include <bitset>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

bool most_common(const vector<uint64_t> &v, int pos) {
    // count ones in position pos
    int ones = 0;
    for (const auto &x : v)
        ones += 1 & (x >> pos);
    
    return ones >= v.size()/2;
}

// 1082324
int main(int argc, char **argv) {
    string line;
    vector<uint64_t> v;
    size_t bit_len = 0;
    while (getline(cin, line)) {
        v.push_back(stoi(line, nullptr, 2));
        if (bit_len == 0)
            bit_len = line.size();
    }
    
    // gamma = 2^pos * most common in v[pos]
    int64_t gamma = 0;
    for (int pos = bit_len-1; pos >= 0; --pos)
        gamma += (pow(2, pos) * most_common(v, pos));

    // epsilon = gamma's bits flipped
    int64_t epsilon = gamma;
    for (int pos = bit_len-1; pos >= 0; --pos)
        epsilon = epsilon ^ (1 << pos);

    cout << gamma * epsilon << "\n";
    return 0;
}
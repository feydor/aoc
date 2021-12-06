#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

int to_int(uint64_t n, int bit_len) {
    int result = 0;
    for (int pos = bit_len-1; pos >= 0; --pos)
        result += pow(2, pos) * ((n >> pos) & 1);
    return n;
}

auto filter(const vector<uint64_t> &v, int pos, bool most_common) {
    // count ones in position pos
    int ones = 0;
    for (const auto &x : v)
        ones += 1 & (x >> pos);
    
    int zeros = v.size() - ones;
    
    vector<uint64_t> filtered;
    copy_if(begin(v), end(v), back_inserter(filtered), [&](uint64_t n){
        auto bit_at_pos = (1 & (n >> pos));
        if (most_common)
            return ones >= zeros ? bit_at_pos == 1 : bit_at_pos == 0;
        else
            return ones >= zeros ? bit_at_pos == 0 : bit_at_pos == 1;
    });
    return filtered;
}

// 1353024
int main() {
    string line;
    vector<uint64_t> v;
    size_t bit_len = 0;
    while (getline(cin, line)) {
        v.push_back(stoull(line, nullptr, 2));
        if (bit_len == 0)
            bit_len = line.size();
    }
    
    // filter through numbers that match most_common bit at position pos
    vector<uint64_t> oxy = v;
    vector<uint64_t> co2 = v;
    for (int pos = bit_len-1; pos >= 0; --pos) {
        if (oxy.size() > 1)
            oxy = filter(oxy, pos, true);
        if (co2.size() > 1)
            co2 = filter(co2, pos, false);
    }

    cout << oxy[0] << endl;
    cout << co2[0] << endl;
    cout << oxy[0] * co2[0] << endl;
}
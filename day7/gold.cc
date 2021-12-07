
#include <algorithm>
#include <cmath>
#include <cstring>
#include <numeric>
#include <vector>
#include <iostream>
#include <numeric>
#include <sstream>
using namespace std;

auto diff = [](auto a, auto b){ return (a > b) ? a - b : b - a; };
auto additive_fact = [](auto n){return n*(n+1)/2;};
auto cost = [](auto c, auto pos){ return additive_fact(diff(pos, c));};

// 90040997
int main() {
    string str;
    getline(cin, str);

    vector<uint64_t> data;
    stringstream ss(str);
    while (getline(ss, str, ','))
        data.push_back(stoul(str));

    // convergence to mean
    sort(begin(data), end(data));
    uint64_t mean = accumulate(begin(data), end(data), 0) / (data.size()*1.0);
    auto mean_range = make_pair(mean, mean+1);
    auto fuels = make_pair(0ul, 0ul);

    for (const auto &x : data) {
        fuels.first += cost(mean_range.first, x);
        fuels.second += cost(mean_range.second, x);
    }

    cout << min(fuels.first, fuels.second) << endl;
    return 0;
}

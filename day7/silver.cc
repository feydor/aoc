
#include <algorithm>
#include <cstring>
#include <numeric>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

// 328262
int main() {
    string str;
    getline(cin, str);

    vector<uint64_t> data;
    stringstream ss(str);
    while (getline(ss, str, ',')) {
        data.push_back(stoull(str));
    }

    // convergence to median (test both floor and ceil)
    sort(begin(data), end(data));
    int mid = data.size()/2;
    auto median_range = make_pair(data[mid], data[mid+1]);
    auto fuels = make_pair(0ul, 0ul);

    auto distance = [](auto a, auto b){ return max(a, b) - min(a, b); };
    for (const auto &x : data) {
        fuels.first += distance(median_range.first, x);
        fuels.second += distance(median_range.second, x);
    }

    cout << min(fuels.first, fuels.second) << endl;
    return 0;
}


#include <algorithm>
#include <cstring>
#include <numeric>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

// 90040997
int main() {
    string str;
    getline(cin, str);

    vector<int> data;
    stringstream ss(str);
    while (getline(ss, str, ',')) {
        data.push_back(stoi(str));
    }

    sort(begin(data), end(data));
    auto min = data.front();
    auto max = data.back();
    vector<int> fuels(max - min, 0);

    // from min to max
    uint64_t min_fuel = UINT64_MAX;
    for (int dest = min; dest < max; ++dest) {
        int fuel = 0;
        for (const auto &x : data) {
            auto n = abs(dest - x);
            fuel += n*(n+1)/2;
        }
        if (fuel < min_fuel) {
            min_fuel = fuel;
        }
    }

    cout << min_fuel << endl;
    return 0;
}


#include <algorithm>
#include <cmath>
#include <cstring>
#include <numeric>
#include <vector>
#include <iostream>
#include <numeric>
#include <sstream>
using namespace std;

// 90040997
int main() {
    string str;
    getline(cin, str);

    vector<uint64_t> data;
    stringstream ss(str);
    while (getline(ss, str, ','))
        data.push_back(stoull(str));

    // find total average
    double total_avg = accumulate(begin(data), end(data), 0) / (data.size()*1.0);

    // do floor and ciel
    uint64_t fl = floor(total_avg);
    uint64_t cl = ceil(total_avg);
    uint64_t fuel_fl = 0;
    uint64_t fuel_cl = 0;
    for (const auto &x : data) {
        auto n_fl = max(fl, x) - min(fl, x);
        auto n_cl = max(cl, x) - min(cl, x);
        fuel_fl += n_fl*(n_fl+1)/2;
        fuel_cl += n_cl*(n_cl+1)/2;
    }
    cout << min(fuel_fl, fuel_cl) << endl;
    return 0;
}

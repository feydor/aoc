
#include <algorithm>
#include <cstring>
#include <numeric>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

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
    for (int dest = min; dest < max; ++dest) {
        int fuel = 0;
        for (int i = 0; i < data.size(); ++i) {
            fuel += abs(dest - data[i]);
        }
        fuels[dest] = fuel;
    }

    cout << *min_element(begin(fuels), end(fuels)) << endl;
    return 0;
}

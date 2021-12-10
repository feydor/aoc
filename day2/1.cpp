#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <fstream>
#include <map>
#include <numeric>
#include <vector>
using namespace std;

int gold(const vector<pair<char, int>> &cmds) {
    int horiz = 0, depth = 0, aim = 0;
    for (const auto &[cmd, x] : cmds) {
        switch (cmd) {
            case 'f': {
                horiz += x;
                depth += aim * x;
            }
            break;
            case 'u': aim -= x; break;
            case 'd': aim += x; break;
            default: throw invalid_argument("not a command:" + cmd);
        }
    }
    return horiz*depth;
}

int silver(const vector<pair<char, int>> &cmds) {
    int horiz = 0, depth = 0;
    for (const auto &[cmd, x] : cmds) {
        switch (cmd) {
            case 'f': horiz += x; break;
            case 'u': depth -= x; break;
            case 'd': depth += x; break;
            default: throw invalid_argument("not a command:" + cmd);
        }
    }
    return horiz*depth; 
}

// 1: 2322630, 2: 2105273490
int main() {
    string str;
    vector<pair<char, int>> cmds;
    while (getline(cin, str))
        cmds.emplace_back(str[0], str.back() - '0');
    
    cout << silver(cmds) << "\n" << gold(cmds) << "\n";
    return 0;
}

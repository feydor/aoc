
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstring>
#include <numeric>
#include <map>
#include <vector>
#include <iostream>
#include <numeric>
#include <sstream>
using namespace std;


int main() {
    string legend = "abcdefg";
    string six_len = "bcdefg";
    string missing;
    sort(begin(six_len), end(six_len));
    set_difference(begin(legend), end(legend), begin(six_len), end(six_len), back_inserter(missing));
    cout << missing << endl;
    return 0;
}

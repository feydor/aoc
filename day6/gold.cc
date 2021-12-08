
#include <cstring>
#include <numeric>
#include <array>
#include <iostream>
using namespace std;

#define DAYS 256 // silver is 80
#define TTL 8

// 1728611055389
int main() {
    string str;
    array<uint64_t, TTL+1> ttl{};
    while (getline(cin, str, ',')) {
        ttl[stoi(str)]++;
    }

    for (size_t day = 0; day < DAYS; ++day) {
        auto dead = ttl[0];
        
        for (size_t t = 1; t < ttl.size(); ++t)
            ttl[t-1] = ttl[t];

        ttl[6] += dead;
        ttl[8] = dead;
    }

    cout << reduce(begin(ttl), end(ttl), 0l) << endl;
    return 0;
}

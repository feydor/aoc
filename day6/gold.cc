
#include <numeric>
#include <array>
#include <iostream>
using namespace std;

#define DAYS 256
#define TTL 8

int main() {
    string str;
    array<uint64_t, TTL+1> ttl{};
    while (getline(cin, str, ',')) {
        ttl[stoi(str)]++;
    }

    for (size_t day = 0; day < DAYS; ++day) {
        auto dead = ttl[0];

        for (auto t = begin(ttl)+1; t != end(ttl); ++t)
            *(t-1) = *t;

        ttl[6] += dead;
        ttl[8] = dead;
    }

    cout << reduce(begin(ttl), end(ttl), 0l) << endl;
    return 0;
}

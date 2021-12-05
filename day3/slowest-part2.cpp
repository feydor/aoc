#include <algorithm>
#include <bitset>
#include <cmath>
#include <bitset>
#include <fstream>
#include <iostream>
#include <vector>

const auto BIT_LEN = 12;

struct results {
    uint64_t oxy;
    uint64_t co2;
    friend std::ostream &operator<<(std::ostream &s, const results &r) {
        s << r.oxy << " : " << r.co2;
        return s;
    }
};

template <std::size_t len>
uint64_t most_common(const std::vector<std::bitset<len>> &vec, int bit_pos) {
    uint64_t ones = 0;
    auto mask_bit_pos = std::bitset<len>(1 << bit_pos);
    for (auto i = 0; i < vec.size(); ++i) {
        std::cout << vec[i].to_string() << std::endl;
    }
    std::cout << std::endl;

    for (int i = 0; i < vec.size(); ++i)
        ones += std::bitset<len>(vec[i] & mask_bit_pos).to_ullong(); // extract the the bit_pos from lines and sum up (ones)

    ones >>= bit_pos; // divide by 2^bit_pos (convert back to decimal)

    return ones > (vec.size() / 2); // more ones than zeros
}

uint64_t find_oxy(auto begin, auto end, int index) {
    if (end - begin == 1 || index == -1)
        return begin->to_ulong();
    auto pivot = std::partition(begin, end, [index](auto &bits){ return bits[index] == 1; });
    
    // more ones
    if (std::distance(begin, pivot) >= std::distance(pivot, end))
        return find_oxy(begin, pivot, index-1);
    else
        return find_oxy(pivot, end, index-1);
}

uint64_t find_co2(auto begin, auto end, int index) {
    if (end - begin == 1 || index == -1)
        return begin->to_ulong();
    auto pivot = std::partition(begin, end, [index](auto &bits){ return bits[index] == 1; });
    
    // less ones
    if (std::distance(begin, pivot) < std::distance(pivot, end) || pivot == end)
        return find_oxy(begin, pivot, index-1);
    else
        return find_oxy(pivot, end, index-1);
}

template <size_t width>
results solve(std::vector<std::bitset<width>> &data) {
    // move ones before zeros
    auto pivot = std::partition(data.begin(), data.end(), [](auto &bits) { return bits[width-1] == 1; });
    
    // all ones
    if (pivot == data.end()) {
        auto oxy = find_oxy(data.begin(), data.end(), width-2);
        auto co2 = find_co2(data.begin(), data.end(), width-2);
        return { .oxy = oxy, .co2 = co2 };
    } else if (std::distance(data.begin(), pivot) >= std::distance(pivot, data.end())) {
        // more ones
        auto oxy = find_oxy(data.begin(), pivot, width-2);
        auto co2 = find_co2(pivot, data.end(), width-2);
        return { .oxy = oxy, .co2 = co2 };
    } else {
        // more zeros
        auto oxy = find_oxy(pivot, data.end(), width-2);
        auto co2 = find_co2(data.begin(), pivot, width-2);
        return { .oxy = oxy, .co2 = co2 };
    }
}

int main(int argc, char **argv) {
    std::ifstream file(argv[1]);
    std::vector<std::bitset<BIT_LEN>> vec;
    std::copy(std::istream_iterator<std::bitset<BIT_LEN>>(file), std::istream_iterator<std::bitset<BIT_LEN>>(),
              std::back_inserter(vec));
    
    auto res = solve(vec);
    std::cout << res << std::endl;
    std::cout << "res: " << res.oxy * res.co2 << std::endl;
}
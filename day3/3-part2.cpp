#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <concepts>
#include <cmath>
#include <iostream>
#include <iterator>
#include <fstream>
#include <numeric>
#include <vector>

const auto NBITS = 12;
typedef std::vector<std::bitset<NBITS>> bit_matrix_t;

int to_integer(const std::vector<bool> &v) {
    int result = 0;
    auto SIZE = v.size();
    for (auto i = 0; i < SIZE; ++i)
        result += (std::pow(2, SIZE-i-1) * (v[i] ? 1 : 0));
    return result;
}

bool find_most_common(const bit_matrix_t &bit_matrix, int bit_pos) {
    const size_t NBITS = bit_matrix[0].size();
    int ones = 0, zeros = 0;
    for (const auto &line : bit_matrix)
        line[bit_pos] ? ++ones : ++zeros;
    
    return ones >= zeros;
}

template <typename UnaryPredicate>
bit_matrix_t filter(const bit_matrix_t &bmat, UnaryPredicate p) {
    bit_matrix_t filtered;
    std::copy_if(bmat.begin(), bmat.end(), std::back_inserter(filtered), p);
    return filtered;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Argument missing.\n";
        return 1;
    }

    // parse 12bit num per line
    std::ifstream file(argv[1]);
    std::vector<std::string> lines;
    std::copy(std::istream_iterator<std::string>(file), std::istream_iterator<std::string>(),
              std::back_inserter(lines));

    bit_matrix_t bit_matrix;
    std::transform(lines.begin(), lines.end(), std::back_inserter(bit_matrix), [](auto line) {
        std::bitset<NBITS> bits;
        for (const auto& ch : line) bits <<= ch == '1' ? 0b1 : 0b0;
        // std::transform(line.begin(), line.end(), std::back_inserter(bits), [](char ch)
        // { return ch == '1'; });
        return bits;
    });

    for (const auto &bits : bit_matrix)
        std::cout << bits.to_string() << std::endl;
    
    // filter through numbers that match most_common
    const size_t NBITS = bit_matrix[0].size();
    bit_matrix_t filtered_bit_matrix = bit_matrix;
    for (int round = 0; round < NBITS; ++round) {
        if (filtered_bit_matrix.size() == 1) break;
        auto most_common = find_most_common(filtered_bit_matrix, round);
        filtered_bit_matrix = filter(filtered_bit_matrix, [round, most_common](auto line)
        { return line[round] == most_common; });
    }

    auto oxy_gen = to_integer(filtered_bit_matrix[0]);

    // filter through least common
    filtered_bit_matrix = bit_matrix;
    for (int round = 0; round < NBITS; ++round) {
        if (filtered_bit_matrix.size() == 1) break;
        auto most_common = find_most_common(filtered_bit_matrix, round);
        filtered_bit_matrix = filter(filtered_bit_matrix, [round, most_common](auto line)
        { return line[round] != most_common; });
    }

    auto c02 = to_integer(filtered_bit_matrix[0]);
    std::cout << c02 << std::endl;
    std::cout << oxy_gen << std::endl;
    std::cout << "multiplied: " << oxy_gen * c02 << std::endl;
}
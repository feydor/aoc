#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iterator>
#include <fstream>
#include <numeric>
#include <vector>

template<std::size_t SIZE>
int to_integer(const std::array<int, SIZE> &a) {
    int result = 0;
    for (auto i = 0; i < SIZE; ++i)
        result += (std::pow(2, SIZE-i-1) * a[i]);
    return result;
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

    std::vector<std::vector<bool>> bit_matrix;
    std::transform(lines.begin(), lines.end(), std::back_inserter(bit_matrix), [](auto line) {
        std::vector<bool> bits;
        std::transform(line.begin(), line.end(), std::back_inserter(bits), [](char ch) {
            return ch == '1';
        });
        return bits;
    });

    const size_t NBITS = 12;
    std::array<int, NBITS> gamma{};
    std::array<int, NBITS> epsilon{};
    std::array<int, NBITS> ones{};
    std::array<int, NBITS> zeros{};
    
    // get gamma by traversing downwards column wise
    for (const auto &line : bit_matrix)
        for (auto i = 0; i < line.size(); ++i)
            line[i] ? ++ones[i] : ++zeros[i];

    for (auto i = 0; i < NBITS; ++i) {
        gamma[i] = (ones[i] > zeros[i]) ? 1 : 0;
        epsilon[i] = gamma[i] ? 0 : 1;
    }

    auto power = to_integer(gamma) * to_integer(epsilon);
    std::cout << power << std::endl;
}
#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

const auto BIT_LEN = 40;

auto filter(const std::vector<std::string> &nums, int pos, bool most_common) {
    int ones = 0, zeros = 0;
    for (const auto &str : nums)
        str[pos] == '1' ? ++ones : ++zeros;

    std::vector<std::string> filtered;
    std::copy_if(nums.begin(), nums.end(), std::back_inserter(filtered), [&](auto str){
        if (most_common)
            return ones >= zeros ? str[pos] == '1' : str[pos] == '0';
        else
            return ones >= zeros ? str[pos] == '0' : str[pos] == '1';
    });
    return filtered;
}

int main(int argc, char **argv) {
    std::ifstream file(argv[1]);
    std::vector<std::string> lines;
    std::copy(std::istream_iterator<std::string>(file), std::istream_iterator<std::string>(),
              std::back_inserter(lines));

    std::vector<std::string> oxygen_list(lines);
    std::vector<std::string> c02_list(lines);
    for (int round = 0; round < BIT_LEN; ++round) {
        if (oxygen_list.size() > 1)
            oxygen_list = filter(oxygen_list, round, true);
        if (c02_list.size() > 1)
            c02_list = filter(c02_list, round, false);
    }

    std::vector<int> v(10, 1);
    v.erase(v.begin() + v.back());

    auto oxy = std::bitset<BIT_LEN>(oxygen_list[0]).to_ulong();
    auto c02 = std::bitset<BIT_LEN>(c02_list[0]).to_ulong();
    std::cout << oxy << "\n";
    std::cout << c02 << "\n";
    std::cout << oxy * c02 << std::endl;
}
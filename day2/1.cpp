#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <fstream>
#include <map>
#include <numeric>
#include <vector>

typedef std::vector<std::pair<std::string, int>> instructions_t;
typedef std::pair<std::string, int> instruction_t;

auto adjacent_pairs(const std::vector<std::string> &lines) {
    instructions_t is;
    for (auto itr = lines.begin()+1; itr != lines.end()-1; itr += 2) {
        is.push_back({*(itr-1), std::stoi(*itr)});
    }
    is.push_back({*(lines.end()-2), std::stoi(lines.back())}); // last instruction
    return is;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Argument missing.\n";
        return 1;
    }

    // parse instructions
    std::ifstream file(argv[1]);
    std::vector<std::string> lines;
    std::copy(std::istream_iterator<std::string>(file), std::istream_iterator<std::string>(),
        std::back_inserter(lines));

    auto instructions = adjacent_pairs(lines);

    // execute instructions
    int horiz = 0, depth = 0, aim = 0;
    for (const auto& i : instructions) {
        switch (i.first[0]) {
            case 'f': {
                horiz += i.second;
                depth += (aim * i.second);
            } break;
            case 'u': aim -= i.second; break;
            case 'd': aim += i.second; break;
            default: throw std::invalid_argument("Not a command.");
        }
    }

    std::cout << "(horiz, depth) :: (" << horiz << ", " << depth << ")\n";
    std::cout << "multiplied: " << horiz * depth << "\n";
}
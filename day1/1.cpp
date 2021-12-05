#include <algorithm>
#include <concepts>
#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>


int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Argument missing.\n";
        return 1;
    }

    // load file
    std::ifstream input_file (argv[1]);
    if (!input_file.is_open()) {
        std::cerr << "File failed to open.\n";
        return 1;
    }

    // parse file into data
    std::vector<int> data;
    std::string line;
    while (getline(input_file, line))
        data.push_back(std::stoi(line));

    int incs = 0;
    for (auto i = 3; i < data.size(); ++i) {
        /* because summation is associative simply compare the individual parts */
        incs += (data[i] > data[i-3]);
        // old way
        // auto next = std::reduce(data.begin() + i + 1, data.begin() + i + 4);
        // auto curr = std::reduce(data.begin() + i, data.begin() + i + 3);
        // if (next > curr)
        //     ++n;
    }

    std::cout << "part 2: " << incs << std::endl;

    return 0;
}
#include <algorithm>
#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>

/* returns the number of times v[i] is greater than v[i-n] for all of v */
int incs(std::vector<int> &v, int n) {
    /* forall in v, incs += (v[i] > v[i-n]) */
    return std::transform_reduce(std::begin(v)+n, std::end(v), std::begin(v), 0, std::plus<int>{},
        std::greater<int>{});
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Argument missing.\n";
        return 1;
    }

    std::ifstream file(argv[1]);

    std::vector<int> x;
    std::copy(std::istream_iterator<int>(file), std::istream_iterator<int>(), std::back_inserter(x));
    std::cout << "part 1: " << incs(x, 1) << "\npart 2: " << incs(x, 3) << "\n";
}
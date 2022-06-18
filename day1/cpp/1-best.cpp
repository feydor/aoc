#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

/* returns the number of times v[i] is greater than v[i-n] for all of v */
int incs(vector<int> &v, int n) {
    return transform_reduce(begin(v)+n, end(v), begin(v), 0, plus<int>{}, greater<int>{});
}

int main() {
    int x;
    vector<int> in;
    while (scanf("%d\n", &x) != EOF)
        in.push_back(x);

    std::cout << incs(in, 1) << "\n" << incs(in, 3) << "\n";
    return 0;
}
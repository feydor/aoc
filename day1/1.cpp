#include <iostream>
#include <vector>
using namespace std;

// 1: 1521, 2: 1543
int main() {
    int x;
    vector<int> v;
    while (scanf("%d\n", &x) != EOF)
        v.push_back(x);
    
    int silver = 0;
    for (size_t i = 1; i < v.size(); ++i)
        silver+= (v[i] > v[i-1]);

    int gold = 0;
    for (auto i = 3; i < v.size(); ++i)
        gold += (v[i] > v[i-3]);

    cout << silver << "\n" << gold << "\n";
    return 0;
}
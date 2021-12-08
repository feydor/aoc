#include <vector>
#include <iostream>
using namespace std;

vector<int> tribonacci(vector<int> seed, int n) {
  if (n < 3)
    seed.resize(n);
  for (size_t i = 3; i<n; ++i)
    seed.push_back(seed[i-3]+seed[i-2]+seed[i-1]);
  return seed;
}

vector<int> tribonacci_v1(vector<int> seed, int n) {
  vector<int> result;
  if (seed.size() < 3 || n == 0) return result;

  int a = seed[0], b = seed[1], c = seed[2];
  int d = 0;
  for (int i = 0; i < n; ++i) {
    if (i < seed.size()) {
      result.push_back(seed.at(i));
      continue;
    }

     d = c;
     c = a + b + c;
     a = b;
     b = d;
     result.push_back(c);
  }
  return result;
}

int main() {
  vector<int> seed = { 1, 1, 1 };
  vector<int> expected = { 1, 1, 1, 3, 5, 9, 17, 31, 57, 105 };
  auto result = tribonacci(seed, 10);
  if (result == expected)
    cout << "SUCCESS\n";
  else
    cout << "ERROR\n";
  for (const auto &x : result)
    cout << x << " ";
  cout << endl;
  return 0;
}


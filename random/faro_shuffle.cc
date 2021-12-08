#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

auto faro_shuffle(const vector<int> &deck) {
  vector<int> result = {deck.front()};
  int mid = (deck.size()/2);

  auto lower = deck.begin();
  auto lower_end = deck.begin() + mid;
  auto upper = deck.begin() + mid;
  auto upper_end = deck.end();

  // assuming equal halves
  while (lower != lower_end && upper != upper_end) {
    // insert from upper
    result.push_back(*upper);
    lower++;
    // insert from lower
    result.push_back(*lower);
    upper++;
  }
  
  result.resize(deck.size());
  return result;
}

int faro_cycles(int n) {
  if (n % 2 == 1) return -1;

  vector<int> range(n);
  iota(begin(range), end(range), 0);
  
  int i = 0;
  auto sentinel = range[1];
  while (true) {
    range = faro_shuffle(range);
    i++;
    if (range[1] == sentinel) break;
  }
  return i;
}

int main() {
  int ans = faro_cycles(52);
  if (ans == 8) cout << "SUCCESS\n";
  cout << ans << endl;
}

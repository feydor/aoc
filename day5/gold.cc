#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
    int x1, y1, x2, y2;
    map<pair<int, int>, int> lines;
    while (scanf("%d, %d -> %d, %d\n", &x1, &y1, &x2, &y2) != EOF) {
        // printf("%d, %d, %d, %d\n", x1, y1, x2, y2);

        // vertical line
        if (x1 == x2) {
            for (int y = min(y1, y2); y <= max(y1, y2); ++y)
                lines[make_pair(x1, y)]++;
        }

        // horizontal line
        if (y1 == y2) {
            for (int x = min(x1, x2); x <= max(x1, x2); ++x)
                lines[make_pair(x, y1)]++;
        }

        // 45 degree diagonal
        if (abs(x2-x1) == abs(y2-y1)) {
            int dx = (x2-x1) < 0 ? -1 : 1;
            int dy = (y2-y1) < 0 ? -1 : 1;
            for (int i = 0; i <= abs(y2-y1); ++i)
                lines[make_pair(x1 + dx * i, y1 + dy * i)]++;
        }
    }

    int uniques = 0;
    for (auto &[point, count]: lines)
        if (count > 1) uniques++;
    std::cout << uniques << std::endl;
    return 0;
}
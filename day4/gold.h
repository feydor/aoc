#include <string>
#include <vector>

struct space_t {
    space_t(int n) : n(n), marked(false) {}
    int n;
    bool marked = false;
};

struct board_t {
    int index;
    std::vector<std::vector<space_t>> board;
    void mark(int row, int col);
    void mark_it(int n);
    int get(int row, int col);
    int nspaces();
    bool has_won();
    int sumof_unmarked();
    friend std::ostream &operator<<(std::ostream &s, const board_t &b);
};

std::vector<int> parse_instructions(const std::string &line);
board_t parse_board(const std::vector<std::string> &lines, int index);
std::vector<std::string> split(const std::string &str, const char delim);
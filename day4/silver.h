#include <string>
#include <vector>

struct board_t {
    std::vector<std::vector<int>> board;
    std::vector<std::vector<bool>> marked;

    board_t(const std::vector<std::string> &data);

    bool has_bingo();

    void mark(int row, int col);
    void mark_it(int n);
    int get(int row, int col);
    int nspaces();
    bool has_won();
    int sumof_unmarked();
    friend std::ostream &operator<<(std::ostream &s, const board_t &b);
};

std::vector<int> parse_instructions(const std::string &line);
board_t parse_board(const std::vector<std::string> &lines);

std::vector<std::string> split(const std::string &str, const char delim);
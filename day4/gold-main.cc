#include <cassert>
#include <fstream>
#include <memory>
#include <iostream>
#include <set>
#include "gold.h"

const int ROWS = 15;

// mark boards and check for last winner
std::unique_ptr<board_t> mark_and_roll(std::vector<board_t> &boards, int cmd) {
    int winners = 0;
    for (auto &board : boards) {
        board.mark_it(cmd);
        if (board.has_won()) {
            winners = std::count_if(boards.begin(), boards.end(), [](auto board){ return board.has_won(); });
            if ((unsigned)winners >= boards.size()) return std::make_unique<board_t>(board);
        }
    }
    return nullptr;
}

// 26878
int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Argument missing.\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    std::string line;

    // parse first line (instructions)
    std::getline(file, line);
    auto instructions = parse_instructions(line);

    // parse boards
    std::vector<board_t> boards;
    std::vector<std::string> curr_board_lines;
    int board_count = 0;
    while (std::getline(file, line)) {
        if (line.size() > 0) {
            for (int i = 0; i < ROWS; ++i) {
               curr_board_lines.push_back(line);
               std::getline(file, line);
            }
            boards.push_back(parse_board(curr_board_lines, board_count));
            ++board_count;
            curr_board_lines.clear();
        }
    }

    // play game and check for final winner
    for (const auto &cmd : instructions) {
        if (auto final = mark_and_roll(boards, cmd)) {
            std::cout << final->sumof_unmarked() * cmd << std::endl;
            return 0;
        }
    }

    std::cout << "no winners\n";
    return 0;
}
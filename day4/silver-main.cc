#include <cassert>
#include <fstream>
#include <iostream>
#include "silver.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Argument missing.\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    std::string line;
    if (!file.is_open())
        throw std::ifstream::failure("Error opening file: " + std::string(argv[1]));

    // parse first line (instructions)
    std::getline(file, line);
    auto instructions = parse_instructions(line);

    // parse boards
    std::vector<board_t> boards;
    std::vector<std::string> curr_board_lines;
    const int ROWS = 15;
    while (std::getline(file, line)) {
        if (line.size() > 0) {
            for (int i = 0; i < ROWS; ++i) {
               curr_board_lines.push_back(line);
               std::getline(file, line);
            }
            boards.push_back(parse_board(curr_board_lines));
            curr_board_lines.clear();
        }
    }

    std::cout << "boards size: " << boards.size() << std::endl;

    // play game (iterate over instructions)
    // mark each board, if applicable
    // check for win, get index of winning board
    // do calculations on it
    for (const auto &cmd : instructions) {
        // std::cout << "'" << cmd << "' ";

        for (auto &board : boards)
            board.mark_it(cmd);
        
        auto winner = std::find_if(boards.begin(), boards.end(), [](board_t board){
            return board.has_won();
        });

        if (winner != boards.end()) {
            std::cout << "sum:" << winner->sumof_unmarked() << std::endl;
            std::cout << "cmd: " << cmd << std::endl;
            auto score = winner->sumof_unmarked() * cmd;
            std::cout << "score: " << score << std::endl;
            return 0;
        }
    }
    std::cout << "no winner..." << std::endl;
    return 0;
}
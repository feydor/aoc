#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include "silver.h"

const int ROWS = 5;

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Argument missing.\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    std::vector<std::string> lines(std::istream_iterator<std::string>(file), std::istream_iterator<std::string>(), {});
    
    // parse commands
    auto cmds_str = split(lines[0], ',');
    std::vector<int> cmds;
    std::transform(cmds_str.begin(), cmds_str.end(), std::back_inserter(cmds),
    [](auto str) { return std::stoi(str); });

    // parse boards
    std::vector<board_t> boards;
    for (auto line = lines.begin()+1; line != lines.end(); line += ROWS) {
        boards.emplace_back(board_t(line, line + ROWS));
    }

    // For each number in bingo board, replace it with the index of that number in
    // the called-out number array you get at the start.
    // A lower index iimplies that number is called early and a higher implies it's called late.
    std::transform(boards.begin(), boards.end(), std::back_inserter(boards), [&](board_t board){
        for (int row = 0; row < board.size(); ++row) {
            for (int col = 0; col < board[0].size(); ++col) {
                auto n = board[row][col];
                auto itr = std::find_if(cmds.begin(), cmds.end(), [&](auto cmd) { return cmd == n; });
                if (itr != cmds.end())
                    board[row][col] = *itr;
            }
        }
        return board;
    });

    // For each bingo board, get it's columns and rows.
    // For each of those, find the maximum number in that column/row.
    // This is the winning turn for that column/row
    std::vector<std::pair<int, int>> winning_turns;
    for (const auto& board : boards) {
        auto rows = board.rows();
        auto cols = board.cols();

        winning_turns.emplace_back(
            std::make_pair(std::max(rows.begin(), rows.end()), std::max(cols.begin(), cols.end()))
        );
    }

    std::min(winning_turns.begin(), winning_turns.end(), [](auto a, auto b) {
        return 
    });
    
    // Then, find the minimum number of the winning turns.
    // This is the winning turn for the bingo.



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
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <concepts>
#include <cmath>
#include <iostream>
#include <sstream>
#include <iterator>
#include <numeric>
#include "gold.h"

void board_t::mark(int row, int col) {
    this->board[row][col].marked = true;
}

// mark the number n, if it exists
void board_t::mark_it(int n) {
    for (auto &row : this->board) {
        auto found = std::find_if(row.begin(), row.end(), [n](space_t sp){
            return sp.n == n;
        });

        if (found != row.end())
            found->marked = true;
    }
}

int board_t::get(int row, int col) {
    return this->board[row][col].n;
}

// assumming evenly sized rows
int board_t::nspaces() {
    return this->board.size() * this->board[0].size();
}

bool board_t::has_won() {
    // check for horizontal wins
    for (const auto &row : this->board) {
        auto winner = std::all_of(row.begin(), row.end(), [](space_t space){
            return space.marked;
        });

        if (winner) return true;
    }

    // check for vertical wins
    for (size_t col = 0; col < this->board.size(); ++col) {
        size_t marks = 0;
        for (size_t row = 0; row < this->board.size(); ++row) {
            auto space = this->board[row][col];
            if (space.marked) ++marks;
        }
        if (marks == this->board.size()) return true;
    }

    return false;
}

// parse comma seperated numbers
std::vector<int> parse_instructions(const std::string &line) {
    auto num_strings = split(line, ',');

    std::vector<int> instructions;
    std::transform(num_strings.begin(), num_strings.end(), std::back_inserter(instructions),
    [](auto str) { return std::stoi(str); });

    return instructions;
}

board_t parse_board(const std::vector<std::string> &lines, int index) {
    std::vector<std::vector<space_t>> board;
    for (const auto &line : lines) {
        std::vector<space_t> row;

        auto num_strings = split(line, ' ');
        std::transform(num_strings.begin(), num_strings.end(), std::back_inserter(row),
        [](std::string str) { return space_t(std::stoi(str)); });
        
        board.push_back(row);
    }
    return { .index = index, .board = board };
}

// sum of the unmarled spaces
int board_t::sumof_unmarked() {
    int sum = 0;
    for (const auto &row : this->board)
        for (const auto &space : row)
            sum += space.marked ? 0 : space.n;
    return sum;
}

template <typename Out>
void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        if (!item.empty())
            *result++ = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

std::ostream & operator<<(std::ostream &s, const board_t &b) {
    for (const auto &row : b.board) {
        for (const auto &space : row) {
            s << space.n << ":" << (space.marked ? "t" : "f") << " ";
        }
        s << "\n";
    }
    return s;
}
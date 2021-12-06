#include <algorithm>
#include <numeric>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
using namespace std;

#define BOARD_SIZE 5

std::vector<std::string> split(const std::string& s, char delimiter) {                                                                                                                                                                                             
   std::vector<std::string> splits;                                                                                                                                                           
   std::string split;                                                                                                                                                                         
   std::istringstream ss(s);                                                                                                                                                                  
   while (std::getline(ss, split, delimiter)) {                                                                                                                                                                                          
      splits.push_back(split);                                                                                                                                                                
   }                                                                                                                                                                                          
   return splits;                                                                                                                                                                             
}

int get_col_max(const vector<vector<int>> &board, int col) {
    int max = 0;
    for (int i = 0; i < board.size(); ++i) {
        auto col_n = board[i][col];
        if (col_n > max)
            max = col_n;
    }
    return max;
}

auto parse_boards() {
    vector<vector<vector<int>>> boards;
    vector<vector<int>> board;
    string line;
    int line_count = 0;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        
        vector<int> nums;
        for (const auto &tok : split(line, ' ')) {
            if (!tok.empty())
                nums.push_back(stoi(tok));
        }
        board.push_back(nums);
        line_count++;
        if (line_count == BOARD_SIZE) {
            boards.push_back(board);
            board.clear();
            line_count = 0;
        }
    }
    return boards;
}

// score = last_called * sum of all the uncalled numbers on the board
int score(const vector<int> &cmds, const vector<vector<int>> &board, int last_called) {
    // get sum of all unmarked spaces in winning board
    auto left_uncalled = find(begin(cmds), end(cmds), last_called);
    int sum = 0;
    for (auto itr = left_uncalled+1; itr != end(cmds); itr++) {
        auto unmarked = *itr;
        for (const auto &row : board) {
            auto found = find(begin(row), end(row), unmarked);
            if (found != end(row))
                sum += *found;
        }
    }
    return sum * last_called;
}

// 1: 49686, 2: 26878
int main() {
    // parse cmds
    string line;
    getline(cin, line);
    vector<int> cmds;
    for (const auto &tok : split(line, ',')) {
        if (!tok.empty())
            cmds.push_back(stoi(tok));
    }

    vector<vector<vector<int>>> boards = parse_boards();
    vector<vector<vector<int>>> board_turns = boards;

    // replace each number with the index of that number in the called-out commands
    for (auto& board : board_turns) {
        for (int row = 0; row < board.size(); ++row) {
            for (int col = 0; col < board[0].size(); ++col) {
                auto n = board[row][col];
                auto found = find(begin(cmds), end(cmds), n);
                if (found != end(cmds))
                    board[row][col] = distance(begin(cmds), found);
                else
                    throw invalid_argument("Board never wins.");
            }
        }
    }

    // for each board, find it's earliest possible winning turn
    // for each row and column of every board, find the largest winning turn for that row/col
    // the smaller of the two, is the winning turn for the whole board
    vector<pair<int, int>> winning_turns; // board index, it's earliest possible winnning turn
    for (int i = 0; i < board_turns.size(); ++i) {
        auto board = board_turns[i];
        int min_all_rows = 99999; // smallest maximum of all rows
        for (const auto& row : board) {
            auto row_max = max_element(begin(row), end(row));
            if (*row_max < min_all_rows)
                min_all_rows = *row_max;
        }

        int min_all_cols = 99999;
        for (int col = 0; col < board.size(); ++col) {
            auto col_max = get_col_max(board, col);
            if (col_max < min_all_cols)
                min_all_cols = col_max;
        }

        winning_turns.emplace_back(i, min(min_all_rows, min_all_cols));
    }

    // get the best and worst boards
    auto best = min_element(begin(winning_turns), end(winning_turns), [](auto a, auto b){
        return a.second < b.second;
    });
    auto worst = max_element(begin(winning_turns), end(winning_turns), [](auto a, auto b){
        return a.second < b.second;
    });

    cout << "silver: " << score(cmds, boards[best->first], cmds[best->second]) << "\n";
    cout << "gold: " << score(cmds, boards[worst->first], cmds[worst->second]) << "\n";

    return 0;
}
#include "silver.h"

#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(ParseInstructionsTest, BasicAssertions) {
  std::string line = "13,47,64,52,60,69,80,85,57,1,2,6,30,81";
  auto cmd = parse_instructions(line);
  EXPECT_EQ(cmd.size(), 14);
  EXPECT_EQ(cmd[0], 13);
  EXPECT_EQ(cmd[1], 47);
  EXPECT_EQ(cmd[2], 64);
  EXPECT_EQ(cmd[8], 57);
}

TEST(ParseBoardTest, BasicAssertions) {
  std::vector<std::string> board_lines = {
    "88 67 20 19 15",
    "22 76 86 44 73",
    "7 42  6 69 25",
    "12 68 92 21 75",
    "97 45 13 52 70"
  };

  auto board = parse_board(board_lines);
  EXPECT_EQ(board.nspaces(), 25);
  EXPECT_EQ(board.has_won(), false);

  // test vertical win
  EXPECT_EQ(board.get(0, 0), 88);
  EXPECT_EQ(board.get(1, 0), 22);
  EXPECT_EQ(board.get(2, 0), 7);
  board.mark(0, 0);
  board.mark(1, 0);
  board.mark(2, 0);
  board.mark(3, 0);
  board.mark(4, 0);
  EXPECT_EQ(board.has_won(), true);
}

TEST(WinBoardTest, BasicAssertions) {
  std::vector<std::string> board_lines = {
    "88 67 20 19 15",
    "22 76 86 44 73",
    "7 42  6 69 25",
    "12 68 92 21 75",
    "97 45 13 52 70"
  };

  auto board = parse_board(board_lines);

  // use board.mark(n) to win horizontally
  board.mark_it(88);
  board.mark_it(67);
  board.mark_it(20);
  board.mark_it(19);
  board.mark_it(15);
  EXPECT_EQ(board.has_won(), true);
}


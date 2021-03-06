
/*
 * Copyright (c) 2021. Victor Reyes
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

package xyz.feydor.aoc;

public class Nqueens {

    private static final int N = 8;
    private static final char[][] board = new char[N][N];

    public static void main(String[] args) {
        // init board
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                board[i][j] = '.';

        var count = search(board,0);
        System.out.println("# of unique solutions to " + N + "-queens problem: " + count);
    }


    public static long search(char[][] board, int row) {
        // when last row is successfully reached
        if (row == N) {
            System.out.println("Printing solution...");
            printBoard(board);
            return 1;
        }

        // place a queen at every square in the current row
        // and recurse for every valid move
        long count = 0;
        for (int i = 0; i < N; i++) {
            if (isSafe(board, row, i)) {
                board[row][i] = 'Q';
                count += search(board,row+1);
                board[row][i] = '.';
            }
        }

        return count;
    }


    public static boolean isSafe(char[][] board, int row, int col) {
        // is not safe if
        // any queen shares the same column, top-left diagonal, or top-right diagonal
        int left_diag_j = col;
        int right_diag_j = col;
        for (int i = row; i >= 0; --i) {
            if (board[i][col] == 'Q')
                return false;
            if (left_diag_j >= 0 && board[i][left_diag_j] == 'Q')
                return false;
            if (right_diag_j < N && board[i][right_diag_j] == 'Q')
                return false;
            --left_diag_j;
            ++right_diag_j;
        }

        return true;
    }


    public static void printBoard(char[][] board) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                System.out.print(board[i][j]);
            }
            System.out.print("\n");
        }
        System.out.print("\n");
    }
}


package xyz.feydor.aoc;

public class nqueens {
    private static final int N = 8;
    private static final char[][] board = new char[N][N];

    public static void main(String[] args) {
        // init board
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                board[i][j] = '.';

        var count = search(board,0);
        System.out.println("# of solutions to " + N + "-queens problem: " + count);
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
        // any queen shares the same column
        for (int i = 0; i < row; ++i) {
            if (board[i][col] == 'Q')
                return false;
        }

        // any queen shares the same row
        for (int i = 0; i < col; ++i) {
            if (board[row][i] == 'Q')
                return false;
        }

        // four diagonals
        // top right
        for (int i = row, j = col; i >= 0 && j < N; i--, j++) {
            if (board[i][j] == 'Q')
                return false;
        }

        // top left
        for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q')
                return false;
        }

        // bottom right
        for (int i = row, j = col; i < N && j < N; i++, j++) {
            if (board[i][j] == 'Q')
                return false;
        }

        // bottom left
        for (int i = row, j = col; i < N && j >= 0; i++, j--) {
            if (board[i][j] == 'Q')
                return false;
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


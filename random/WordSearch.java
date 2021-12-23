package xyz.feydor.aoc;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * Returns all the given words on a board of MxN chars
 */
public class WordSearch {
    private static final int M = 4;
    private static final int N = 4;
    private static char[][] board = new char[M][N];
    private record Coord(int x, int y) { }

    public static void main(String[] args) {
        // sample board and words
        board = new char[][]{
                {'o', 'a', 'a', 'n'},
                {'e', 't', 'a', 'e'},
                {'i', 'h', 'k', 'r'},
                {'i', 'f', 'l', 'v'}
        };

        var words = List.of("pea", "oath", "eat", "rain", "at");
        var found = new HashSet<String>(); // no repeat solutions

        wordsearch(words, found);
        for (var word : found)
            System.out.println(word);
    }

    private static void wordsearch(List<String> words, Set<String> found) {
        for (var word : words) {
            // iterate over board and find all the locations where the first char matches
            var locations = search(word.charAt(0));

            // first char of current word not in board, skip
            if (locations.isEmpty())
                continue;

            // first char IS in board, find matches
            for (var loc : locations) {
                if (matches(word, 1, loc.y, loc.x)) {
                    found.add(word);
                }
            }
        }
    }

    private static List<Coord> search(char c) {
        var found = new ArrayList<Coord>();
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (board[i][j] == c)
                    found.add(new Coord(j, i));
            }
        }
        return found;
    }

    private static boolean matches(String word, int ci, int i, int j) {
        // check right, left, above, and below for the next char
        if (ci != word.length()) {
            if (j+1 < N && board[i][j+1] == word.charAt(ci)) {
                matches(word, ci+1, i, j+1);
            } else if (j-1 >= 0 && board[i][j-1] == word.charAt(ci)) {
                matches(word, ci+1, i, j-1);
            } else if (i-1 >= 0 && board[i-1][j] == word.charAt(ci)) {
                matches(word, ci+1, i-1, j);
            } else if (i+1 < M && board[i+1][j] == word.charAt(ci)) {
                matches(word, ci+1, i+1, j);
            } else {
                return false;
            }
        }
        return true;
    }
}


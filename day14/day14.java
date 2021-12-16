package xyz.feydor.aoc;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.*;
import java.util.stream.IntStream;

public class day14 {
    static final int STEPS = 10;
    static final int ALPHA_SIZE = 'Z' - 'A' + 1;
    private record Rule(int a, int b, int insert){}
    // char -> int == char-'A'
    // int -> char == int+'A'

    public static void main(String[] args) throws IOException {
        var data = Files.lines(Paths.get(args[0])).toList();
        var template = data.get(0);
        var instructions = data.stream()
                .skip(2)
                .map(s -> new Rule(s.charAt(0)-'A', s.charAt(1)-'A', s.charAt(s.length()-1)-'A'))
                .toList();

        // make a 2d matrix where the indices are the alphabets, the intersections are counts of each pair
        var pairMatrix = new int[ALPHA_SIZE][ALPHA_SIZE];
        for (int i = 0; i < template.length()-1; ++i) {
            var first = template.charAt(i)-'A';
            var second = template.charAt(i+1)-'A';
            pairMatrix[first][second]++;
        }

        printMatrix(pairMatrix);
        printRules(instructions);

        for (int step = 0; step < STEPS; ++step) {
            pairMatrix = pairInsertion(pairMatrix, instructions);
        }
        printMatrix(pairMatrix);

        var freq = new int[ALPHA_SIZE]; // frequency of alphabet
        for (int i = 0; i < ALPHA_SIZE; ++i) {
            for (int j = 0; j < ALPHA_SIZE; ++j) {
                freq[i] += pairMatrix[i][j]; // compress columns into rows
            }
        }
        freq[template.charAt(template.length()-1)-'A']++; // add the last character in the template

        // print frequency array
        int max = Integer.MIN_VALUE;
        int min = Integer.MAX_VALUE;
        for (int i = 0; i < freq.length; ++i) {
            System.out.printf("%c: %d\n", i+'A', freq[i]);
            if (freq[i] > 0) {
                max = Math.max(max, freq[i]);
                min = Math.min(min, freq[i]);
            }
        }
        System.out.print("\n");
        System.out.println("max: " + max + " min: " + min);
        System.out.println(max-min);
    }

    private static void printRules(List<Rule> rules) {
        System.out.println("Printing rules...");
        for (var rule : rules) {
            System.out.printf("%c%c -> %c\n", rule.a+'A', rule.b+'A', rule.insert+'A');
        }
    }

    private static void printMatrix(int[][] matrix) {
        System.out.println("Printing matrix...");
        // print column labels
        System.out.print("   ");
        for (int i = 'A'; i <= 'Z'; ++i) {
            System.out.print((char) (i) + " ");
        }
        System.out.print("\n");

        // print pair counts, row then column
        for (int i = 0; i < ALPHA_SIZE; ++i) {
            System.out.printf("%c: ", i+'A');
            for (int j = 0; j < ALPHA_SIZE; ++j) {
                if (matrix[i][j] != 0) {
                    System.out.printf("%d ", matrix[i][j]);
                } else {
                    System.out.print(". ");
                }
            }
            System.out.print("\n");
        }
    }

    private static int[][] pairInsertion(int[][] pairs, List<Rule> rules) {
        var nextPairs = new int[ALPHA_SIZE][ALPHA_SIZE];

        // for each rule, get the number of pairs that are affected by that rule
        // add them to the new pairs created by that rule
        for (var rule : rules) {
            var nPairs = pairs[rule.a][rule.b];
            nextPairs[rule.a][rule.insert] += nPairs;
            nextPairs[rule.insert][rule.b] += nPairs;
        }
        return nextPairs;
    }

    // get every k pair in str
    public static List<String> getSubStrings(String str, int k) {
        return IntStream.range(0, str.length() - k+1)
                .mapToObj(i -> str.substring(i, i+k))
                .toList();
    }
}


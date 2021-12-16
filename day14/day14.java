package xyz.feydor.aoc;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.*;

public class day14 {
    static final int STEPS = 40;
    static final int ALPHA_SIZE = ('Z' - 'A') + 1;

    // store characters as ints for easy indexing into a frequency array
    private record Rule(int a, int b, int insert){}

    public static void main(String[] args) throws IOException {
        var data = Files.lines(Paths.get(args[0])).toList();
        var template = data.get(0);
        var instructions = data.stream()
                .skip(2)
                .map(s -> new Rule(s.charAt(0)-'A', s.charAt(1)-'A', s.charAt(s.length()-1)-'A'))
                .toList();

        // make a 2d matrix where the indices are the alphabets, the intersections are counts of each pair
        var pairMatrix = new long[ALPHA_SIZE][ALPHA_SIZE];
        for (int i = 0; i < template.length()-1; ++i) {
            var first = template.charAt(i)-'A';
            var second = template.charAt(i+1)-'A';
            pairMatrix[first][second]++;
        }

        // run the pair insertion
        for (int step = 0; step < STEPS; ++step) {
            pairMatrix = pairInsertion(pairMatrix, instructions);
        }

        // for each character, add its occurrences to freq
        var freq = new long[ALPHA_SIZE]; // frequency of alphabet
        for (int i = 0; i < ALPHA_SIZE; ++i) {
            for (int j = 0; j < ALPHA_SIZE; ++j) {
                freq[i] += pairMatrix[i][j];
            }
        }
        freq[template.charAt(template.length()-1)-'A']++; // add the last character in the template

        // find the most and least common occurrences
        var max = Long.MIN_VALUE;
        var min = Long.MAX_VALUE;
        for (long x : freq) {
            if (x > 0) {
                max = Math.max(max, x);
                min = Math.min(min, x);
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

    private static void printMatrix(long[][] matrix) {
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

    private static long[][] pairInsertion(long[][] pairs, List<Rule> rules) {
        var nextPairs = new long[ALPHA_SIZE][ALPHA_SIZE];

        // for each rule, get the number of pairs that are affected by that rule
        // add them to the new pairs created by that rule
        for (var rule : rules) {
            var nPairs = pairs[rule.a][rule.b];
            nextPairs[rule.a][rule.insert] += nPairs;
            nextPairs[rule.insert][rule.b] += nPairs;
        }
        return nextPairs;
    }
}


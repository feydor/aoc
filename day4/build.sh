#!/usr/bin/bash

# run
bazel run --strategy=CppCompile=standalone //day4:silver-main -- ~/Documents/lambda/aoc/day4/input

# test
bazel test --strategy=CppCompile=standalone //day4:silver-test

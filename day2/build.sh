#!/bin/sh
CXX=c++
CXXFLAGS="-Wall -Wextra -Wshadow -std=c++17 -pedantic"
set -xe

$CXX $CXXFLAGS 1.cpp && cat input | ./a.out

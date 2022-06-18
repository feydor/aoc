#!/bin/sh
CXX=c++
CXXFLAGS="-Wall -Wextra -Wshadow -std=c++17 -pedantic -O3"
set -xe

$CXX $CXXFLAGS -o gold gold.cc && cat bigboy.txt | ./gold

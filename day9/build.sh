#!/bin/sh
CXX=c++
CXXFLAGS="-Wall -Wextra -Wshadow -std=c++20 -pedantic -O2"
set -xe

$CXX $CXXFLAGS -o gold gold.cc && cat input | ./gold

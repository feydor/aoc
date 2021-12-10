#!/bin/sh
CC=c++
CCFLAGS="-Wall -Wextra -Wshadow -std=c++17 -pedantic"
set -xe

$CC $CCFLAGS 1-best.cpp && cat input | ./a.out

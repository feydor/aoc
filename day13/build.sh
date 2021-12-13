#!/bin/sh
CXX=c++
CXXFLAGS="-Wall -Wextra -Wshadow -std=c++20 -pedantic"
set -xe

$CXX $CXXFLAGS -o silver silver.cc && cat example | ./silver

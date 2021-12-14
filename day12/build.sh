#!/bin/sh
CXX=c++
CXXFLAGS="-Wall -Wextra -Wshadow -std=c++20 -pedantic"
CXXINCLUDE="-I ../"
set -xe

$CXX $CXXFLAGS $CXXINCLUDE -o gold gold.cc && cat example | ./gold

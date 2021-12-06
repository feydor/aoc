#!/bin/bash
g++ -O3 gold.cc && time cat bigboy.txt | ./a.out

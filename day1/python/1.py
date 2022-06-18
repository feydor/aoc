from ast import operator
from functools import reduce
from itertools import accumulate
import sys

filepath = '../example'

def scan(filepath):
    def strip(x): return x.strip()
    with open(filepath) as f:
        return list(map(strip, f.readlines()))

def n_sliding_window(vec, n):
    # count increments of sums of n sliding windows
    # example: 199 200 208 2010
    # method: increment += (199 + 200 + 208) > (200 + 208 + 210) 
    #         increment += 199 > 210
    increments = 0
    for i, curr in enumerate(vec[n:], start=n):
        prev = vec[i-n]
        increments += (curr > prev)
    return increments

def silver(vec):
    return n_sliding_window(vec, 1)

def gold(vec):
    return n_sliding_window(vec, 3)

def main():
    lines = list(map(int, scan(filepath=sys.argv[1])))

    print(f'silver: {silver(lines)}')
    print(f'gold: {gold(lines)}')

main()
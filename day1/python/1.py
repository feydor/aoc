import operator
from functools import reduce
from itertools import accumulate, pairwise
import sys

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

def re_n(vec, n):
    def tuple_gt(tup): return tup[1] > tup[0]
    return sum(map(operator.truth, map(tuple_gt, zip(vec, vec[n:]))))

def silver(vec):
    return n_sliding_window(vec, n=1)

def gold(vec):
    return n_sliding_window(vec, n=3)

def main():
    lines = list(map(int, scan(filepath=sys.argv[1])))

    print(f'silver: {silver(lines)}')
    print(f'gold: {gold(lines)}')

    print(f'test: {re_n(lines, 3)}')

main()
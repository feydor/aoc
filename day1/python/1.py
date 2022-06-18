from ast import operator
from functools import reduce
from itertools import accumulate


filepath = '../example'

def strip(str):
    return str.strip()


def n_sliding_window(vec, n):
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
    lines = {}
    with open(filepath) as f:
        lines = f.readlines()
    lines = list(map(int, map(strip, lines)))

    for l in lines:
        print(l)
    print("before")

    print(f'silver: {silver(lines)}')
    print(f'gold: {gold(lines)}')

main()
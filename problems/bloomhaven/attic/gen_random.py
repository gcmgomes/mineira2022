#!/usr/bin/env python

import sys,os,string,math
from random import seed, randint, sample

MAXV = 100000

def make_nums(n):
    i = 0
    nums = []
    pos = randint(0,1)
    while i < n:
        chunk_size = randint(1, min(n - i, int(math.sqrt(n))))
        i += chunk_size
        sign = 1 if pos == 1 else -1
        while chunk_size > 0:
            nums.append(sign * randint(1, MAXV))
            chunk_size -= 1
        pos = 1 - pos
    return nums

# first argument must be seed
seed(sys.argv[1])

# second argument is the min n
min_n = int(sys.argv[2])
# third argument is the max n
max_n = int(sys.argv[3])

n = randint(min_n, max_n)
h_n = int(n/2)
odds = []
odds = make_nums(h_n + (n % 2))
evens = make_nums(h_n)
vec = []
i = 0
while i < h_n:
    vec.append(odds[i])
    vec.append(evens[i])
    i += 1
if n % 2:
    vec.append(odds[i])
print(n)
print(" ".join(map(str, vec)))
#!/usr/bin/env python

# Sample test generator

import sys,os,string
import numpy as np
from random import seed, randint, sample

# first argument must be seed
seed(sys.argv[1])
# second argument must be number of rows
max_n = int(sys.argv[2])
# third argument must be number of columns
max_m = int(sys.argv[3])
# fourth argument must be color threshold
max_k = int(sys.argv[4])

# if optional fifth argument is present, do not rand the limits
force_size = True if len(sys.argv) > 5 else False


k = max_k if force_size else randint(int(0.9*max_k), max_k)
m = max_m if force_size else randint(int(0.9*max_m), max_m)
n = max_n if force_size else randint(int(0.9*max_n), max_n)

grid = []

print("{} {} {}".format(n, m, k))
init_color = randint(1,3)
prev_count = 0
for i in range(0, n):
    row = []
    new_init_color = randint(1,3)
    while new_init_color == init_color and prev_count == k - 1:
        new_init_color = randint(1,3)
    cur_color = new_init_color
    for j in range(0, m):
        row.append(cur_color)
        cur_color = max(1, (cur_color + 1) % 4)
    prev_count = prev_count + 1 if init_color == new_init_color else 1
    init_color = new_init_color
    print(" ".join(map(str, row)))
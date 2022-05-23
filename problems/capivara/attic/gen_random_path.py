#!/usr/bin/env python

# Sample test generator

import sys,os,string
import numpy as np
from random import seed, randint, sample

# first argument must be seed.
seed(sys.argv[1])
# second argument must be number of columns.
max_m = int(sys.argv[2])
# third argument must be color threshold.
max_k = int(sys.argv[3])
# fourth argument decides if we print a row or a column path.
as_column = False
if sys.argv[4] == 'True':
    as_column = True

# if optional fifth argument is present, do not rand the limits.
force_size = True if len(sys.argv) > 5 else False


k = max_k if force_size else randint(1, max_k)
m = max_m if force_size else randint(1, max_m)
n = 1

if as_column:
    print("{} {} {}".format(m, n, k-1))
else:
    print("{} {} {}".format(n, m, k-1))
row = []
prev_color = 0
while len(row) < m:
    subseg_size = randint(1, min(k-1, m - len(row)))
    color = prev_color
    while color == prev_color:
        color = randint(1, 3)
    row.extend([color]*subseg_size)
    prev_color = color
if as_column:
    for p in row:
        print(p)
else:
    print(" ".join(map(str, row)))
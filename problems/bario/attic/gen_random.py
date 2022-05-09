#!/usr/bin/env python

# Sample test generator

import sys,os,string
from random import seed, randint, sample

# first argument must be seed
seed(sys.argv[1])
# second argument is the minimum number of blocks
MIN=int(sys.argv[2])
# third argument is the maximum number of blocks
MAX=int(sys.argv[3])

n = randint(MIN,MAX)
output = ''
c = '.'
chunk = 0
while len(output) < n - 1:
    c = '.' if (c == 'x') else 'x'
    chunk = randint(1, n - 1 - len(output))
    ext = ''
    while len(ext) < chunk:
        ext = ext + c
    output = output + ext
output += 'x'
print(n)
print(output)
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
# fourth argument is the maximum size of a chunk
CHUNK=int(sys.argv[4])

n = randint(MIN,MAX)
output = ''
c = '.'
chunk = 0
while len(output) < n - 1:
    c = '.' if (c == 'x') else 'x'
    max_len = min(CHUNK, n - 1 - len(output))
    if c == '.':
        max_len = min(max_len, max(chunk-1, 1))
    chunk = randint(1, max_len)
    ext = ''
    while len(ext) < chunk:
        ext = ext + c
    output = output + ext
output += 'x'
print(n)
print(output)

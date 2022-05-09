#!/usr/bin/env python

# Sample test generator

import sys,os,string
from random import seed, randint, sample

# first argument must be seed
seed(sys.argv[1])
N=int(sys.argv[2])
M=int(sys.argv[3])
K=int(sys.argv[4])
Q=int(sys.argv[5])

print N, M, K, Q

cidades = set()

while len(cidades) < Q:
    x = randint(1, N)
    y = randint(1, M)
    cidades.add((x, y))
    
for c in cidades:
  print c[0], c[1], randint(1, 1000000000)

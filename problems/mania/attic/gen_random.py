#!/usr/bin/env python

# Sample test generator

import sys,os,string,random
from random import seed, randint, sample

# first argument must be seed
seed(sys.argv[1])
G=int(sys.argv[2])
S=int(sys.argv[3])

if G == -1:
    G = randint(1, 360)
print G
print(''.join(random.choice('DE') for _ in range(S)))


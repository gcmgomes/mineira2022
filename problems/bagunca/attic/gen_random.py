#!/usr/bin/env python

# Sample test generator

import sys,os,string,random
from random import seed, randint, sample

# first argument must be seed
seed(sys.argv[1])
L=int(sys.argv[2])
C=int(sys.argv[3])


A = randint(1, L)
B = randint(1, C)

print L, C
for i in range(L):
	for j in range(C):
		if(j<C-1):
			print randint(0, 1000000),
		else:
			print randint(0, 1000000)
print A, B


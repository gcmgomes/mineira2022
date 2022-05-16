#!/usr/bin/env python

import sys,os,string
from random import seed, randint, sample

# first argument is always seed
seed(sys.argv[1])
T=int(sys.argv[2])

if T == 1:
	print """3 4
0 0 0 0
0 0 0 0
0 0 0 0
3 4"""

if T == 2:
	print """2 2
1 0
0 0
2 2"""

if T == 3:
	print """4 4
1000 1000 1000 1000
1000 1000 1000 1000
1000 1000 1000 1000
1000 1000 1000 1000
4 4"""

if T == 4:
	print """1 1
23
1 1"""

if T == 5:
	print """12 1
8
0
0
0
0
0
0
2
0
0
0
0
12 1"""

if T == 6:
	print """3 4
10 0 0 0
0 0 0 0
0 0 0 10
3 4"""

if T == 7:
    print """3 4
0 0 0 0
0 0 0 0
0 0 0 10
3 4"""

if T == 8:
    print """3 4
0 0 0 0
0 0 0 0
0 0 0 1000000
1 1"""

if T == 9:
    print """1 20
5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
1 20"""
    
if T == 10:
    print """1 20
5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
1 2"""

if T == 11:
    print """12 1
5
0
0
0
0
0
0
0
0
0
0
0
1 1"""

if T == 12:
    print """12 1
8
0
0
0
0
0
0
0
0
0
0
0
12 1"""
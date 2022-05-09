#!/usr/bin/env python

import sys,os,string
from random import seed, randint, sample

# first argument is always seed
seed(sys.argv[1])
T=int(sys.argv[2])

if T == 1:
	print """1 1 1 1
1 1 777"""

if T == 2:
	print """4 4 3 9
1 1 1
1 2 1
1 3 1
2 1 1
2 3 1
3 1 1
3 2 1
3 3 1
1 4 1"""

if T == 3:
	print """4 4 3 9
1 1 5
1 2 5
1 3 5
2 1 5
2 3 5
3 1 5
3 2 5
3 3 5
2 2 5"""

if T == 4:
	print """4 4 3 9
1 1 123
1 2 5
1 3 5
2 1 5
2 3 5
3 1 5
3 2 5
3 3 5
2 2 5"""

if T == 5:
	print """4 4 2 8
1 1 5
1 2 5
2 1 5
2 2 555
3 3 5
3 4 5
4 3 5
4 4 556"""

if T == 6:
	print """4 4 2 7
1 1 5
1 2 999999999
2 1 5
2 2 5
2 3 5
3 2 999999998
3 3 5"""

if T == 7:
	print """4 4 2 7
1 1 5
1 2 999999999
2 1 5
2 2 5
2 3 5
3 2 1000000000
3 3 5"""

if T == 8:
	print """4 4 2 6
1 1 5
1 2 5
2 1 5
2 3 5
3 2 5
3 3 5"""

#!/usr/bin/env python

import sys,os,string
from random import seed, randint, sample

# first argument is always seed
seed(sys.argv[1])
T=int(sys.argv[2])

if T == 1:
	print """360
D"""

if T == 2:
	print """360
E"""

if T == 3:
	print """180
DE"""

if T == 4:
	print """90
DDDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDEDED"""

if T == 5:
	print """359
EDEDEDEDEDEDEDEDE"""

if T == 6:
	print """360
ED"""

if T == 7:
	print """90
EEDDDD"""

if T == 8:
	print """90
DDEEEE"""

if T == 9:
	print """90
DDEEEDDEEDEE"""

if T == 10:
    print 1
    print(('E' * 359) + ('DE' * 49000))

if T == 11:
    print 1
    print(('D' * 359) + ('ED' * 49000))

if T == 12:
    print 1
    print(('E' * 359) + ('DE' * 49000) + 'E')
    
if T == 13:
    print 1
    print(('D' * 359) + ('ED' * 49000) + 'D')    

#!/usr/bin/env python

# Sample test generator

import sys,os,string
from random import seed, randint, sample

# first argument must be seed.
seed(sys.argv[1])
# second argument must be max number of days.
max_n = int(sys.argv[2])
# third argument must be max value of Ki
max_k = int(sys.argv[3])
# if optional fourth argument is present, do not rand the limits.
force_size = True if len(sys.argv) > 5 else False

n = max_n if force_size else randint(1, max_n)


print(n)
print(" ".join(str(max_k if force_size else randint(1, max_k)) for i in range(n)))

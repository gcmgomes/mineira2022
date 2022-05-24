#!/usr/bin/env python

# cypher test generator

import sys,os,string
import random
from random import seed, randint, sample

# first argument must be seed
seed(sys.argv[2])
max_c = int(sys.argv[3])

rand_c = randint(1, max_c)
c = ''.join(random.choice(string.ascii_uppercase) for _ in range(rand_c))
n = randint(1, len(c))

print("{}\n{}".format(c, n))

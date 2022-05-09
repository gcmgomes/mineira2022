#!/usr/bin/env python3

import sys
import random

# first argument must be seed
random.seed(sys.argv[1])

FIRST_VALUE = int(sys.argv[2])
LAST_VALUE = int(sys.argv[3])
DELTA = int(sys.argv[4])

values = list(range(FIRST_VALUE, LAST_VALUE, DELTA))
values.append(LAST_VALUE)
print(len(values))
print(" ".join(str(value) for value in values));
print(1)
print(1, len(values))

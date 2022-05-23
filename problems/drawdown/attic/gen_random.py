#!/usr/bin/env python3

import sys
import random

# first argument must be seed
random.seed(sys.argv[1])

MIN_NUM_VALUES=int(sys.argv[2])
MAX_NUM_VALUES=int(sys.argv[3])
MIN_VALUE = int(sys.argv[4])
MAX_VALUE = int(sys.argv[5])
MIN_NUM_QUERIES = int(sys.argv[6])
MAX_NUM_QUERIES = int(sys.argv[7])

num_values = random.randint(MIN_NUM_VALUES,MAX_NUM_VALUES)
print(num_values)
print(" ".join(str(random.randint(MIN_VALUE, MAX_VALUE)) for _ in range(num_values)));
num_queries = random.randint(MIN_NUM_QUERIES, MAX_NUM_QUERIES)
print(num_queries)
for _ in range(num_queries):
    start_index = random.randint(1, num_values);
    end_index = random.randint(start_index, num_values);
    print(start_index, end_index)

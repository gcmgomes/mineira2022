#!/usr/bin/env python

# Sample test generator


import sys,os,string
from random import seed, randint, sample

def Sieve(sieve_len):
    nums = [1]*sieve_len
    ret_val = []
    nums[0] = nums[1] = 0
    i = 2
    while i < len(nums):
        if nums[i] == 0:
            i += 1
            continue
        ret_val.append(i)
        j = i+i
        while j < len(nums):
            nums[j] = 0
            j += i
        i += 1
    return ret_val

# first argument must be seed
seed(sys.argv[1])
# second argument is the minimum number of digits
min_n = int(sys.argv[2])
# third argument is the maximum number of digits
max_n = int(sys.argv[3])
# fourth argument is the minimum number of primes
min_k = int(sys.argv[4])
# fifth argument is the mximum number of primes
max_k = int(sys.argv[5])


n = randint(min_n, max_n)
k = randint(min_k, max_k)

num = str(randint(1, 9))
while len(num) < n:
    nex = randint(0, 99999)
    num = num + str(nex)
while len(num) > n:
    num = num[:-1]

if  int(num[n-1]) % 2 == 0:
    num = num[:-1] + str(int(num[n-1]) + 1)

sieved = Sieve(1000000 if len(num) > 6 else 10**(len(num)-1))
primes = sample(sieved, min(len(sieved), k))

print("{} {}".format(num, len(primes)))
print(" ".join(map(str, primes)))

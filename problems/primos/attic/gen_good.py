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
# fourth argument is the minimum number of primes
min_k = int(sys.argv[3])
# fifth argument is the mximum number of primes
max_k = int(sys.argv[4])

n = min_n
k = randint(min_k, max_k)

max_prime = 1000000 if n > 6 else 10**(n-1)
if len(sys.argv) > 5:
    max_prime = int(sys.argv[5])

sieved = Sieve(max_prime)
primes = sorted(sample(sieved, min(len(sieved), k)))
num = ""
while len(num) < n:
    max_i = 0
    while max_i < len(primes) and (len(str(primes[max_i])) + len(num) <= n):
        max_i += 1
    i = randint(0, max(0, max_i-1))
    cur_num = primes[i]
    multiple = randint(1, 2)
    if len(str(cur_num*multiple)) + len(num) > n:
        multiple = randint(1, 2)
    num = num + str(cur_num*multiple)


print("{} {}".format(num, len(primes)))
print(" ".join(map(str, reversed(primes))))

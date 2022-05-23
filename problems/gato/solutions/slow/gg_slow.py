import sys

def IsDiv(cur_num, k, p):
    i = 0
    while i < k:
        if cur_num % p[i] == 0:
            return True
        i += 1
    return False

def Solve(i, recover, num, k, p):
    if i >= len(num):
        return 1
    cur_num = 0
    sol = 0
    j = i
    while j < len(num):
        cur_num = 10*cur_num + int(num[j])
        if IsDiv(cur_num, k, p):
            rest = Solve(j+1, recover, num, k, p)
            recover[i] = j+1
            sol = rest
        j += 1
    return sol


first_l = sys.stdin.readline().split()
N = first_l[0]
K = int(first_l[1])

P = list(map(int, sys.stdin.readline().split()))

divs = [-1]*len(N)
ret_val = Solve(0, divs, N, K, P)
if ret_val == 0:
    print(-1)
else:
    seq = []
    i = 0
    while i < len(N):
        base = i
        cur_num = 0
        while i < len(N) and i < divs[base]:
            cur_num = 10*cur_num + int(N[i])
            i += 1
        seq.append(cur_num)
    print(len(seq))
    print(" ".join(map(str, seq)))

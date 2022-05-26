#!/usr/bin/env python3

# Sample test generator

import sys,os,string
from random import seed, randint, sample, uniform, shuffle

class UnionFind:
    def __init__(self, n_, e_):
        self.n = n_
        self.e = e_
        self.size = [1] * (n+e)
        self.parent = list(range(0,n+e))
        self.max_size = 1
    
    def Find(self, u):
        if self.parent[u] != u:
            self.parent[u] = self.Find(self.parent[u])
        return self.parent[u]
    
    def Union(self, u, v):
        u = self.Find(u)
        v = self.Find(v)
        if u == v:
            return
        if self.size[u] < self.size[v]:
            self.Union(v,u)
            return
        self.parent[v] = u
        self.size[u] += self.size[v]
        self.max_size = max(self.max_size, self.size[u])
        
    

# first argument must be seed.
seed(sys.argv[1])
# second argument is the number of newbies.
n=int(sys.argv[2])
# third argument is the number of veterans.
e=int(sys.argv[3])
# fourth argument is the probability of each extra edge.
p=float(sys.argv[4])

graph = []
for i in range(0, n+e):
    graph.append(set())
uf = UnionFind(n, e)

while uf.max_size < n+e:
    u = randint(0, n-1)
    v = randint(n, n+e-1)
    base_v = v
    while uf.Find(v) == uf.Find(u):
        v += 1
        if(v == n + e):
            v = n
        if(v == base_v):
            break
    uf.Union(u,v)
    graph[u].add(v)
    graph[v].add(u)
    
for i in range(0,n):
    for j in range(n, n+e):
        if not (v in graph[u]) and (uniform(0.0, 1.0) <= p):
            graph[u].add(v)
            graph[v].add(u)

print(n,e)
for i in range(0, n):
    edges = list(graph[i])
    # everything was 0-based so far, have to fix it.
    for i in range(0, len(edges)):
        edges[i] = edges[i] + 1
    shuffle(edges)
    print(len(edges), " ".join(map(str, edges)))

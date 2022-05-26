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
        

def MakeGraph(n, e, p):
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
    return graph

def MakeSuperSeparator(gap_count, prev_last):
    graph = []
    total_n = 2*gap_count + 1
    for i in range(0, gap_count):
        graph.append([prev_last + i + 1])
    for i in range(0, gap_count+1):
        graph.append([prev_last + i, prev_last + i + 1])
    return graph

def RebaseGraph(in_graph, offset):
    out_graph = []
    for u_set in in_graph:
        s = []
        for v in u_set:
            s.append(v + offset)
        shuffle(s)
        out_graph.append(s)
    return out_graph

# first argument must be seed.
seed(sys.argv[1])
# second argument is the number of newbies per piece.
n=int(sys.argv[2])
# third argument is the number of veterans per piece.
e=int(sys.argv[3])
# fourth argument is the number of separators (pieces - 1).
s=int(sys.argv[4])
# fifth argument is the number of gaps in each separator.
gap_count=int(sys.argv[5])
# sixth argument is the probability of each extra edge.
p=float(sys.argv[6])

graphs = []
total_n = (s+1)*n + s*(2*gap_count + 1)
offset = total_n
for i in range(0, s+1):
    if i > 0:
        graphs.append((2*gap_count+1, MakeSuperSeparator(gap_count, offset)))
        offset += gap_count
    graphs.append((n, RebaseGraph(MakeGraph(n, e, p), offset - n + 1)))
    offset += e
print(total_n, (s+1)*e + s*gap_count)
for ng in graphs:
    n_g, graph = ng
    for i in range(0, n_g):
        print(len(graph[i]), " ".join(map(str, graph[i])))

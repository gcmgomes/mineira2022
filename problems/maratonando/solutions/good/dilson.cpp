#include <cassert>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

/******************************************************************************
 * Templated functions to read the input
 *****************************************************************************/
template <typename T> T Read() {
  T value;
  std::cin >> value;
  assert(std::cin);
  return value;
}

/******************************************************************************
 * Dinic's algorithm for maximum flow..
 *****************************************************************************/
struct Edge {
  int v, rev;
  int cap;
  bool real;
  Edge(int v_, int cap_, int rev_, bool real_)
      : v(v_), rev(rev_), cap(cap_), real(real_) {}
};

struct MaxFlow {
  vector<vector<Edge>> g;
  vector<int> level;
  queue<int> q;
  int flow, n;

  MaxFlow(int n_) : g(n_), level(n_), n(n_) {}

  void addEdge(int u, int v, int cap) {
    if (u == v)
      return;
    Edge e(v, cap, int(g[v].size()), true);
    Edge r(u, 0, int(g[u].size()), false);
    g[u].push_back(e);
    g[v].push_back(r);
  }

  bool buildLevelGraph(int src, int sink) {
    fill(level.begin(), level.end(), -1);
    while (not q.empty())
      q.pop();
    level[src] = 0;
    q.push(src);
    while (not q.empty()) {
      int u = q.front();
      q.pop();
      for (auto e = g[u].begin(); e != g[u].end(); ++e) {
        if (not e->cap or level[e->v] != -1)
          continue;
        level[e->v] = level[u] + 1;
        if (e->v == sink)
          return true;
        q.push(e->v);
      }
    }
    return false;
  }

  int blockingFlow(int u, int sink, int f) {
    if (u == sink or not f)
      return f;
    int fu = f;
    for (auto e = g[u].begin(); e != g[u].end(); ++e) {
      if (not e->cap or level[e->v] != level[u] + 1)
        continue;
      int mincap = blockingFlow(e->v, sink, min(fu, e->cap));
      if (mincap) {
        g[e->v][e->rev].cap += mincap;
        e->cap -= mincap;
        fu -= mincap;
      }
    }
    if (f == fu)
      level[u] = -1;
    return f - fu;
  }

  int maxFlow(int src, int sink) {
    flow = 0;
    while (buildLevelGraph(src, sink))
      flow += blockingFlow(src, sink, numeric_limits<int>::max());
    return flow;
  }
};

/*****************************************************************************/

int BuildTreeAndCountMatches(const vector<vector<int>> &g,
                             const vector<int> &matches, const int node,
                             vector<int> &parent, vector<int> &color) {
  color[node] = color[parent[node]];
  int count = 0;
  if (matches[node] != -1 && parent[matches[node]] == -1) {
    parent[matches[node]] = node;
    count +=
        BuildTreeAndCountMatches(g, matches, matches[node], parent, color) + 1;
  }
  for (const int next : g[node]) {
    if (parent[next] == -1) {
      parent[next] = node;
      count += BuildTreeAndCountMatches(g, matches, next, parent, color);
    }
  }
  return count;
}

int main() {
  const auto n = Read<int>();
  const auto e = Read<int>();

  vector<vector<int>> g(n + e);
  MaxFlow flow(n + e + 2);
  const int src = n + e;
  const int sink = n + e + 1;
  for (int a = 0; a < n; a++) {
    flow.addEdge(src, a, 1);
    const auto k = Read<int>();
    for (int i = 0; i < k; i++) {
      const auto b = Read<int>() - 1;
      assert(b >= n);
      assert(b < n + e);
      g[a].push_back(b);
      g[b].push_back(a);
      flow.addEdge(a, b, 1);
    }
  }
  for (int b = n; b < n + e; b++) {
    flow.addEdge(b, sink, 1);
  }

  const int m = flow.maxFlow(src, sink);
  if (m == 0) {
    cout << 0 << endl;
    return 0;
  }

  vector<int> matches(n + e, -1);
  for (int a = 0; a < n; a++) {
    for (const Edge &edge : flow.g[a]) {
      if (edge.real && edge.cap == 0) {
        matches[a] = edge.v;
        matches[edge.v] = a;
      }
    }
  }

  int max_matches = 0;
  int best_root = -1;
  vector<int> parent(n + e, -1);
  vector<int> color(n + e, -1);
  for (int r = 0; r < n + e; r++) {
    if (parent[r] == -1) {
      parent[r] = r;
      color[r] = r;
      const int num_matches =
          BuildTreeAndCountMatches(g, matches, r, parent, color);
      if (num_matches > max_matches) {
        max_matches = num_matches;
        best_root = r;
      }
    }
  }

  int changes;
  do {
    changes = 0;
    for (int i = 0; i < n + e; i++) {
      if (parent[i] != i && matches[i] != -1 && matches[parent[i]] == -1) {
        matches[matches[i]] = -1;
        matches[i] = parent[i];
        matches[parent[i]] = i;
        changes++;
      }
    }
  } while (changes);

  cout << max_matches << '\n';
  for (int a = 0; a < n; a++) {
    if (color[a] == best_root && matches[a] != -1) {
      assert(color[matches[a]] == best_root);
      cout << (a + 1) << ' ' << (matches[a] + 1) << '\n';
    }
  }
}

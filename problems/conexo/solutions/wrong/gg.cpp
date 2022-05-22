#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

int INF = std::numeric_limits<int>().max();
int MINF = std::numeric_limits<int>().min();
double INFD = std::numeric_limits<double>().max();

double PI = acos(-1);

bool BFS(vector<vector<int>>& graph, vector<int>& dist, vector<int>& matching,
         vector<int>& left) {
  queue<int> q;
  dist.assign(dist.size(), INF);
  for (int i = 0; i < left.size(); i++) {
    if (matching[left[i]] == -1) {  // vertex is not matched
      dist[left[i]] = 0;
      q.push(left[i]);
    }
  }
  int shortest = INF;  //, bla = 0;
  while (q.size()) {
    int u = q.front();
    q.pop();
    // cerr << "popped " << u << ". dist[u] = " << dist[u]
    //  << " and shortest = " << shortest << endl;
    // cin >> bla;
    if (dist[u] < shortest) {
      for (auto& v : graph[u]) {
        if (matching[v] == u || dist[v] != INF) {
          continue;
        }
        // cerr << "looking at " << v << " with matching[v] = " << matching[v]
        //  << endl;
        // we found a non-matched vertex on the right side.
        if (matching[v] == -1) {
          dist[v] = dist[u] + 1;
          shortest = dist[u] + 1;
        }
        // have to keep looking for a non-matched vertex.
        else if (dist[matching[v]] == INF) {
          dist[v] = dist[matching[v]] = dist[u] + 1;
          q.push(matching[v]);
          //   cerr << "pushed " << matching[v] << endl;
        }
      }
    }
  }
  return shortest != INF;
}

bool DFS(vector<vector<int>>& graph, vector<int>& matching, vector<int>& dist,
         int u) {
  if (u == -1) {
    return true;
  }
  for (auto& v : graph[u]) {
    // if v is not matched or if there is a shortest augmenting path that
    // passes through u-v-matching[v], take it.
    if (matching[v] == -1 || dist[matching[v]] == dist[u] + 1) {
      if (DFS(graph, matching, dist, matching[v])) {
        // cerr << "matching u = " << u << " with v = " << v << endl;
        matching[v] = u;
        matching[u] = v;
        return true;
      }
    }
  }
  dist[u] = INF;
  return false;
}

void print_vec(vector<int>& vec, int p = 0) {
  for (auto& v : vec) {
    cerr << " " << v + p;
  }
  cerr << endl;
}

vector<int> HopcroftKarp(vector<vector<int>>& graph, vector<int>& left) {
  vector<int> matching(graph.size(), -1), dist(graph.size(), INF);
  int matching_size = 0;
  while (BFS(graph, dist, matching, left)) {
    // print_vec(dist);
    for (int i = 0; i < left.size(); i++) {
      if (matching[left[i]] == -1 && DFS(graph, matching, dist, left[i])) {
        matching_size++;
      }
    }
    // print_vec(matching);
    // cerr << matching_size << endl;
  }
  return matching;
}

// S[v] == 1 iff v is in the connected component.
bool CBFS(vector<vector<int>>& graph, vector<int>& matching, vector<int>& S,
          vector<int>& ignored, queue<int>& candidates, int root) {
  queue<int> q;
  vector<int> visits(graph.size(), 0);
  q.push(root);
  bool expanded = false;
  while (q.size()) {
    int u = q.front();
    q.pop();
    for (auto& v : graph[u]) {
      if (S[v] || visits[v] || ignored[v]) {
        continue;
      }
      visits[v] = 1;
      if (matching[v] != -1) {
        S[v] = 1;
        q.push(v);
        expanded = true;
      } else {
        candidates.push(v);
      }
    }
  }
  return expanded;
}

void print_matching(vector<int>& matching, int n) {
  vector<pair<int, int>> edges;
  for (int i = 0; i < n; i++) {
    if (matching[i] != -1) {
      edges.push_back({i, matching[i]});
    }
  }
  cout << edges.size() << endl;
  for (auto& e : edges) {
    cout << e.first + 1 << ' ' << e.second + 1 << endl;
  }
}

int main() {
  iostream::sync_with_stdio(false);
  int n = 0, e = 0;
  cin >> n >> e;
  vector<vector<int>> graph(n + e, vector<int>());
  vector<int> left(n);
  for (int i = 0; i < n; i++) {
    left[i] = i;
    int n_i = 0;
    cin >> n_i;
    graph[i].resize(n_i, 0);
    for (auto& c : graph[i]) {
      cin >> c;
      c--;
      graph[c].push_back(i);
    }
  }
  vector<int> matching = HopcroftKarp(graph, left);
  print_matching(matching, n);
  return 0;
}
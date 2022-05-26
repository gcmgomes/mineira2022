#include <queue>

#include "testlib.h"

using namespace std;

const int MAX_N = 1000;
const int MAX_E = 1000;

bool IsConnectedBipartite(vector<vector<int>>& graph) {
  vector<int> visits(graph.size(), -1);
  int total_visits = 1;
  stack<int> s;
  s.push(0);
  visits[0] = 0;
  while (s.size()) {
    int u = s.top();
    s.pop();
    for (auto& v : graph[u]) {
      if (visits[v] == -1) {
        visits[v] = 1 - visits[u];
        total_visits++;
        s.push(v);
      }
      if (visits[v] == visits[u]) {
        return false;
      }
    }
  }
  return total_visits == graph.size();
}

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);
  int n = inf.readInt(1, MAX_N);
  inf.readSpace();
  int e = inf.readInt(1, MAX_E);
  inf.readEoln();

  vector<vector<int>> graph(n + e);
  for (int i = 0; i < n; i++) {
    int n_i = inf.readInt(1, e);
    inf.readSpace();
    graph[i] = inf.readInts(n_i);
    for (auto& v : graph[i]) {
      assert(n < v && v <= n + e);
      v--;
      graph[v].push_back(i);
    }
    inf.readEoln();
  }
  inf.readEof();
  assert(IsConnectedBipartite(graph));
  return 0;
}

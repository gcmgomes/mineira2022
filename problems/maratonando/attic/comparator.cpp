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
double INFD = std::numeric_limits<double>().max();
int ERR = -1, ACCEPTED = 4;

double PI = acos(-1);

bool CheckEdgesExist(vector<vector<int>>& graph,
                     vector<pair<int, int>>& team_edges) {
  for (auto& e : team_edges) {
    if (e.first < 0 || e.first >= graph.size()) {
      return false;
    }
    bool found = false;
    for (auto& v : graph[e.first]) {
      found = found || v == e.second;
    }
    if (!found) {
      return false;
    }
  }
  return true;
}

bool IsMatching(vector<pair<int, int>>& team_edges, vector<int>& matched) {
  for (auto& e : team_edges) {
    if (matched[e.first] || matched[e.second]) {
      return false;
    }
    matched[e.first] = matched[e.second] = 1;
  }
  return true;
}

bool IsConnected(vector<vector<int>>& graph, vector<int>& matched,
                 int vertex_count, int root) {
  queue<int> q;
  q.push(root);
  vector<int> visited(matched.size(), 0);
  visited[root] = 1;
  while (q.size()) {
    int u = q.front();
    q.pop();
    vertex_count--;
    for (auto& v : graph[u]) {
      if (visited[v] || !matched[v]) {
        continue;
      }
      visited[v] = 1;
      q.push(v);
    }
  }
  return vertex_count == 0;
}

int main(int argc, char** argv) {
  ifstream judge(argv[2]);
  freopen(argv[3], "r", stdin);  // read problem input
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
  int judge_matching_size = 0, team_matching_size = 0;
  judge >> judge_matching_size;
  judge.close();
  freopen(argv[1], "r", stdin);  // read team solution.
  scanf("%d", &team_matching_size);
  if (judge_matching_size == 0 && team_matching_size == 0) {
    return ACCEPTED;
  }
  if (judge_matching_size > team_matching_size) {
    fprintf(stderr, "Team found did not find a maximum connected matching.\n");
    return ERR;  // whatever is the error code for boca/box.
  }
  vector<pair<int, int>> team_edges(team_matching_size);
  for (auto& e : team_edges) {
    cin >> e.first >> e.second;
    e.first--;
    e.second--;
  }
  vector<int> matched(n + e, 0);
  if (!CheckEdgesExist(graph, team_edges) || !IsMatching(team_edges, matched)) {
    fprintf(stderr, "Team reported something that is not a matching.\n");
    return ERR;
  }
  if (!IsConnected(graph, matched, 2 * team_edges.size(),
                   team_edges[0].first)) {
    fprintf(stderr, "Team reported a matching that is not connected.\n");
    return ERR;
  } else if (judge_matching_size != team_matching_size) {
    fprintf(stderr,
            "HOUSTON, WE HAVE A PROBLEM. Team found a matching bigger than the "
            "judge.\n");
  }
  return ACCEPTED;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

struct Kuhn {
  int N, M;
  std::vector<std::vector<int>> E;
  std::vector<int> matchA, matchB;
  std::vector<bool> vis;

  Kuhn(int N, int M) : N(N), M(M), E(N), matchA(N, -1), matchB(M, -1), vis(N) {}

  void add_edge(int u, int v) {
    E[u].push_back(v);
  }

  bool augment(int u) {
    vis[u] = true;
    for (auto v : E[u]) {
      int w = matchB[v];
      if (w == -1 || (!vis[w] && augment(w))) {
        matchA[u] = v, matchB[v] = u;
        return true;
      }
    }
    return false;
  }

  std::vector<int> U;

  int maximum_matching() {
    int max = 0;
    while (true) {
      bool converged = true;
      std::fill(vis.begin(), vis.end(), false);
      for (auto u : U) {
        if (!vis[u] && matchA[u] == -1 && augment(u)) {
          converged = false;
          ++max;
          break;
        }
      }
      if (converged) break;
    }
    return max;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int N, E;
  std::cin >> N >> E;

  std::vector<std::vector<int>> G(N + E);
  for (int u = 0; u < N; ++u) {
    int k;
    std::cin >> k;
    G[u].resize(k);
    for (auto& v : G[u]) {
      std::cin >> v;
      --v;
      G[v].push_back(u);
    }
  }

  std::vector<std::pair<int, int>> best;

  std::vector<int> dist(N + E, -1);

  for (int s = 0; s < N; ++s) {
    if (dist[s] != -1) continue;

    Kuhn kuhn(N, E);

    std::queue<int> q;
    dist[s] = 0;
    q.push(s);

    while (!q.empty()) {
      int u = q.front();
      q.pop();

      for (auto v : G[u]) {
        if (dist[v] == -1) {
          dist[v] = dist[u] + 1;
          q.push(v);
        }
      }

      if (u < N) {
        kuhn.U.push_back(u);
        std::sort(G[u].begin(), G[u].end(), [&](int v1, int v2) { return dist[v1] < dist[v2]; });
        for (auto v : G[u]) {
          kuhn.add_edge(u, v - N);
        }
      }
    }

    if (kuhn.maximum_matching() > best.size()) {
      best.clear();
      for (auto u : kuhn.U) {
        int v = kuhn.matchA[u];
        if (v != -1) {
          best.emplace_back(u, N + v);
        }
      }
    }
  }

  std::cout << best.size() << '\n';
  for (auto [u, v] : best) {
    std::cout << u + 1 << ' ' << v + 1 << '\n';
  }

  exit(0);
}

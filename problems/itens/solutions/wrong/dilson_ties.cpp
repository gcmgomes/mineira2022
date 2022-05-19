#include <iostream>
#include <queue>
#include <string>
#include <vector>

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

int main() {
  int n, m, t, ci, cj;
  std::cin >> n >> m >> t >> ci >> cj;
  ci--;
  cj--;

  std::vector<std::string> g(n);
  for (std::string &row : g) {
    std::cin >> row;
  }

  std::vector<std::vector<int>> dist(n, std::vector<int>(m, n + m));
  std::queue<std::pair<int, int>> q;
  dist[ci][cj] = 0;
  q.push({ci, cj});
  while (!q.empty()) {
    const std::pair<int, int> x = q.front();
    q.pop();

    const int new_dist = dist[x.first][x.second] + 1;

    const std::vector<std::pair<int, int>> deltas = {
        {0, 1}, {-1, 0}, {0, -1}, {1, 0}};
    for (const auto delta : deltas) {
      const std::pair<int, int> y = {x.first + delta.first,
                                     x.second + delta.second};
      if (y.first < 0 || y.first >= n || y.second < 0 || y.second >= m ||
          g[y.first][y.second] != '.' || dist[y.first][y.second] <= new_dist) {
        continue;
      }
      dist[y.first][y.second] = new_dist;
      q.push(y);
    }
  }

  int num_free = 0;
  int num_reached = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (g[i][j] == '.') {
        num_free++;
        if (dist[i][j] < t) {
          num_reached++;
        }
      }
    }
  }

  const int div = gcd(num_free, num_reached);
  std::cout << (num_reached / div) << ' ' << (num_free / div) << std::endl;
}

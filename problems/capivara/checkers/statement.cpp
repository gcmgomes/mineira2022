#include <queue>

#include "testlib.h"

using namespace std;

const int MAX_N = 50000000;
const int MAX_M = 50000000;
const int MAX_K = 50000000;

int component_size(vector<vector<int>>& grid, vector<vector<int>>& visits,
                   int i, int j) {
  if (visits[i][j]) {
    return 0;
  }
  vector<pair<int, int>> moves = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
  int pos_color = grid[i][j];
  queue<pair<int, int>> q;
  q.push({i, j});
  int size = 0;
  while (q.size()) {
    auto p = q.front();
    q.pop();
    if (grid[p.first][p.second] != pos_color) {
      continue;
    }
    size++;
    visits[p.first][p.second] = 1;
    for (auto& m : moves) {
      auto nex = p;
      nex.first += m.first;
      nex.second += m.second;
      if ((nex.first < 0 || nex.first >= grid.size()) ||
          (nex.second < 0 || nex.second >= grid[0].size()) ||
          visits[nex.first][nex.second]) {
        continue;
      }
      q.push(nex);
    }
  }
  return size;
}

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);
  int n = inf.readInt(1, MAX_N);
  inf.readSpace();
  int m = inf.readInt(1, MAX_M);
  inf.readSpace();
  int x = inf.readInt(2, MAX_K);
  inf.readEoln();

  vector<vector<int>> grid(n, vector<int>(m, 0)), visits;
  visits = grid;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      grid[i][j] = inf.readInt(1, 3);
      if (j < m - 1) {
        inf.readSpace();
      }
    }
    inf.readEoln();
  }
  inf.readEof();

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int size = component_size(grid, visits, i, j);
      if (size > MAX_K) {
        return -1;
      }
    }
  }
  return 0;
}

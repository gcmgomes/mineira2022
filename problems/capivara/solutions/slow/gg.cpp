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

double PI = acos(-1);

int total_jewels = 0;

int ColorCount(vector<int>& path, int color) {
  int swaps = 0;
  for (auto c : path) {
    swaps += (c != color) ? 1 : 0;
  }
  return swaps;
}

int SolveGrid(vector<vector<int>>& grid, int n, int m, int k) {
  if (n * m > k) {
    return -1;
  }
  int min_swaps = INF;
  for (int color = 1; color < 4; color++) {
    int swaps = 0;
    for (auto& row : grid) {
      swaps += ColorCount(row, color);
    }
    min_swaps = min(min_swaps, swaps);
  }
  return min_swaps;
}

int SolvePathMid(vector<int>& path, int k) {
  int min_swaps = INF;
  for (int color = 1; color < 4; color++) {
    int swaps = (path[k - 1] == color) ? 2 : 0;
    swaps += ColorCount(path, color);
    min_swaps = min(min_swaps, swaps);
  }
  return min_swaps;
}

int SolvePath(vector<int>& path, int k) {
  if (path.size() == 2 * k - 1) {
    return SolvePathMid(path, k);
  }
  int min_swaps = INF;
  for (int merger = path.size() - k; merger < k; merger++) {
    for (int color = 1; color < 4; color++) {
      cout << min_swaps << std::endl;
      int swaps = (path[merger] == color) ? 2 : 0;
      swaps += ColorCount(path, color);
      min_swaps = min(min_swaps, swaps);
    }
  }
  return min_swaps;
}

int main() {
  int n = 0, m = 0, k = 0;
  cin >> n >> m >> k;
  total_jewels = n * m;
  vector<vector<int>> grid(n, vector<int>(m, 0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> grid[i][j];
    }
  }
  if (total_jewels < k || total_jewels > 2 * k - 1) {
    cout << -1 << endl;
  } else if (n == 1) {
    cout << SolvePath(grid[0], k) << endl;
  } else if (m == 1) {
    vector<int> path(n);
    for (int i = 0; i < path.size(); i++) {
      path[i] = grid[i][0];
    }
    cout << SolvePath(path, k) << endl;
  } else {
    cout << SolveGrid(grid, n, m, k) << endl;
  }
  return 0;
}

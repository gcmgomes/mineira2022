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

void RemoveElement(int val, map<int, int>& nums) {
  nums[val]--;
  if (nums[val] < 1) {
    nums.erase(val);
  }
}

void RemoveColumn(vector<vector<int>>& grid, int i, int j, int k,
                  map<int, int>& nums) {
  for (int il = i; il < i + k && il < grid.size(); il++) {
    RemoveElement(grid[il][j], nums);
  }
}

void AddColumn(vector<vector<int>>& grid, int i, int j, int k,
               map<int, int>& nums) {
  for (int il = i; il < i + k && il < grid.size(); il++) {
    nums[grid[il][j]]++;
  }
}

void RemoveRow(vector<vector<int>>& grid, int i, int j, int k,
               map<int, int>& nums) {
  for (int jl = j; jl < j + k && jl < grid[i].size(); jl++) {
    RemoveElement(grid[i][jl], nums);
  }
}

void AddRow(vector<vector<int>>& grid, int i, int j, int k,
            map<int, int>& nums) {
  for (int jl = j; jl < j + k && jl < grid[i].size(); jl++) {
    nums[grid[i][jl]]++;
  }
}

int GetTime(map<int, int>& nums) {
  if (nums.count(MINF)) {
    return INF;
  }
  cerr << nums.size() << endl;
  return nums.rbegin()->first;
}

string point(int i, int j) {
  stringstream s;
  s << '(' << i << ", " << j << ')';
  return s.str();
}

int Solve(vector<vector<int>>& grid, int k) {
  int ans = INF;
  map<int, int> times;
  for (int i = 0; i < k; i++) {
    AddRow(grid, i, 0, k, times);
  }
  bool left_to_right = true;

  for (int i = k; i <= grid.size(); i++) {
    if (left_to_right) {
      for (int j = k; j <= grid[0].size(); j++) {
        ans = min(ans, GetTime(times));
        // cerr << "looking at " << point(i - k, j - k) << " -- " << point(i, j)
        //      << endl;
        if (j < grid[i].size()) {
          AddColumn(grid, i - k, j, k, times);
          RemoveColumn(grid, i - k, j - k, k, times);
        }
      }
      RemoveRow(grid, i - k, grid[0].size() - k, k, times);
    } else {
      for (int j = grid[0].size() - k - 1; j >= 0; j--) {
        ans = min(ans, GetTime(times));
        // cerr << "looking at " << point(i - k, j + k) << " -- " << point(i, j)
        //      << endl;
        if (j > 0) {
          AddColumn(grid, i - k, j, k, times);
          RemoveColumn(grid, i - k, j + k, k, times);
        }
      }
      RemoveRow(grid, i - k, 0, k, times);
    }
    if (i < grid.size()) {
      AddRow(grid, i, grid[0].size() - k, k, times);
    }
    left_to_right = !left_to_right;
  }
  return (ans == INF) ? -1 : ans;
}

int main() {
  iostream::sync_with_stdio(false);
  int n = 0, m = 0, k = 0, q = 0;
  cin >> n >> m >> k >> q;
  vector<vector<int>> grid(n, vector<int>(m, MINF));
  for (int i = 0; i < q; i++) {
    int a = 0, b = 0, d = 0;
    cin >> a >> b >> d;
    grid[a - 1][b - 1] = d;
  }
  cout << Solve(grid, k) << endl;
  return 0;
}
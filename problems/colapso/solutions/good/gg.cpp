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
int MINF = -1;
double INFD = std::numeric_limits<double>().max();

double PI = acos(-1);

string point(int i, int j, bool open_bracket = false) {
  stringstream s;
  s << ((open_bracket) ? '[' : '(') << i << ", " << j << ')';
  return s.str();
}

void RemoveElement(int val, map<int, int>& nums, bool silent = false) {
  if (!silent) {
    // cerr << "    Removing " << val << endl;
  }
  nums[val]--;
  if (nums[val] < 1) {
    nums.erase(val);
  }
}

void RemoveColumn(vector<vector<int>>& grid, int i, int j, int k,
                  map<int, int>& nums) {
  //   cerr << "Removing column " << j << " interval " << point(i, i + k, true)
  //    << endl;
  for (int il = i; il < i + k && il < grid.size(); il++) {
    RemoveElement(grid[il][j], nums);
  }
}

void AddColumn(vector<vector<int>>& grid, int i, int j, int k,
               map<int, int>& nums) {
  //   cerr << "Adding column " << j << " interval " << point(i, i + k, true)
  //    << endl;
  for (int il = i; il < i + k && il < grid.size(); il++) {
    // cerr << "    Adding " << grid[il][j] << endl;
    nums[grid[il][j]]++;
  }
}

void RemoveRow(vector<vector<int>>& grid, int i, int j, int k,
               map<int, int>& nums) {
  //   cerr << "Removing row " << i << " interval " << point(j, j + k, true) <<
  //   endl;
  for (int jl = j; jl < j + k && jl < grid[i].size(); jl++) {
    RemoveElement(grid[i][jl], nums);
  }
}

void AddRow(vector<vector<int>>& grid, int i, int j, int k,
            map<int, int>& nums) {
  //   cerr << "Adding row " << i << " interval " << point(j, j + k, true) <<
  //   endl;
  for (int jl = j; jl < j + k && jl < grid[i].size(); jl++) {
    // cerr << "    Adding " << grid[i][jl] << endl;
    nums[grid[i][jl]]++;
  }
}

int GetTime(map<int, int>& nums) {
  if (nums.count(MINF)) {
    return INF;
  }
  //   cerr << nums.size() << endl;
  return nums.rbegin()->first;
}

void print_map(map<int, int>& nums) {
  for (auto& p : nums) {
    cerr << point(p.first, p.second) << " ";
  }
  if (nums.size()) {
    cerr << endl;
  }
}

bool CheckMove(vector<vector<int>>& grid, int i, int ui, int j, int uj,
               map<int, int> nums) {
  print_map(nums);
  for (int il = i; il < ui; il++) {
    for (int jl = j; jl < uj; jl++) {
      cerr << grid[il][jl] << " ";
      RemoveElement(grid[il][jl], nums, true);
    }
    cerr << endl;
  }
  return nums.empty();
}

int Solve(vector<vector<int>>& grid, int k) {
  int ans = INF;
  map<int, int> times;
  for (int i = 0; i < k; i++) {
    AddRow(grid, i, 0, k, times);
  }
  bool left_to_right = true;

  int base_i = 0, base_j = 0;
  for (int i = k; i <= grid.size(); i++, base_i++) {
    if (left_to_right) {
      base_j = 0;
      for (int j = k; j <= grid[0].size(); j++, base_j++) {
        ans = min(ans, GetTime(times));
        // cerr << "left-right: looking at " << point(base_i, base_j) << " -- "
        //      << point(i - 1, j - 1) << endl;
        // assert(CheckMove(grid, base_i, i, base_j, j, times));
        if (j < grid[0].size()) {
          AddColumn(grid, base_i, j, k, times);
          RemoveColumn(grid, base_i, base_j, k, times);
        }
      }
      RemoveRow(grid, base_i, base_j - 1, k, times);
      if (i < grid.size()) {
        AddRow(grid, i, base_j - 1, k, times);
      }
    } else {
      base_j = grid[0].size() - 1;
      for (int j = grid[0].size() - k - 1; j >= 0; j--, base_j--) {
        ans = min(ans, GetTime(times));
        // cerr << "right-left: looking at " << point(base_i, base_j) << " -- "
        //      << point(i - 1, j + k) << endl;
        // assert(CheckMove(grid, base_i, i, j + 1, base_j + 1, times));
        AddColumn(grid, i - k, j, k, times);
        RemoveColumn(grid, base_i, base_j, k, times);
      }
      RemoveRow(grid, base_i, 0, k, times);
      if (i < grid.size()) {
        AddRow(grid, i, 0, k, times);
      }
    }
    left_to_right = !left_to_right;

    // cerr << "Base grid" << endl;
    // CheckMove(grid, 0, grid.size(), 0, grid[0].size(), map<int, int>());
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
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

int main() {
  int n = 0;
  string level;
  cin >> n >> level;
  // this should fail on tests where the first block is a hole.
  int power = 1;
  int jumps = 0;
  bool decrementing = false;
  for (auto& block : level) {
    if (block == 'x') {
      power = (decrementing) ? 1 : power + 1;
      decrementing = false;
    } else {
      power--;
      jumps += (decrementing) ? 0 : 1;
      decrementing = true;
    }
    if (decrementing && power < 0) {
      cout << -1 << endl;
      return 0;
    }
  }
  cout << jumps << endl;
  return 0;
}

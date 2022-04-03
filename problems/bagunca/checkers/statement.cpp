#include "testlib.h"

using namespace std;

int component_size(vector<vector<int>>& graph, vector<vector<int>>& visits,
                   int i, int j) {
  vector<pair<int, int>> moves = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
  queue<pair<int, int>> que;
  int size = 0;
  que.push({ i, j });
  while (que.size()) {
    size++;
    auto pos = que.front();
    visits[pos.first][pos.second] = 1;
    que.pop();
    for (auto l : moves) {
      auto n = pos;
      n.first += l.first;
      n.second += l.second;
      if (n.first < 0 || n.first >= visits.size() || n.second < 0 ||
          n.second >= visits.front().size()) {
        continue;
      }
      if (!visits[n.first][n.second] &&
          graph[pos.first][pos.second] == graph[n.first][n.second]) {
        que.push(n);
      }
    }
  }
  return size;
}

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);

  int n = inf.readInt(1, 100000);
  inf.readSpace();
  int m = inf.readInt(1, 100000);
  inf.readSpace();
  int x = inf.readInt(1, 100000);
  inf.readSpace();
  int k = inf.readInt(1, 100);
  inf.readEoln();
  inf.readEof();
}

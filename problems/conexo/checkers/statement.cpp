#include <queue>

#include "testlib.h"

using namespace std;

const int MAX_N = 1000;
const int MAX_E = 1000;

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);
  int n = inf.readInt(1, MAX_N);
  inf.readSpace();
  int e = inf.readInt(1, MAX_E);
  inf.readEoln();

  for (int i = 0; i < n; i++) {
    int n_i = inf.readInt(1, e);
    vector<int> vs = inf.readInts(n_i);
    for (auto& v : vs) {
      assert(n < v && v <= n + e);
    }
    inf.readEoln();
  }
  inf.readEof();
  return 0;
}

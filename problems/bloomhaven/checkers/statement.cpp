#include "testlib.h"

using namespace std;

int MINN = 3, MAXN = 1000000;
int MINV = -100000, MAXV = -MINV;

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);

  int n = inf.readInt(MINN, MAXN);
  inf.readEoln();
  vector<int> edges = inf.readInts(n, MINV, MAXV);
  inf.readEoln();
  inf.readEof();
}

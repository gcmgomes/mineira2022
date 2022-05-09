#include "testlib.h"

using namespace std;

const int MAX_N = 100000;
const int MAX_K = 1000000000;

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);

  int n = inf.readInt(1, MAX_N);
  inf.readEoln();
  
  for (int i = 0; i < n; i++) {
    inf.readInt(1, MAX_K);
    if (i < n - 1) {
      inf.readSpace();
    }
  }
  inf.readEoln();
  inf.readEof();
}

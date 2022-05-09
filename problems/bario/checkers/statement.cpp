#include <queue>

#include "testlib.h"

using namespace std;

const int MAX_N = 5000000;

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);
  int n = inf.readInt(1, MAX_N);
  inf.readEoln();
  string level = inf.readWord();
  if (level.size() != n) {
    inf.quit(TResult::_fail, "Level size doesn't match passed size");
  }
  if (level.back() == '.') {
    inf.quit(TResult::_fail, "Level ends on an empty block");
  }
  for (auto& c : level) {
    if (c != '.' && c != 'x') {
      inf.quit(TResult::_fail, "Level has a bad char");
    }
  }
  inf.readEoln();
  inf.readEof();
}

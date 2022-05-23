#include "testlib.h"

using namespace std;


int main(int argc, char* argv[]) {
  registerValidation(argc, argv);

  int n = inf.readInt(3, 100000);
  inf.readEoln();
  
  for (int i = 0; i < n + 1; i++)
  {
    int x = inf.readInt(-100000, 100000);
    inf.readSpace();
    int y = inf.readInt(-100000, 100000);
    inf.readEoln();
  }

  inf.readEof();

}

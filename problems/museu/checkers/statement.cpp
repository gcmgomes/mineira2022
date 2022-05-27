#include "testlib.h"
#include <set>
#include <utility>

using namespace std;


int main(int argc, char* argv[]) {
  registerValidation(argc, argv);

  const int min_points = 3;
  const int max_points = 100'000;
  const int min_coordinate = -100'000;
  const int max_coordinate = 100'000;

  int n = inf.readInt(min_points, max_points);
  inf.readEoln();

  set<pair<int, int> > st;
  
  for (int i = 0; i < n + 1; i++)
  {
    int x = inf.readInt(min_coordinate, max_coordinate);
    inf.readSpace();
    int y = inf.readInt(min_coordinate, max_coordinate);
    inf.readEoln();

    st.insert({x,y});
  }

  if (st.size() != (n + 1))
  {
    inf.quit(TResult::_fail, "Input has duplicated points...");
  }

  inf.readEof();

}

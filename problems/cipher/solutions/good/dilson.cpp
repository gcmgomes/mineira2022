#include <iostream>
#include <string>
#include <cassert>
#include <vector>

/******************************************************************************
 * Templated functions to read the input
 *****************************************************************************/
template <typename T> T Read() {
  T value;
  std::cin >> value;
  assert(std::cin);
  return value;
}


using namespace std;

int main() {
    const auto s = Read<string>();
    const auto n = Read<int>();
    
    if (n == 1) {
        cout << s << endl;
        return 0;
    }

    vector<vector<int>> rows(n);
    int i = 0;
    int dir = 1;
    for (int pos = 0; pos < s.size(); pos++) {
        rows[i].push_back(pos);
        i += dir;
        if (i == n - 1 || i == 0) {
            dir *= -1;
        }
    }

    string res = s;
    int j = 0;
    for (int i = 0; i < n; i++) {
        for (const int pos : rows[i]) {
            res[pos] = s[j];
            j++;
        }
    }
    cout << res << endl;
}

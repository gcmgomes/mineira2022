#include <iostream>
#include <cassert>
#include <vector>
#include <limits>

/******************************************************************************
 * Templated functions to read the input
 *****************************************************************************/
template <typename T> T Read() {
  T value;
  std::cin >> value;
  assert(std::cin);
  return value;
}

template <typename T> std::vector<T> ReadVector(const int n) {
  std::vector<T> values;
  values.reserve(n);
  for (int i = 0; i < n; i++) {
    values.push_back(Read<T>());
  }
  return values;
}


using ll = long long;
using namespace std;

int main() {
    const auto n = Read<int>();
    auto v = ReadVector<ll>(n);
    for (int i = 0; i < n; i++) {
        v.push_back(v[i]);
    }

    ll ans = numeric_limits<ll>::min();
    for (int s = 0; s < n; s++) {
        ll sum = 0;
        for (int i = s; i < s + n - n%2; i += 2) {
            sum += v[i];
            if (sum > ans) {
                ans = sum;
            }
        }
    }

    cout << ans << endl;
}

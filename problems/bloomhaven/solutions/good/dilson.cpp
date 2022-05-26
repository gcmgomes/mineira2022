#include <iostream>
#include <vector>
#include <cassert>
#include <limits>

using namespace std;
using ll = long long;
/******************************************************************************
 * Templated functions to read the input
 *****************************************************************************/
template <typename T> T Read() {
  T value;
  std::cin >> value;
  assert(std::cin);
  return value;
}


/*****************************************************************************/

constexpr int MAXN = 1'000'000;
ll v[2][MAXN];
ll pre[2][MAXN];
ll max_pre[2][MAXN];
ll min_pre[2][MAXN];
ll max_suf[2][MAXN];
int n;
int k[2];

int main() {
    n = Read<int>();
    for (int i = 0; i < n; i++) {
        v[i%2][k[i%2]++] = Read<ll>();
    }
    
    for (int p = 0; p < 2; p++) {
        for (int i = 0; i < k[p]; i++) {
            pre[p][i + 1] = pre[p][i] + v[p][i];
            max_pre[p][i + 1] = max(max_pre[p][i], pre[p][i + 1]);
            min_pre[p][i + 1] = min(min_pre[p][i], pre[p][i + 1]);
        }


        for (int i = 0; i < k[p]; i++) {
            max_suf[p][i + 1] = max(max_suf[p][i], pre[p][k[p]] - pre[p][k[p] - i - 1]);
        }
    }

    ll sol = numeric_limits<ll>::min();
    for (int p = 0; p < 2; p++) {
        for (int i = 0; i < k[p]; i++) {
            sol = max(sol, pre[p][i + 1] - min_pre[p][i]);
        }
    }

    if (n % 2) {
        for (int s0 = 1; s0 < k[0]; s0++) {
            const int s1 = (n - 1) / 2 - s0;
            assert(s1 <= k[1]);
            assert(s1 >= 0);
            if (s1 == 0) {
                continue;
            }

            sol = max(sol, max_suf[0][s0] + pre[1][s1]);
            sol = max(sol, max_suf[1][s1] + pre[0][s0]);
        }
    } else {
        for (int p = 0; p < 2; p++) {
            for (int i = 1; i < k[p] - 1; i++) {
                sol = max(sol, pre[p][k[p]] - (pre[p][i + 1] - max_pre[p][i]));
            }
        }
    }

    cout << sol << endl;
}

#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<ll> p(n);
    for (auto& pi : p) cin >> pi;

    int q;
    cin >> q;
    for (int qi = 0; qi < q; qi++) {
        int a, b;
        cin >> a >> b;
        a--;
        ll max_dd = 0;
        ll max_dd_rel_num = 0;
        ll max_dd_rel_den = 1;
        for (int i = a; i < b; i++) {
            for (int j = i; j < b; j++) {
                ll dd = std::max(p[i] - p[j], 0ll);
                if (dd > max_dd) {
                    max_dd = dd;
                }

                ll g = gcd(dd, p[i]);
                ll dd_rel_num = dd / g;
                ll dd_rel_den = p[i] / g;
                if (dd_rel_num * max_dd_rel_den > max_dd_rel_num * dd_rel_den) {
                    max_dd_rel_num = dd_rel_num;
                    max_dd_rel_den = dd_rel_den;
                }
            }
        }
        cout << max_dd << ' ' << max_dd_rel_num << ' ' << max_dd_rel_den << '\n';
    }

}

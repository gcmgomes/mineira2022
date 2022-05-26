#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

template <class T, T combine(T, T), T max_fn(T, T)> struct Segtree {
    vector<T> maxi, lazy;
    T id;

    Segtree(int n, T init, T id) : id(id) {
        maxi = vector<T>(4*n, init);
        lazy = vector<T>(4*n, id);
    }

    void propagate(int root, int l, int r) {
        maxi[root] = combine(maxi[root], lazy[root]);
        if (l != r) {
            lazy[2*root+1] = combine(lazy[2*root+1], lazy[root]);
            lazy[2*root+2] = combine(lazy[2*root+2], lazy[root]);
        }
        lazy[root] = id;
    }

    void add(int root, int l, int r, int a, int b, T val) {
        if (r < a || l > b)
            return;
        if (l >= a && r <= b) {
            lazy[root] = combine(lazy[root], val);
            return;
        }
        propagate(root, l, r);

        int mid = (l+r)/2;
        add(2*root+1, l, mid, a, b, val);
        add(2*root+2, mid+1, r, a, b, val);
        maxi[root] = max_fn(combine(maxi[2*root+1], lazy[2*root+1]),
                            combine(maxi[2*root+2], lazy[2*root+2]));
    }

    T query(int root, int l, int r, int a, int b) {
        if (l >= a && r <= b)
            return combine(maxi[root], lazy[root]);
        propagate(root, l, r);

        int mid = (l+r)/2;
        if (b <= mid)
            return query(2*root+1, l, mid, a, b);
        if (a >= mid+1)
            return query(2*root+2, mid+1, r, a, b);
        return max_fn(query(2*root+1, l, mid, a, b),
                      query(2*root+2, mid+1, r, a, b));
    }
};

int combine1(int f1, int f2) {
    return f1+f2;
}

int max1(int f1, int f2) {
    return max(f1, f2);
}

pair<int, int> combine2(pair<int, int> f1, pair<int, int> f2) {
    long long n = (long long)f1.first * f2.first;
    long long d = (long long)f1.second * f2.second;
    long long g = __gcd(n, d);
    if (g < 0) g = -g;
    return make_pair(n/g, d/g);
}

pair<int, int> max2(pair<int, int> f1, pair<int, int> f2) {
    return (long long)f1.first * f2.second >= (long long)f2.first * f1.second ? f1 : f2;
}

int main() {
    ios::sync_with_stdio(false);

    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++)
        cin >> p[i];

    int q;
    cin >> q;
    vector<pair<pair<int, int>, int>> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].first.second >> queries[i].first.first;
        queries[i].first.first--; queries[i].first.second--;
        queries[i].second = i;
    }
    sort(queries.begin(), queries.end());

    Segtree<int, combine1, max1> s1(n, 0, 0);
    Segtree<pair<int, int>, combine2, max2> s2(n, {-1, 1}, {1, 1});

    int ptr = 0;
    vector<pair<int, int>> min_stack; // increasing in 2nd coord
    min_stack.emplace_back(-1, -1);

    vector<pair<int, pair<int, int>>> ans(q);
    for (int i = 0; i < q; i++) {
        int b = queries[i].first.first;
        int a = queries[i].first.second;
        int idx = queries[i].second;

        while (ptr <= b) {
            int val = p[ptr];
            while (min_stack.back().second >= val) {
                int idx = min_stack.back().first;
                int oldval = min_stack.back().second;
                int g = __gcd(val, oldval);

                min_stack.pop_back();
                s1.add(0, 0, n-1, min_stack.back().first+1, idx, oldval - val);
                s2.add(0, 0, n-1, min_stack.back().first+1, idx, make_pair(val/g, oldval/g));
            }

            min_stack.emplace_back(ptr++, val);
        }

        int d1 = s1.query(0, 0, n-1, a, b);
        pair<int, int> d2 = s2.query(0, 0, n-1, a, b);

        d2.first += d2.second;
        assert(__gcd(d2.first, d2.second) == 1);
        ans[idx] = make_pair(d1, make_pair(d2.first, d2.second));
    }

    for (int i = 0; i < q; i++)
        cout << ans[i].first << " " << ans[i].second.first << " " << ans[i].second.second << endl;
}

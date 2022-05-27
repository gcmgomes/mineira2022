#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

long long INF = std::numeric_limits<long long>().max();
long long MINF = std::numeric_limits<long long>().min();
double INFD = std::numeric_limits<double>().max();

double PI = acos(-1);

/*
 * Templated SegTree implementation based on the concept of Monoids.
 * A Monoid over a set of elements S has an identity element I from S and an
 * associative bynary operator OP such that OP(I, X) = OP(X, I) = X for any X
 * in S.
 *
 * The template argument Monoid should be a type such that:
 *  - Monoid::type is the type of the elements in S.
 *  - Monoid::Identity() returns the identity element.
 *  - Monoid::ApplyOperator(a, b) returns OP(a, b).
 *
 * The query over a range [L, R) returns the value of
 * OP(X[L], OP(X[L + 1], ... OP(X[R -1])), where X is the sequence of values in
 * the segtree.
 */
template <typename Monoid> class SegTree {
public:
  SegTree(const int size) : size_(size), nodes_(4 * size, monoid_.Identity()){};

  void Update(const int index, typename Monoid::type value) {
    UpdateRecursively(index, value, RootNode());
  }

  typename Monoid::type Query(const int range_start,
                              const int range_end) const {
    return QueryRecursively(range_start, range_end, RootNode());
  }

private:
  int size_;
  Monoid monoid_;
  std::vector<typename Monoid::type> nodes_;

  struct NodeIndex {
    int range_start;
    int range_end;
    int index;

    NodeIndex LeftChild() const {
      return {.range_start = range_start,
              .range_end = (range_start + range_end) / 2,
              .index = 2 * index + 1};
    }
    NodeIndex RightChild() const {
      return {.range_start = (range_start + range_end) / 2,
              .range_end = range_end,
              .index = 2 * index + 2};
    }
    bool Contains(const int index) const {
      return index >= range_start && index < range_end;
    }

    bool IsInsideRange(const int range_start, const int range_end) const {
      return range_start <= this->range_start && this->range_end <= range_end;
    }

    int RangeSize() const { return std::max(range_end - range_start, 0); }
  };

  NodeIndex RootNode() const {
    return {.range_start = 0, .range_end = size_, .index = 0};
  }

  typename Monoid::type UpdateRecursively(const int index,
                                          typename Monoid::type value,
                                          const NodeIndex node) {

    const int range_size = node.RangeSize();
    if (range_size == 0) {
      return monoid_.Identity();
    }
    if (!node.Contains(index)) {
      return nodes_[node.index];
    }
    if (range_size == 1) {
      nodes_[node.index] = value;
      return value;
    }
    nodes_[node.index] = monoid_.ApplyOperator(
        UpdateRecursively(index, value, node.LeftChild()),
        UpdateRecursively(index, value, node.RightChild()));
    return nodes_[node.index];
  }

  typename Monoid::type QueryRecursively(const int range_start,
                                         const int range_end,
                                         const NodeIndex node) const {
    if (node.RangeSize() == 0) {
      return monoid_.Identity();
    }
    if (node.IsInsideRange(range_start, range_end)) {
      return nodes_[node.index];
    }
    if (!node.Contains(range_start) && !node.Contains(range_end - 1)) {
      return monoid_.Identity();
    }
    return monoid_.ApplyOperator(
        QueryRecursively(range_start, range_end, node.LeftChild()),
        QueryRecursively(range_start, range_end, node.RightChild()));
  }
};

/******************************************************************************
 * Finally, the problem solution.
 *****************************************************************************/

using ll = long long;



struct MinMonoid {
  using type = ll;

  type Identity() const {
    return INF;
  }

  type ApplyOperator(const type &left, const type &right) const {
    return std::min(left, right);
  }
};


long long Solve(const vector<int>& edges, int size) {
  long long best = MINF;
  vector<long long> pre(edges.size() + 1);
  for (int i = 0; i < edges.size(); i++) {
    pre[i + 1] = pre[i] + edges[i];
  }
  SegTree<MinMonoid> st(pre.size());
  for (int i = 0; i < pre.size(); i++) {
    st.Update(i, pre[i]);
  }
  for (int i = 0; i < edges.size(); i++) {
      const int ub = i + 1;
      const int lb = i - size + 1;
      const ll sub = pre[i + 1] - st.Query(lb, ub);
      best = max(best, sub);
  }
  return best;
}

void Replicate(vector<int>& edges, int n) {
  for (int i = 0; i < n - 1; i++) {
    edges.push_back(edges[i]);
  }
}

int main() {
  iostream::sync_with_stdio(false);
  int n = 0;
  scanf("%d", &n);
  vector<int> edges(n, 0);
  for (auto& e : edges) {
    scanf("%d", &e);
  }
  if (n % 2) {
    vector<int> split_edges;
    for (int i = 0; i < edges.size(); i = i + 2) {
      split_edges.push_back(edges[i]);
    }
    for (int i = 1; i < edges.size(); i = i + 2) {
      split_edges.push_back(edges[i]);
    }
    for (int i = 0; i < edges.size(); i = i + 2) {
      split_edges.push_back(edges[i]);
    }
    printf("%lld\n", Solve(split_edges, (n - 1) / 2));
  } else {
    vector<int> odds, evens;
    for (int i = 0; i < edges.size(); i++) {
      vector<int>& v = (i % 2) ? odds : evens;
      v.push_back(edges[i]);
    }
    Replicate(odds, n);
    Replicate(evens, n);
    printf("%lld\n", max(Solve(odds, n / 2), Solve(evens, n / 2)));
  }
  return 0;
}

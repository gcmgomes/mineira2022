#include <cassert>
#include <functional>
#include <iostream>
#include <limits>
#include <optional>
#include <string>
#include <type_traits>
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

template <typename T> std::vector<T> ReadVector(const int n) {
  std::vector<T> values;
  values.reserve(n);
  for (int i = 0; i < n; i++) {
    values.push_back(Read<T>());
  }
  return values;
}

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

const ll INF = std::numeric_limits<ll>::max() / 4;

struct MaxRangeSumMonoidElement {
    ll max_prefix_sum;
    ll max_suffix_sum;
    ll max_sum;
    ll total;
};

struct MaxRangeSumMonoid {
  using type = MaxRangeSumMonoidElement;

  type Identity() const {
    return {.max_prefix_sum = -INF, .max_suffix_sum = -INF, .max_sum = -INF, .total=0};
  }

  type ApplyOperator(const type &left, const type &right) const {
    return {.max_prefix_sum = std::max(left.max_prefix_sum, left.total + right.max_prefix_sum),
            .max_suffix_sum = std::max(right.max_suffix_sum, left.max_suffix_sum + right.total),
            .max_sum = std::max(std::max(left.max_sum, right.max_sum), left.max_suffix_sum + right.max_prefix_sum),
            .total = left.total + right.total};
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  const auto n = Read<int>();
  const auto x = ReadVector<ll>(n);

  std::vector<int> starts;
  std::vector<ll> v;
  for (int i = 0; i < n; i += 2) {
      starts.push_back(v.size());
      v.push_back(x[i]);
  }
  if (n % 2 == 0) {
     for (int i = 0; i < n; i += 2) {
          v.push_back(x[i]);
     }
  }
  for (int i = 1; i < n; i += 2) {
      starts.push_back(v.size());
      v.push_back(x[i]);
  }
  if (n % 2) {
      for (int i = 0; i < n; i += 2) {
          v.push_back(x[i]);
      }
  } else {
    for (int i = 1; i < n; i += 2) {
          v.push_back(x[i]);
      }

  }


  const int m = v.size();
  SegTree<MaxRangeSumMonoid> st(m);
  for (int i = 0; i < m; i++) {
    st.Update(i, {.max_prefix_sum = v[i], .max_suffix_sum = v[i], .max_sum = v[i], .total = v[i]});
  }
  
  ll sol = -INF;
  for (const int i : starts) {
      const int j = i + n / 2;
      sol = std::max(sol, st.Query(i, j).max_sum);
  }
  

  
  std::cout << sol << std::endl;
}

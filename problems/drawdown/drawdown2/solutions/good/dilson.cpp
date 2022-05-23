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

template <typename T> T GCD(T a, T b) { return b == 0 ? a : GCD(b, a % b); }

// Assumption: den > 0.
template <typename T> struct Rational {
  T num;
  T den;

  Rational(T num, T den) : num(num), den(den) { Normalize(); };

  void Normalize() {
    const T gcd = GCD(num, den);
    num /= gcd;
    den /= gcd;
  }

  bool operator<(const Rational &other) const {
    return num * other.den < other.num * den;
  }
};

struct DrawdownMonoidElement {
  int min_price;
  int max_price;
  Rational<long long> t; // max{p[j]/p[i] : i <= j}. User for relative drawdown.
  int max_drawdown;
};

struct DrawdownMonoid {
  using type = DrawdownMonoidElement;

  type Identity() const {
    return {.min_price = std::numeric_limits<int>::max(),
            .max_price =
                1, // Prices are positive and having a negative value as t's
                   // denominator would make this not work as an identity.
            .t = Rational<long long>(std::numeric_limits<int>::max(), 1),
            .max_drawdown = 0};
  }

  type ApplyOperator(const type &left, const type &right) const {
    type result = Identity();
    result.min_price = std::min(left.min_price, right.min_price);
    result.max_price = std::max(left.max_price, right.max_price);

    result.t = Rational<long long>(right.min_price, left.max_price);
    if (left.t < result.t) {
      result.t = left.t;
    }
    if (right.t < result.t) {
      result.t = right.t;
    }

    result.max_drawdown = left.max_price - right.min_price;
    if (left.max_drawdown > result.max_drawdown) {
      result.max_drawdown = left.max_drawdown;
    }
    if (right.max_drawdown > result.max_drawdown) {
      result.max_drawdown = right.max_drawdown;
    }

    return result;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  const auto n = Read<int>();
  const auto p = ReadVector<int>(n);

  SegTree<DrawdownMonoid> st(n);
  for (int i = 0; i < n; i++) {
    st.Update(i, {.min_price = p[i],
                  .max_price = p[i],
                  .t = Rational<long long>(1, 1),
                  .max_drawdown = 0});
  }

  const auto q = Read<int>();
  for (int i = 0; i < q; i++) {
    const auto a = Read<int>() - 1;
    const auto b = Read<int>();

    const DrawdownMonoidElement res = st.Query(a, b);
    const Rational<long long> max_rel_drawdown(res.t.den - res.t.num,
                                               res.t.den);
    std::cout << res.max_drawdown << ' ' << max_rel_drawdown.num << ' '
              << max_rel_drawdown.den << '\n';
  }
}

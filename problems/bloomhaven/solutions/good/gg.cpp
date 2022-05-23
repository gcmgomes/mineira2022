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

struct Node {
  Node(long long sum_, long long prefix_sum_, long long suffix_sum_,
       long long maxsum_)
      : sum(sum_),
        prefix_sum(prefix_sum_),
        suffix_sum(suffix_sum_),
        maxsum(maxsum_) {}

  Node() : Node(MINF, MINF, MINF, MINF) {}

  string ToStr() {
    stringstream s;
    s << "node(" << sum << ", " << prefix_sum << ", " << suffix_sum << ", "
      << maxsum << ")";
    return s.str();
  }

  long long sum;
  long long prefix_sum;
  long long suffix_sum;
  long long maxsum;
};

struct Segtree {
  Segtree(const vector<int>& edges) {
    nodes.resize(edges.size() * 4);
    Fill(edges, 0, 0, edges.size() - 1);
  }

  Node Combine(const Node& left, const Node& right) {
    Node current;
    current.sum = left.sum + right.sum;
    current.prefix_sum = max(left.prefix_sum, left.sum + right.prefix_sum);
    current.suffix_sum = max(right.suffix_sum, right.sum + left.suffix_sum);
    current.maxsum =
        max(current.prefix_sum,
            max(current.suffix_sum,
                max(left.maxsum,
                    max(right.maxsum, left.suffix_sum + right.prefix_sum))));
    return current;
  }

  Node Fill(const vector<int>& edges, int root, int l, int r) {
    if (l == r) {
      return nodes[root] =
                 Node(edges.at(l), edges.at(l), edges.at(l), edges.at(l));
    }
    Node left = Fill(edges, 2 * root + 1, l, floor(((double)l + r) / 2.0));
    Node right = Fill(edges, 2 * root + 2, 1 + floor(((double)l + r) / 2.0), r);
    return nodes[root] = Combine(left, right);
  }

  // Return subvector of maximum sum in [l, r]. node_l is the left bound that
  // root represents, node_r the right bound.
  Node Query(int root, int l, int r, int node_l, int node_r) {
    // static string spaces = "";
    // spaces += "|  ";
    // cerr << spaces << "Node id: " << root << ". Node range: [" << node_l <<
    // ", "
    //     << node_r << "]. Querying for [" << l << ", " << r << "]" << endl;
    if (l <= node_l && node_r <= r) {
      // spaces.pop_back();
      // spaces.pop_back();
      // spaces.pop_back();
      return nodes[root];
    }
    int mid = floor(((double)node_l + node_r) / 2.0);
    // everything is in the right subtree.
    Node ret;
    if (mid + 1 <= l) {
      // cerr << spaces << "Going full-right..." << endl;
      ret = Query(2 * root + 2, l, r, 1 + mid, node_r);
      // cerr << spaces << "After going full-right I got " << ret.ToStr() <<
      // endl;
    } else if (r <= mid) {
      // cerr << spaces << "Going full-left..." << endl;
      ret = Query(2 * root + 1, l, r, node_l, mid);
      // cerr << spaces << "After going full-left I got " << ret.ToStr() <<
      // endl;
    } else {
      // cerr << spaces << "Going left..." << endl;
      Node left = Query(2 * root + 1, l, r, node_l, mid);
      // cerr << spaces << "After going left I got " << left.ToStr() << endl;

      // cerr << spaces << "Going right..." << endl;
      Node right = Query(2 * root + 2, l, r, 1 + mid, node_r);
      // cerr << spaces << "After going right I got " << right.ToStr() << endl;

      ret = Combine(left, right);
      // cerr << spaces << "Combination gave me " << ret.ToStr() << endl;
    }
    // spaces.pop_back();
    // spaces.pop_back();
    // spaces.pop_back();
    return ret;
  }

  vector<Node> nodes;
};

long long Solve(const vector<int>& edges, int size) {
  long long best = MINF;
  Segtree tree(edges);
  for (int i = 0; i + size < edges.size(); i++) {
    // cerr << "Querying vector";
    // for (auto& e : edges) {
    //   cerr << " " << e;
    // }
    // cerr << endl;
    best =
        max(best, tree.Query(0, i, i + size - 1, 0, edges.size() - 1).maxsum);
    // cerr << "new best is " << best << endl;
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

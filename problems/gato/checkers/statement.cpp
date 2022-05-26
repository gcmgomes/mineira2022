#include <unordered_set>
#include <cassert>
#include "testlib.h"

using namespace std;

unordered_set<int> Sieve() {
  vector<int> nums(1000001, 1);
  unordered_set<int> primes;
  nums[0] = nums[1] = 0;
  int i = 2;
  while (i < nums.size()) {
    if (!nums[i]) {
      i++;
      continue;
    }
    primes.insert(i);
    for (int j = i + i; j < nums.size(); j += i) {
      nums[j] = 0;
    }
    i++;
  }
  return primes;
}

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);

  string n;
  while (inf.curChar() != ' ') {
    n += inf.readChar();
  }
  assert(n.size() <= 1000);
  inf.readSpace();
  int k = inf.readInt(1, 50);
  inf.readEoln();
  vector<int> primes = inf.readInts(k, 2, 1000000);
  auto prime_set = Sieve();
  for (auto& p : primes) {
    assert(prime_set.count(p));
  }
  inf.readEoln();
  inf.readEof();
}

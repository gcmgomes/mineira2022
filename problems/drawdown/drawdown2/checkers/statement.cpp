#include "testlib.h"

int main(int argc, char *argv[]) {
  registerValidation(argc, argv);

  // Limits for the number of values.
  constexpr int MIN_NUM_VALUES = 1;
  constexpr int MAX_NUM_VALUES = 500'000;

  // Limits for the values.
  constexpr int MIN_VALUE = 1;
  constexpr int MAX_VALUE = 1'000'000'000;

  // Limits for the number of queries.
  constexpr int MIN_NUM_QUERIES = 1;
  constexpr int MAX_NUM_QUERIES = 500'000;

  // Checks the values.
  const int num_values = inf.readInt(MIN_NUM_VALUES, MAX_NUM_VALUES);
  inf.readEoln();
  for (int i = 0; i < num_values; i++) {
    if (i != 0) {
      inf.readSpace();
    }

    const int value = inf.readInt(MIN_VALUE, MAX_VALUE);
  }
  inf.readEoln();

  // Checks the queries;
  const int num_queries = inf.readInt(MIN_NUM_QUERIES, MAX_NUM_QUERIES);
  inf.readEoln();
  for (int i = 0; i < num_queries; i++) {
    const int start_index = inf.readInt(1, num_values);
    inf.readSpace();
    const int end_index = inf.readInt(start_index, num_values);
    inf.readEoln();
  }

  inf.readEof();
}

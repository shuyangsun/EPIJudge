#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int SearchFirstOfK(const vector<int>& A, int k) {
  if (A.size() <= 0) {
    return -1;
  }
  if (A[0] == k) {
    return 0;
  }
  int lhs{0}, rhs{static_cast<int>(A.size() - 1)};
  while (rhs - lhs > 1) {
    int mid{lhs + (rhs - lhs) / 2};
    auto const mid_val{A[mid]};
    if (mid_val >= k) {
      rhs = mid;
    } else {
      lhs = mid;
    }
  }
  return A[rhs] == k ? rhs : -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "search_first_key.cc", "search_first_key.tsv",
                         &SearchFirstOfK, DefaultComparator{}, param_names);
}

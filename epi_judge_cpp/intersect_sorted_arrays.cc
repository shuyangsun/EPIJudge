#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

vector<int> IntersectTwoSortedArrays(const vector<int>& A,
                                     const vector<int>& B) {
  vector<int> res{};
  auto a{A.begin()};
  auto b{B.begin()};
  while (a < A.end() && b < B.end()) {
    if (*a == *b) {
      if (res.empty() || *a != res.back()) {
        res.emplace_back(*a);
      }
      ++a;
      ++b;
    } else if (*a < *b) {
      ++a;
    } else {
      ++b;
    }
  }
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(
      args, "intersect_sorted_arrays.cc", "intersect_sorted_arrays.tsv",
      &IntersectTwoSortedArrays, DefaultComparator{}, param_names);
}

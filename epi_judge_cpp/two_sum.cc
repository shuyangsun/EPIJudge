#include <unordered_set>
#include <vector>

#include "test_framework/generic_test.h"
using std::unordered_set;
using std::vector;

bool HasTwoSum(const vector<int>& A, int t) {
  unordered_set<int> cache{};
  for (auto const& ele : A) {
    if (cache.find(t - ele) != cache.end() || t % 2 == 0 && t / 2 == ele) {
      return true;
    }
    cache.insert(ele);
  }
  return false;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "t"};
  return GenericTestMain(args, "two_sum.cc", "two_sum.tsv", &HasTwoSum,
                         DefaultComparator{}, param_names);
}

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

bool HasThreeSum(vector<int> A, int t) {
  unordered_set<int> not_found{};
  for (auto const& ele : A) {
    const int target{t - ele};
    if (not_found.find(target) != not_found.end()) {
      continue;
    }
    const bool cur_res{HasTwoSum(A, target)};
    if (cur_res) {
      return true;
    }
    not_found.insert(target);
  }
  return false;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "t"};
  return GenericTestMain(args, "three_sum.cc", "three_sum.tsv", &HasThreeSum,
                         DefaultComparator{}, param_names);
}

#include <functional>
#include <numeric>
#include <queue>
#include <vector>

#include "test_framework/generic_test.h"

using std::priority_queue;
using std::vector;

vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {
  priority_queue<int, vector<int>, std::greater<int>> queue{};
  for (auto const& vec : sorted_arrays) {
    for (auto const& ele : vec) {
      queue.emplace(ele);
    }
  }

  size_t total_size{std::accumulate(
      sorted_arrays.begin(), sorted_arrays.end(), static_cast<size_t>(0),
      [](size_t accum, vector<int> const& vec) { return accum + vec.size(); })};
  vector<int> res{};
  res.reserve(total_size);
  while (!queue.empty()) {
    res.emplace_back(queue.top());
    queue.pop();
  }
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sorted_arrays"};
  return GenericTestMain(args, "sorted_arrays_merge.cc",
                         "sorted_arrays_merge.tsv", &MergeSortedArrays,
                         DefaultComparator{}, param_names);
}

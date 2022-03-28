#include <array>
#include <stack>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::array;
using std::stack;
using std::vector;
const int kNumPegs = 3;

vector<vector<int>> TowerHanio(int num_rings, int from_peg, int to_peg) {
  if (num_rings <= 0) {
    return {};
  }
  if (num_rings == 1) {
    return {{from_peg, to_peg}};
  }
  int idle_peg = 0;
  if (from_peg != 1 && to_peg != 1) {
    idle_peg = 1;
  }
  if (from_peg != 2 && to_peg != 2) {
    idle_peg = 2;
  }
  auto result{TowerHanio(num_rings - 1, from_peg, idle_peg)};
  result.push_back({from_peg, to_peg});
  auto second_step{TowerHanio(num_rings - 1, idle_peg, to_peg)};
  result.insert(result.end(), second_step.begin(), second_step.end());
  return result;
}

vector<vector<int>> ComputeTowerHanoi(int num_rings) {
  return TowerHanio(num_rings, 0, 1);
}

void ComputeTowerHanoiWrapper(TimedExecutor& executor, int num_rings) {
  array<stack<int>, kNumPegs> pegs;
  for (int i = num_rings; i >= 1; --i) {
    pegs[0].push(i);
  }

  vector<vector<int>> result =
      executor.Run([&] { return ComputeTowerHanoi(num_rings); });

  for (const vector<int>& operation : result) {
    int from_peg = operation[0], to_peg = operation[1];
    if (!pegs[to_peg].empty() && pegs[from_peg].top() >= pegs[to_peg].top()) {
      throw TestFailure("Illegal move from " +
                        std::to_string(pegs[from_peg].top()) + " to " +
                        std::to_string(pegs[to_peg].top()));
    }
    pegs[to_peg].push(pegs[from_peg].top());
    pegs[from_peg].pop();
  }
  array<stack<int>, kNumPegs> expected_pegs1, expected_pegs2;
  for (int i = num_rings; i >= 1; --i) {
    expected_pegs1[1].push(i);
  }
  for (int i = num_rings; i >= 1; --i) {
    expected_pegs2[2].push(i);
  }
  if (pegs != expected_pegs1 && pegs != expected_pegs2) {
    throw TestFailure("Pegs doesn't place in the right configuration");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "num_rings"};
  return GenericTestMain(args, "hanoi.cc", "hanoi.tsv",
                         &ComputeTowerHanoiWrapper, DefaultComparator{},
                         param_names);
}

#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int NumCombinationsForFinalScore(int final_score,
                                 const vector<int>& individual_play_scores) {
  vector<unsigned int> dp(final_score + 1, 0);
  dp[0] = 1;
  for (auto const score : individual_play_scores) {
    for (int i{1}; i <= final_score; ++i) {
      const int delta{i - score};
      if (delta == 0) {
        ++dp[i];
      } else if (delta > 0 && dp[delta] > 0) {
        dp[i] += dp[delta];
      }
    }
  }
  return dp.back();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"final_score", "individual_play_scores"};
  return GenericTestMain(args, "number_of_score_combinations.cc",
                         "number_of_score_combinations.tsv",
                         &NumCombinationsForFinalScore, DefaultComparator{},
                         param_names);
}

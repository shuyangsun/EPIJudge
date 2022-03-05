#include <vector>
#include <limits>

#include "test_framework/generic_test.h"
using std::vector;
using namespace std;

double BuyAndSellStockOnce(const vector<double>& prices) {
  auto cur_min{numeric_limits<double>::infinity()},
       cur_max{numeric_limits<double>::min()},
       res{cur_max};
  for (const double cur: prices) {
      if (cur_min > cur) {
        if (cur_max >= 0) {
          res = max(cur_max - cur_min, res);
        }

        cur_min = cur;
        cur_max = cur;
      }
      if (cur_max < cur) {
          cur_max = cur;
      }
  }
  res = max(cur_max - cur_min, res);
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}

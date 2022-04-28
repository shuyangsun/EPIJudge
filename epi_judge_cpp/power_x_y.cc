#include <cmath>

#include "test_framework/generic_test.h"
using namespace std;

double Power(const double x, const int y) {
  if (y == 0) return 1;
  if (y == 1) return x;

  bool is_fraction{y < 0};
  int pos_y{abs(y)};

  int cur_pow{1};
  double cur{x};
  while (cur_pow * 2 <= y) {
    cur *= cur;
    cur_pow *= 2;
    if (cur_pow == y) {
      return is_fraction ? 1.0 / cur : cur;
    }
  }

  double res{cur * Power(x, y - cur_pow)};
  return is_fraction ? 1 / res : res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "power_x_y.cc", "power_x_y.tsv", &Power,
                         DefaultComparator{}, param_names);
}

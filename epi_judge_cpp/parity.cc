#include "test_framework/generic_test.h"
short Parity(unsigned long long x) {
  bool is_odd{false};
  while (x) {
    if (x & 1) {
      is_odd = !is_odd;
    }
    x = x >> 1;
  }
  return is_odd ? 1 : 0;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "parity.cc", "parity.tsv", &Parity,
                         DefaultComparator{}, param_names);
}

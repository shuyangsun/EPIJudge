#include <cmath>
#include <cstdint>
#include <limits>
#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"

using namespace std;

string IntToString(int x) {
  if (x == 0) {
    return "0";
  }
  bool is_negative{x < 0};
  string res{};
  const int zero{static_cast<int>('0')};
  while (x != 0) {
    const int num{is_negative ? -(x % 10) : (x % 10)};
    res.push_back(static_cast<char>(zero + num));
    x /= 10;
  }
  if (is_negative) {
    res.push_back('-');
  }
  reverse(res.begin(), res.end());
  return res;
}

int StringToInt(const string& s) {
  const int zero_char_int{static_cast<int>('0')};
  const int low{numeric_limits<int>::min()}, high{numeric_limits<int>::max()};

  int sign{1};
  int res{0};
  bool is_in{false};
  int sign_i{-1};

  for (auto i{s.begin()}; i < s.end(); ++i) {
    const char ch{*i};
    if (!is_in && ch == ' ') {
      continue;
    }
    if (sign_i < 0 && (ch == '-' || ch == '+')) {
      sign_i = i - s.begin();
    }
    const int int_val{static_cast<int>(ch) - zero_char_int};
    const bool is_digit{int_val >= 0 && int_val < 10};
    if (!is_in && !is_digit && !(ch == ' ' || ch == '+' || ch == '-')) {
      return 0;
    }
    if (!is_in && is_digit) {
      is_in = true;
      if ((sign_i >= 0) && (i - (s.begin() + sign_i) > 1)) {
        return 0;
      }
      const char prev_ch = *(i - 1);
      if (i > s.begin() && prev_ch == '-') {
        sign = -1;
      }
    }
    if (is_in) {
      if (!is_digit) {
        return res;
      }
      if (sign < 0 && (low + int_val) / 10 > res) {
        return low;
      }
      if (sign > 0 && (high - int_val) / 10 < res) {
        return high;
      }
      res = res * 10 + int_val * sign;
    }
  }
  return res;
}
void Wrapper(int x, const string& s) {
  if (stoi(IntToString(x)) != x) {
    throw TestFailure("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailure("String to int conversion failed");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "s"};
  return GenericTestMain(args, "string_integer_interconversion.cc",
                         "string_integer_interconversion.tsv", &Wrapper,
                         DefaultComparator{}, param_names);
}

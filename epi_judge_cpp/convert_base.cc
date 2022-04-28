#include <cctype>
#include <string>

#include "test_framework/generic_test.h"

using namespace std;

constexpr int ord_0{static_cast<int>('0')};
constexpr int ord_a{static_cast<int>('A')};

unsigned short CharToNum(const char& ch) {
  return static_cast<int>(ch) - (isdigit(ch) ? ord_0 : ord_a - 10);
}

char NumToChar(const unsigned short& num) {
  if (num < 10) {
    return static_cast<char>(ord_0 + num);
  } else {
    return static_cast<char>(ord_a + num - 10);
  }
}

void reverse(string& str) {
  for (size_t i{0}; i < str.size() / 2; ++i) {
    size_t j{str.size() - i - 1};
    swap(str[i], str[j]);
  }
}

string ConvertBase(const string& num_as_string, int b1, int b2) {
  if (b1 == b2) {
    return num_as_string;
  }
  if (num_as_string == "0") {
    return 0;
  }
  unsigned int res{0};
  unsigned int cur_base{1};
  bool is_neg{num_as_string[0] == '-'};
  int offset{is_neg ? 1 : 0};
  for (auto ch{num_as_string.rbegin()}; ch < num_as_string.rend() - offset;
       ++ch) {
    res += CharToNum(toupper(*ch)) * cur_base;
    cur_base *= b1;
  }

  string res_str{""};
  while (res > 0) {
    const char cur{NumToChar(res % b2)};
    res_str.push_back(cur);
    res /= b2;
  }
  if (is_neg) {
    res_str.push_back('-');
  }
  reverse(res_str);
  return res_str;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}

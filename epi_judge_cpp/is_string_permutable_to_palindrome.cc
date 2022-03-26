#include <string>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;
using std::unordered_map;

bool CanFormPalindrome(const string& s) {
  unordered_map<char, bool> occurance{};
  for (auto const ch : s) {
    if (occurance.find(ch) == occurance.end()) {
      occurance.insert({ch, true});
    } else {
      occurance[ch] = !occurance[ch];
    }
  }
  bool did_find_single{false};
  for (auto const& key_val : occurance) {
    if (key_val.second) {
      if (did_find_single) {
        return false;
      }
      did_find_single = true;
    }
  }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_permutable_to_palindrome.cc",
                         "is_string_permutable_to_palindrome.tsv",
                         &CanFormPalindrome, DefaultComparator{}, param_names);
}

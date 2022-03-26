#include <string>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;
using std::unordered_map;

unordered_map<char, unsigned int> GetLetterOccurrence(const string& str) {
  unordered_map<char, unsigned int> result{};
  for (auto const& ch : str) {
    if (result.find(ch) == result.end()) {
      result[ch] = 1;
    } else {
      ++result[ch];
    }
  }
  return result;
}

bool IsLetterConstructibleFromMagazine(const string& letter_text,
                                       const string& magazine_text) {
  auto letter_occur{GetLetterOccurrence(letter_text)};
  auto mag_occur{GetLetterOccurrence(magazine_text)};
  for (auto const& ch_occur : letter_occur) {
    char ch{ch_occur.first};
    const unsigned int occur{ch_occur.second};
    const bool no_occur{mag_occur.find(ch) == mag_occur.end()};
    const bool less_occur{!no_occur && mag_occur[ch] < occur};
    if (no_occur || less_occur) {
      return false;
    }
  }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"letter_text", "magazine_text"};
  return GenericTestMain(args, "is_anonymous_letter_constructible.cc",
                         "is_anonymous_letter_constructible.tsv",
                         &IsLetterConstructibleFromMagazine,
                         DefaultComparator{}, param_names);
}

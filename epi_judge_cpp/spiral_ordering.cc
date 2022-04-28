#include <iostream>

#include "test_framework/generic_test.h"

using namespace std;

vector<int> MatrixInSpiralOrder(const vector<vector<int>>& square_matrix) {
  const auto& m{square_matrix};
  size_t n{m.size()};
  if (n == 0) return vector<int>{};
  vector<int> res{};
  res.reserve(n * n);
  if (n == 1) {
    res.push_back(m[0][0]);
    return res;
  }

  size_t top{0}, left{0}, bot{n}, right{n};
  unsigned int dir{0};
  size_t count{0};

  while (count < n * n) {
    switch (dir) {
      case 0:  // Right
        res.insert(res.end(), m[top].begin() + left, m[top].begin() + right);
        count += right - left;
        ++top;
        break;
      case 1:  // Down
        for (size_t row{top}; row < bot; ++row) {
          res.push_back(m[row][right - 1]);
        }
        count += bot - top;
        --right;
        break;
      case 2:  // Left
        res.insert(res.end(), m[bot - 1].rbegin() + (n - right),
                   m[bot - 1].rend() - left);
        count += right - left;
        --bot;
        break;
      case 3:  // Up
        for (size_t row{bot - 1}; row >= top; --row) {
          res.push_back(m[row][left]);
        }
        count += bot - top;
        ++left;
        break;
    }
    dir = (dir + 1) % 4;
  }
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "spiral_ordering.cc", "spiral_ordering.tsv",
                         &MatrixInSpiralOrder, DefaultComparator{},
                         param_names);
}

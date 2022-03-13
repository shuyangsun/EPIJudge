#include <algorithm>
#include <cmath>
#include <stack>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

int GetHeight(const unique_ptr<BinaryTreeNode<int>>& tree) {
  if (!tree) {
    return -1;
  }
  auto const left_height{GetHeight(tree->left)};
  auto const right_height{GetHeight(tree->right)};
  if (std::abs(left_height - right_height) > 1 || left_height == -2 ||
      right_height == -2) {
    return -2;
  }
  return std::max(left_height, right_height) + 1;
}

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
  return GetHeight(tree) > -2;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
                         &IsBalanced, DefaultComparator{}, param_names);
}

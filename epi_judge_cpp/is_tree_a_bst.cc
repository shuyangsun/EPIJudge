#include <memory>
#include <utility>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

using std::unique_ptr;

std::tuple<bool, int, int> MinAndMax(
    const unique_ptr<BinaryTreeNode<int>>& tree) {
  auto res{std::make_tuple(true, tree->data, tree->data)};
  if (tree->left) {
    const auto cur{MinAndMax(tree->left)};
    if (!std::get<0>(cur) || std::get<2>(cur) > tree->data) {
      return std::make_tuple(false, 0, 0);
    }
    std::get<1>(res) = std::get<1>(cur);
  }
  if (tree->right) {
    const auto cur{MinAndMax(tree->right)};
    if (!std::get<0>(cur) || std::get<1>(cur) < tree->data) {
      return std::make_tuple(false, 0, 0);
    }
    std::get<2>(res) = std::get<2>(cur);
  }
  return res;
}

bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>>& tree) {
  if (!tree) {
    return true;
  }
  return std::get<0>(MinAndMax(tree));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_a_bst.cc", "is_tree_a_bst.tsv",
                         &IsBinaryTreeBST, DefaultComparator{}, param_names);
}

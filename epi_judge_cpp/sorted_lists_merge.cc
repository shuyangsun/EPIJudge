#include "list_node.h"
#include "test_framework/generic_test.h"
shared_ptr<ListNode<int>> MergeTwoSortedLists(shared_ptr<ListNode<int>> L1,
                                              shared_ptr<ListNode<int>> L2) {
  if (!L1) {
    return L2;
  }
  if (!L2) {
    return L1;
  }
  auto res{L1->data < L2->data ? L1 : L2};
  auto n1{res};
  shared_ptr<ListNode<int>> n1_last{};
  auto n2{L1->data < L2->data ? L2 : L1};
  while (n1 && n2) {
    if (n1->data <= n2->data && n2->data <= n1->next->data) {
      auto const tmp{n1->next};
      n1->next = n2;
      n2 = n2->next;
      n1->next->next = tmp;
    }
    n1 = n1->next;
    n1_last = n1;
  }

  if (!n1 && n2 && n1_last) {
    n1_last->next = n2;
  }

  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L1", "L2"};
  return GenericTestMain(args, "sorted_lists_merge.cc",
                         "sorted_lists_merge.tsv", &MergeTwoSortedLists,
                         DefaultComparator{}, param_names);
}

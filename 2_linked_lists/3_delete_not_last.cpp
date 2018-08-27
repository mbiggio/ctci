#include <iostream>
#include <cassert>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "linked_list.h"
using namespace std;

/*
 * Removes a node in a linked list
 * which is not the head nor the tail,
 * given a pointer to that node.
 */
void remove_middle(Node *n) {
  assert(n);
  assert(n->next);
  swap(n->val, n->next->val);
  Node *to_delete = n->next;
  n->next = n->next->next;
  delete to_delete;
}

TEST(remove_middle_test,nominal) {
  const vector<int> v_in = {4,5,1};
  Node *head = nullptr;
  for (auto i : v_in) head = add_to_tail(head,i);
  
  remove_middle(head->next);
  EXPECT_EQ(4, head->val);
  EXPECT_EQ(1, head->next->val);
  EXPECT_EQ(nullptr, head->next->next);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

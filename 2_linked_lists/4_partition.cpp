#include <iostream>
#include "linked_list.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace std;

Node *partition(Node *head, int x) {
  if (!head) return nullptr;
  Node *cur = head;
  while (cur->next) {
    if (cur->next->val < x) {
      Node *n = cur->next;
      cur->next = cur->next->next;
      n->next = head;
      head = n;
    }
    else {
      cur = cur->next;
    }
  }
  return head;
}

TEST(partition_test,all_left) {
  const vector<int> v_in = {4,5,1};
  Node *head = nullptr;
  for (auto i : v_in) head = add_to_tail(head,i);

  head = partition(head,10);
  EXPECT_EQ(1,head->val);
  EXPECT_EQ(5,head->next->val);
  EXPECT_EQ(4,head->next->next->val);
  EXPECT_EQ(nullptr,head->next->next->next);
}

TEST(partition_test,all_right) {
  const vector<int> v_in = {4,5,1};
  Node *head = nullptr;
  for (auto i : v_in) head = add_to_tail(head,i);

  head = partition(head,0);
  EXPECT_EQ(4,head->val);
  EXPECT_EQ(5,head->next->val);
  EXPECT_EQ(1,head->next->next->val);
  EXPECT_EQ(nullptr,head->next->next->next);
}

TEST(partition_test,mixed) {
  const vector<int> v_in = {4,5,7,8};
  Node *head = nullptr;
  for (auto i : v_in) head = add_to_tail(head,i);

  head = partition(head,6);
  EXPECT_EQ(5,head->val);
  EXPECT_EQ(4,head->next->val);
  EXPECT_EQ(7,head->next->next->val);
  EXPECT_EQ(8,head->next->next->next->val);
  EXPECT_EQ(nullptr,head->next->next->next->next);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

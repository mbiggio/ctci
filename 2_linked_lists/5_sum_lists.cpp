#include <iostream>
#include "linked_list.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace std;

Node *sum_lists(Node *l1, Node *l2, int carry=0) {
  if (!l1 && !l2 && carry==0) return nullptr;
  int val = carry;
  if (l1) val += l1->val;
  if (l2) val += l2->val;
  Node *cur = new Node(val%10);
  Node *next = sum_lists(l1?l1->next:l1, l2?l2->next:l2, val/10);
  cur->next = next;
  return cur;
}

TEST(sum_lists_test,nominal) {
  const vector<int> v1 = {7,1,6};
  Node *l1 = nullptr;
  for (auto i : v1) l1 = add_to_tail(l1,i);

  const vector<int> v2 = {5,9,2};
  Node *l2 = nullptr;
  for (auto i : v2) l2 = add_to_tail(l2,i);

  Node *s = sum_lists(l1,l2);
  EXPECT_EQ(2,s->val);
  EXPECT_EQ(1,s->next->val);
  EXPECT_EQ(9,s->next->next->val);
  EXPECT_EQ(nullptr,s->next->next->next);
}

TEST(sum_lists_test,carry) {
  const vector<int> v1 = {7,1,6};
  Node *l1 = nullptr;
  for (auto i : v1) l1 = add_to_tail(l1,i);

  const vector<int> v2 = {5,9,4};
  Node *l2 = nullptr;
  for (auto i : v2) l2 = add_to_tail(l2,i);

  Node *s = sum_lists(l1,l2);
  EXPECT_EQ(2,s->val);
  EXPECT_EQ(1,s->next->val);
  EXPECT_EQ(1,s->next->next->val);
  EXPECT_EQ(1,s->next->next->next->val);
  EXPECT_EQ(nullptr,s->next->next->next->next);
}

TEST(sum_lists_test,not_same_length) {
  const vector<int> v1 = {7,1,6};
  Node *l1 = nullptr;
  for (auto i : v1) l1 = add_to_tail(l1,i);

  const vector<int> v2 = {5,9};
  Node *l2 = nullptr;
  for (auto i : v2) l2 = add_to_tail(l2,i);

  Node *s = sum_lists(l1,l2);
  EXPECT_EQ(2,s->val);
  EXPECT_EQ(1,s->next->val);
  EXPECT_EQ(7,s->next->next->val);
  EXPECT_EQ(nullptr,s->next->next->next);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

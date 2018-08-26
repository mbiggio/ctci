#include <iostream>
#include "linked_list.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace std;

Node *kth_to_last(Node *head, int k) {
  // set up two pointers 
  // separated by k-1 hops.
  if (k<=0 || !head) return nullptr;
  Node *first = head, *second = head;
  int dist = 1;
  while (dist < k && second->next != nullptr) {
    second = second->next;
    ++dist;
  }
  if (dist < k) return nullptr;

  // scan list until second->next != nullptr.
  // The kth-to-last element is pointed by first.
  while (second->next) {
    second = second->next;
    first = first->next;
  }
  return first;
}

TEST(kth_to_last_test,nominal) {
  const vector<int> v_in = {4,5,1};
  Node *head = nullptr;
  for (auto i : v_in) head = add_to_tail(head,i);

  {
    Node *res = kth_to_last(head,1);
    EXPECT_NE(nullptr, res);
    EXPECT_EQ(1,res->val);
  }
  {
    Node *res = kth_to_last(head,2);
    EXPECT_NE(nullptr, res);
    EXPECT_EQ(5,res->val);
  }
  {
    Node *res = kth_to_last(head,3);
    EXPECT_NE(nullptr, res);
    EXPECT_EQ(4,res->val);
  }
}

TEST(kth_to_last_test,null) {
  Node *head = nullptr;
  {
    Node *res = kth_to_last(head,1);
    EXPECT_EQ(nullptr, res);
  }
  {
    Node *res = kth_to_last(head,2);
    EXPECT_EQ(nullptr, res);
  }
}

TEST(kth_to_last_test,out_of_bounds) {
  const vector<int> v_in = {4,5,1};
  Node *head = nullptr;
  for (auto i : v_in) head = add_to_tail(head,i);
  {
    Node *res = kth_to_last(head,0);
    EXPECT_EQ(nullptr, res);
  }
  {
    Node *res = kth_to_last(head,-1);
    EXPECT_EQ(nullptr, res);
  }
  {
    Node *res = kth_to_last(head,4);
    EXPECT_EQ(nullptr, res);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
  

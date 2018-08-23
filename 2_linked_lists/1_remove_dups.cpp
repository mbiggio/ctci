#include <iostream>
#include <unordered_set>
#include "linked_list.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace std;

/*
 * Remove duplicates from an unsorted linked list.
 */

Node *remove_dups(Node *head) {
  if (!head) return head;
  unordered_set<int> visited;
  visited.insert(head->val);

  Node *prev = head;
  Node *cur = head->next;
  while (cur) {
    auto it = visited.find(cur->val);
    if (it == visited.end()) {
      visited.insert(cur->val);
      prev = cur;
      cur = cur->next;
    }
    else {
      prev->next = cur->next;
      cur = cur->next;
    }
  }
  return head;
}

TEST(remove_dups_test,nominal) {
  const vector<int> v_in = {1,2,3,1,2,3,4,5,1};
  const vector<int> v_out = {1,2,3,4,5};
  Node *head = nullptr;
  for (auto i : v_in) head = add_to_tail(head,i);
  EXPECT_NE(nullptr, remove_dups(head));

  int i = 0;
  while (i<v_out.size() && head) {
    EXPECT_EQ(v_out[i],head->val);
    ++i;
    head = head->next;
  }

  EXPECT_EQ(v_out.size(), i);
  EXPECT_EQ(nullptr, head);
  
}

int main(int argc, char** argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

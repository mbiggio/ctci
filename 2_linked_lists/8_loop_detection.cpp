#include <iostream>
#include <stack>
#include "linked_list.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace std;

/**
 * Finds whether or not a singly-linked list 
 * has a cycle, and if yes returns the first 
 * node of the cycle startting from the head
 * of the list.
 * Time complexity: O(n)
 * Space complexity: O(1)
 */

Node *loop_detection(Node *head) {
  if (!head) return nullptr;
  Node *slow = head, *fast = head->next;
  while (slow != fast && fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
  }

  if (!fast || !fast->next) return nullptr;

  // We found a cycle, now we need to find
  // the starting node.
  // Find first the cycle length.
  Node *cur = slow->next;
  int length = 1;
  while (cur != slow) {
    ++length;
    cur = cur->next;
  }

  // Initialize a pointer at distance 
  // length from the head
  cur = head;
  while (length) {
    --length;
    cur = cur->next;
  }

  // Increment head and distant pointer
  // until they are equal.
  // Head now points to the first node of the cycle.
  while (head != cur) {
    head = head->next;
    cur = cur->next;
  }

  return head;
}

TEST(loop_detection_test,ko) {
  const vector<int> v = {5,7,7,6};
  Node *l = nullptr;
  for (auto i : v) l = add_to_tail(l,i);
  EXPECT_EQ(nullptr, loop_detection(l));
}

TEST(loop_detection_test,ok) {
  Node *n1 = new Node(1);
  Node *n2 = new Node(2);
  Node *n3 = new Node(3);
  Node *n4 = new Node(4);

  n1->next = n2;
  n2->next = n3;
  n3->next = n4;

  n4->next = n1;
  EXPECT_EQ(n1, loop_detection(n1));
  n4->next = n2;
  EXPECT_EQ(n2, loop_detection(n1));
  n4->next = n3;
  EXPECT_EQ(n3, loop_detection(n1));
  n4->next = n4;
  EXPECT_EQ(n4, loop_detection(n1));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

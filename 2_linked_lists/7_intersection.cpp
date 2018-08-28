#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "linked_list.h"
using namespace std;

int get_length(Node *h) {
  int length = 0;
  while (h) {
    h = h->next;
    ++length;
  }
  return length;
}

/**
 * Determine if two singly-linked lists
 * intersect or not.
 * This approach first calculates the lengths
 * of the two lists, and advances the head
 * of the longer list until lengths are equal.
 * Then, advances the two heads simultaneously
 * until they are either equal or null.
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
Node *intersect(Node *h1, Node *h2) {
  int l1 = get_length(h1);
  int l2 = get_length(h2);

  while (l1 > l2) {
    h1 = h1->next;
    --l1;
  }
  while (l2 > l1) {
    h2 = h2->next;
    --l2;
  }

  while (h1 && h2) {
    if (h1 == h2) return h1;
    h1 = h1->next;
    h2 = h2->next;
  }
  return nullptr;
}

TEST(intersect_test,ko) {
  const vector<int> v1 = {1,2,3};
  Node *h1 = nullptr;
  for (auto i : v1) h1 = add_to_tail(h1,i);
  
  const vector<int> v2 = {1,2,3};
  Node *h2 = nullptr;
  for (auto i : v2) h2 = add_to_tail(h2,i);

  EXPECT_EQ(nullptr, intersect(h1,h2));
}

TEST(intersect_test,ok) {
  const vector<int> v1 = {1,2,3};
  Node *h = nullptr;
  for (auto i : v1) h = add_to_tail(h,i);

  Node *h1 = new Node(10);
  h1->next = h;
  
  Node *h21 = new Node(20);
  Node *h22 = new Node(30);
  h21->next = h22;
  h22->next = h;
  
  EXPECT_EQ(h, intersect(h1,h21));
  EXPECT_EQ(h, intersect(h21,h1));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}


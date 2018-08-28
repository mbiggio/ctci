#include <iostream>
#include <stack>
#include "linked_list.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace std;

/**
 * Test if a singly-linked list is a palyndrome.
 * This approach uses a stack and a pair of 
 * slow/fast pointers to reach the middle
 * of the list without knowing the length.
 * Time complexity: O(n)
 * Space complexity: O(n)
 */

bool is_palindrome(Node *head) {
  if (!head || !head->next) return true;
  stack<int> s;
  Node *slow = head, *fast = head->next;
  s.push(slow->val);
  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
    if (fast) s.push(slow->val);
  }

  slow = slow->next;
  while(!s.empty() && slow) {
    if (s.top() != slow->val) return false;
    s.pop();
    slow = slow->next;
  }
  return true;
}

TEST(is_palindrome,odd_ok) {
  const vector<int> v = {6,7,1,7,6};
  Node *l = nullptr;
  for (auto i : v) l = add_to_tail(l,i);
  EXPECT_TRUE(is_palindrome(l));
}

TEST(is_palindrome,odd_ko_1) {
  const vector<int> v = {6,5,1,7,6};
  Node *l = nullptr;
  for (auto i : v) l = add_to_tail(l,i);
  EXPECT_FALSE(is_palindrome(l));
}

TEST(is_palindrome,odd_ko_2) {
  const vector<int> v = {5,7,1,7,6};
  Node *l = nullptr;
  for (auto i : v) l = add_to_tail(l,i);
  EXPECT_FALSE(is_palindrome(l));
}

TEST(is_palindrome,even_ok) {
  const vector<int> v = {6,7,7,6};
  Node *l = nullptr;
  for (auto i : v) l = add_to_tail(l,i);
  EXPECT_TRUE(is_palindrome(l));
}

TEST(is_palindrome,even_ko_1) {
  const vector<int> v = {6,5,7,6};
  Node *l = nullptr;
  for (auto i : v) l = add_to_tail(l,i);
  EXPECT_FALSE(is_palindrome(l));
}

TEST(is_palindrome,even_ko_2) {
  const vector<int> v = {5,7,7,6};
  Node *l = nullptr;
  for (auto i : v) l = add_to_tail(l,i);
  EXPECT_FALSE(is_palindrome(l));
}

TEST(is_palindrome,empty) {
  Node *l = nullptr;
  EXPECT_TRUE(is_palindrome(l));
}

TEST(is_palindrome,one) {
  const vector<int> v = {5};
  Node *l = nullptr;
  for (auto i : v) l = add_to_tail(l,i);
  EXPECT_TRUE(is_palindrome(l));
}

TEST(is_palindrome,two_ok) {
  const vector<int> v = {5,5};
  Node *l = nullptr;
  for (auto i : v) l = add_to_tail(l,i);
  EXPECT_TRUE(is_palindrome(l));
}

TEST(is_palindrome,two_ko) {
  const vector<int> v = {5,4};
  Node *l = nullptr;
  for (auto i : v) l = add_to_tail(l,i);
  EXPECT_FALSE(is_palindrome(l));
}


int main(int argc, char **argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

#include <iostream>
#include <stack>
#include <stdexcept>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace std;

void sort_stack(stack<int> &s) {
  stack<int> s_sorted;
  while (!s.empty()) {
    int tmp = s.top();
    s.pop();
    int popped = 0;
    while (!s_sorted.empty() && tmp <= s_sorted.top()) {
      s.push(s_sorted.top());
      s_sorted.pop();
      ++popped;
    }
    s_sorted.push(tmp);
    for (int i=0; i<popped; ++i) {
      s_sorted.push(s.top());
      s.pop();
    }
  }

  while (!s_sorted.empty()) {
    s.push(s_sorted.top());
    s_sorted.pop();
  }
}

TEST(sort_stack_test, nominal) {

  stack<int> s;

  // push a few elements
  s.push(80);
  s.push(15);
  s.push(30);
  s.push(1);
  s.push(10);
  s.push(27);

  sort_stack(s);
  EXPECT_EQ(1,s.top());
  EXPECT_NO_THROW(s.pop());
  EXPECT_EQ(10,s.top());
  EXPECT_NO_THROW(s.pop());
  EXPECT_EQ(15,s.top());
  EXPECT_NO_THROW(s.pop());
  EXPECT_EQ(27,s.top());
  EXPECT_NO_THROW(s.pop());
  EXPECT_EQ(30,s.top());
  EXPECT_NO_THROW(s.pop());
  EXPECT_EQ(80,s.top());
  EXPECT_NO_THROW(s.pop());

  EXPECT_TRUE(s.empty());
}


int main(int argc, char** argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}


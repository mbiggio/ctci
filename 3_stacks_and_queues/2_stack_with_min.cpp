#include <iostream>
#include <stack>
#include <stdexcept>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace std;

/**
 * This class implements a stack 
 * having in addition a min function returning 
 * the minimum element of the stack in time O(1).
 * The usual stack operations (push(), top(), pop()) 
 * are still O(1).
 */
template <typename T>
class stack_with_min {

public:

  T& top() {
    if (s.empty()) {
      throw runtime_error("stack empty");
    }
    return s.top();
  }

  void pop() {
    if (s.empty()) {
      throw runtime_error("stack empty");
    }
    if (s.top() == smin.top()) smin.pop();
    s.pop();
  }

  bool empty() const {
    return s.empty();
  }

  void push(const T &item) {
    s.push(item);
    if (smin.empty() || smin.top() >= item) {
      smin.push(item);
    }
  }

  T min() const {
    if (s.empty()) {
      throw runtime_error("stack empty");
    }
    return smin.top();
  }

  size_t size() const {
    return s.size();
  }

private:
  stack<T> s;
  stack<T> smin;
};

TEST(stack_with_min_test, nominal) {

  stack_with_min<int> s;

  // push a few elements
  s.push(1);
  s.push(2);
  s.push(3);

  // pop elements until also the min is popped
  EXPECT_EQ(1,s.min());
  s.pop();
  EXPECT_EQ(1,s.min());
  s.pop();
  EXPECT_EQ(1,s.min());
  s.pop();
  EXPECT_THROW(s.min(),runtime_error);
  EXPECT_TRUE(s.empty());

  // push a few elements
  s.push(3);
  s.push(2);
  s.push(3);
  
  EXPECT_EQ(2,s.min());
  s.pop();
  EXPECT_EQ(2,s.min());
  s.pop();
  EXPECT_EQ(3,s.min());
  EXPECT_EQ(1,s.size());

  s.push(1);
  EXPECT_EQ(1,s.min());
  EXPECT_EQ(2,s.size());
}


int main(int argc, char** argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

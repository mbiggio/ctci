#include <iostream>
#include <list>
#include <queue>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tree.h"
using namespace std;

struct result {
  result(bool is_balanced,int height) : 
    is_balanced(is_balanced), height(height) {};
  bool is_balanced;
  int height;
};

result check_balanced_helper(TreeNode const * const root) {
  if (!root) return result(true,-1);
  auto right = check_balanced_helper(root->right);
  if (!right.is_balanced) return right;
  auto left = check_balanced_helper(root->left);
  if (!left.is_balanced) return left;
  return result(abs(left.height-right.height)<=1, 1+max(left.height,right.height));
}

bool check_balanced(TreeNode const * const root) {
  return check_balanced_helper(root).is_balanced;
}

TEST(check_balanced_test, nominal) {
  TreeNode *n1 = new TreeNode(1);
  TreeNode *n2 = new TreeNode(2);
  TreeNode *n3 = new TreeNode(3);
  TreeNode *n4 = new TreeNode(4);
  TreeNode *n5 = new TreeNode(5);

  n1->left = n2;
  n1->right = n3;
  ASSERT_TRUE(check_balanced(n1));

  n2->left = n4;
  ASSERT_TRUE(check_balanced(n1));

  n4->left = n5;
  ASSERT_FALSE(check_balanced(n1));
}


int main(int argc, char **argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

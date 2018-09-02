#include <iostream>
#include <list>
#include <queue>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tree.h"
using namespace std;

struct result {
  result (bool is_bst, int min_val, int max_val) : 
    is_bst(is_bst), min_val(min_val), max_val(max_val) {};
  bool is_bst;
  int min_val;
  int max_val;
};

result is_bst_helper(TreeNode const * const root) {
  // invariant : root != nullptr
  int min_val = root->val, max_val = root->val;
  if (root->left) {
    auto left = is_bst_helper(root->left);
    if (!left.is_bst) return left;
    if (left.max_val > root->val) return result(false,-1,-1);
    min_val = left.min_val;
  }
  if (root->right) {
    auto right = is_bst_helper(root->right);
    if (!right.is_bst) return right;
    if (right.min_val <= root->val) return result(false,-1,-1);
    max_val = right.max_val;
  }

  return result(true,min_val,max_val);
}

bool is_bst (TreeNode const * const root) {
  if (!root) return true;
  return is_bst_helper(root).is_bst;
}

TEST(is_bst_test, nominal) {
  TreeNode *n1 = new TreeNode(8);
  TreeNode *n2 = new TreeNode(4);
  TreeNode *n3 = new TreeNode(10);
  TreeNode *n4 = new TreeNode(2);
  TreeNode *n5 = new TreeNode(6);
  TreeNode *n6 = new TreeNode(20);
  TreeNode *n7 = new TreeNode(12);

  n1->left = n2;
  n1->right = n3;
  n2->left = n4;
  n3->right = n6;

  n2->right = n5;
  ASSERT_TRUE(is_bst(n1));

  n2->right = n7;
  ASSERT_FALSE(is_bst(n1));

}

int main(int argc, char **argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

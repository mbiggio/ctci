#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tree.h"
using namespace std;

int height(TreeNode const * const root) {
  if (!root) return -1;
  return 1 + max(height(root->left), height(root->right));
}

TreeNode *minimal_tree(const vector<int> &v, int start, int end) {
  if (start > end) return nullptr;
  int mid = start + (end-start)/2;
  TreeNode *root = new TreeNode(v[mid]);
  root->left = minimal_tree(v,start, mid-1);
  root->right = minimal_tree(v,mid+1,end);
}

TEST(minimal_tree_test, nominal) {
  {
    TreeNode *root = nullptr;
    EXPECT_NE(nullptr, root = minimal_tree({1,2,3,4,5},0,4));
    EXPECT_EQ(2,height(root));
  }
  {
    TreeNode *root = nullptr;
    EXPECT_NE(nullptr, root = minimal_tree({1,2,3,4},0,3));
    EXPECT_EQ(2,height(root));
  }
  {
    TreeNode *root = nullptr;
    EXPECT_NE(nullptr, root = minimal_tree({1,2,3},0,2));
    EXPECT_EQ(1,height(root));
  }
  {
    TreeNode *root = nullptr;
    EXPECT_NE(nullptr, root = minimal_tree({1,2},0,1));
    EXPECT_EQ(1,height(root));
  }
  {
    TreeNode *root = nullptr;
    EXPECT_NE(nullptr, root = minimal_tree({1},0,0));
    EXPECT_EQ(0,height(root));
  }
  {
    TreeNode *root = nullptr;
    EXPECT_EQ(nullptr, root = minimal_tree({},0,-1));
    EXPECT_EQ(-1,height(root));
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

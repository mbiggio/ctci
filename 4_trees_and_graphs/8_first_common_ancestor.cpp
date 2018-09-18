#include <iostream>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tree.h"
using namespace std;

struct result {
  result(bool has_first, bool has_second, const TreeNode *ancestor) :
    has_first(has_first), has_second(has_second), ancestor(ancestor) {};
  bool has_first;
  bool has_second;
  const TreeNode *ancestor;
};

result first_common_ancestor_helper(TreeNode const *root,  TreeNode const *n1, TreeNode const *n2) {

  // base case
  if (!root) return result(false,false,nullptr);

  // check left subtree
  auto rl = first_common_ancestor_helper(root->left, n1, n2);
  if (rl.has_first && rl.has_second) return rl;

  // check right subtree
  auto rr = first_common_ancestor_helper(root->right, n1, n2);
  if (rr.has_first && rr.has_second) return rr;

  // check root node
  bool has_first = rl.has_first || rr.has_first || root == n1;
  bool has_second = rl.has_second || rr.has_second || root == n2;
  TreeNode const *ptr = (has_second && has_second)?root:nullptr;
  return result(has_first,has_second,ptr);
}

TreeNode const *first_common_ancestor(TreeNode const *root, TreeNode const *n1, TreeNode const *n2) {
  return first_common_ancestor_helper(root,n1,n2).ancestor;
}

TEST(first_common_ancestor_test, baseline) {

  /***************************
   *            8
   *        4       10
   *      2   6    9  20
   ***************************/

  TreeNode *n8 = new TreeNode(8);
  TreeNode *n4 = new TreeNode(4);
  TreeNode *n10 = new TreeNode(10);
  TreeNode *n2 = new TreeNode(2);
  TreeNode *n6 = new TreeNode(6);
  TreeNode *n20 = new TreeNode(20);
  TreeNode *n9 = new TreeNode(9);

  n8->left = n4;
  n8->right = n10;
  n4->left = n2;
  n4->right = n6;
  n10->left = n9;
  n10->right = n20;

  ASSERT_EQ(n10, first_common_ancestor(n8,n9,n20));
  ASSERT_EQ(n10, first_common_ancestor(n8,n9,n10));
  ASSERT_EQ(n8, first_common_ancestor(n8,n6,n20));
  ASSERT_EQ(n8, first_common_ancestor(n8,n4,n20));
  ASSERT_EQ(n8, first_common_ancestor(n8,n8,n20));

  TreeNode *nout1 = new TreeNode(0);
  TreeNode *nout2 = new TreeNode(0);
  ASSERT_EQ(nullptr, first_common_ancestor(n8,n9,nout1));
  ASSERT_EQ(nullptr, first_common_ancestor(n8,nout1,nout2));
  ASSERT_EQ(nullptr, first_common_ancestor(nullptr,nullptr,nullptr));

}



int main(int argc, char **argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

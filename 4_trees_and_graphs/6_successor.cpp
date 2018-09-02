#include <iostream>
#include <list>
#include <queue>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tree.h"
using namespace std;

TreeNodeWithParent const * successor(TreeNodeWithParent const * node) {
  if (!node) return nullptr;
  if (node->right) {
    TreeNodeWithParent const * s = node->right;
    while (s->left) s = s->left;
    return s;
  }
  else {
    TreeNodeWithParent const * c = node;
    TreeNodeWithParent const * p = c->parent;
    while (p && p->right == c) {
      c = p;
      p = c->parent;
    }
    return p;
  }
}

TEST(successor_test, nominal) {

  TreeNodeWithParent *n8 = new TreeNodeWithParent(8);
  TreeNodeWithParent *n4 = new TreeNodeWithParent(4);
  TreeNodeWithParent *n10 = new TreeNodeWithParent(10);
  TreeNodeWithParent *n2 = new TreeNodeWithParent(2);
  TreeNodeWithParent *n6 = new TreeNodeWithParent(6);
  TreeNodeWithParent *n20 = new TreeNodeWithParent(20);
  TreeNodeWithParent *n9 = new TreeNodeWithParent(9);

  n8->left = n4;
  n4->parent = n8;
  n8->right = n10;
  n10->parent = n8;
  n4->left = n2;
  n2->parent = n4;
  n4->right = n6;
  n6->parent = n4;
  n10->left = n9;
  n9->parent = n10;
  n10->right = n20;
  n20->parent = n10;

  ASSERT_EQ(n8, successor(n6));
  ASSERT_EQ(n9, successor(n8));
  ASSERT_EQ(n20, successor(n10));

}
int main(int argc, char **argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

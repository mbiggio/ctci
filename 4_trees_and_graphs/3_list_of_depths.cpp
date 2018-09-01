#include <iostream>
#include <list>
#include <queue>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tree.h"
using namespace std;

/**
 * Contructs a vector of lists containing
 * the values of the nodes in the input tree
 * for each tree level.
 * Uses a BFS with sentinel to detect the beginning/end
 * of a level.
 */
vector<list<int>> levels(TreeNode const * const root) {
  queue<TreeNode const *> q;
  vector<list<int>> res;
  q.push(root);
  q.push(nullptr);

  list<int> cur_list;
  while (!q.empty()) {
    TreeNode const *cur = q.front();
    q.pop();

    if (!cur) {
      res.emplace_back(list<int>{});
      res.back().swap(cur_list);
      if (!q.empty()) q.push(nullptr);
    }
    else {
      cur_list.emplace_back(cur->val);
      if (cur->left) q.push(cur->left);
      if (cur->right) q.push(cur->right);
    }
  }

  return move(res);
}

TEST(levels_test, nominal) {

  TreeNode *n1 = new TreeNode(1);
  TreeNode *n2 = new TreeNode(2);
  TreeNode *n3 = new TreeNode(3);
  TreeNode *n4 = new TreeNode(4);

  n1->left = n2;
  n1->right = n3;
  n2->right = n4;

  auto v = levels(n1);
  vector<list<int>> v_ex = {{1},{2,3},{4}};
  ASSERT_EQ((size_t)3, v.size());
  for (int i=0; i<v.size(); ++i) {
    ASSERT_THAT(v[i], ::testing::ContainerEq(v_ex[i]));
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tree.h"
using namespace std;

void bst_sequences_helper(vector<TreeNode const *> &candidates,
                          vector<vector<int>> &result,
                          vector<int> &result_so_far) {
  if (candidates.empty()) {
    result.push_back(result_so_far);
    return;
  }

  int csize = candidates.size();
  for (int i=0; i<csize; ++i) {

    TreeNode const *node = candidates[i];

    // add new node 
    result_so_far.push_back(node->val);
    swap(candidates[i],candidates.back());
    candidates.pop_back();
    if (node->left) candidates.push_back(node->left);
    if (node->right) candidates.push_back(node->right);

    // recurse
    bst_sequences_helper(candidates,result,result_so_far);

    // restore
    if (node->right) candidates.pop_back();
    if (node->left) candidates.pop_back();
    candidates.push_back(node);
    swap(candidates[i],candidates.back());
    result_so_far.pop_back();
  }
}

vector<vector<int>> bst_sequences(TreeNode const * root) {
  if (!root) return {};
  vector<TreeNode const *> candidates = {root};
  vector<vector<int>> result;
  vector<int> result_so_far;
  bst_sequences_helper(candidates,result,result_so_far);
  return result;
}

TEST(bst_sequences, baseline) {

  /********************
   *        2 
   *      1   3
   ********************/

  TreeNode *n2 = new TreeNode(2);
  TreeNode *n1 = new TreeNode(1);
  TreeNode *n3 = new TreeNode(3);

  n2->left = n1;
  n2->right = n3;

  EXPECT_THAT(bst_sequences(n2),testing::ContainerEq(vector<vector<int>>{{2,1,3},{2,3,1}}));

}

int main(int argc, char **argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

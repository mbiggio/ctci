#ifndef __TREE__
#define __TREE_
#include <iostream>
#include <string>
#include <utility>

struct TreeNode {
  TreeNode(int val) : val(val), left(nullptr), right(nullptr) {};
  int val;
  TreeNode *left;
  TreeNode *right;
};

struct TreeNodeWithParent : public TreeNode {
  TreeNodeWithParent(int val) : TreeNode(val), parent(nullptr) {};
  TreeNodeWithParent *parent;
};

void print_pre_order_helper(const TreeNode *n) {
  if (!n) ::std::cout << "null ";
  else {
    ::std::cout << n->val << " ";
    print_pre_order_helper(n->left);
    print_pre_order_helper(n->right);
  }
}

void print_pre_order(const TreeNode *n) {
  print_pre_order_helper(n);
  ::std::cout << ::std::endl;
}

::std::pair<TreeNode*, size_t> read_pre_order(const ::std::string &preorder, ::std::size_t offset) { 
  // read_pre_order("1 2 null null 3 null null ", 0)
  // next = 1
  // strval == "1"
  //   read_pre_order("1 2 null null 3 null null ", 2)
  //   next = 3
  //   strval = "2"
  //     read_pre_order("1 2 null null 3 null null ", 4)
  //     next = 8
  //     strval = "null"
  //     return (nullptr,9)
  //     read_pre_order("1 2 null null 3 null null ", 9)
  //     next = 13
  //     strval = "null"
  //     return (nullptr,14)
  //   return (node(2),14)
  //   read_pre_order("1 2 null null 3 null null ", 14)
  //   next = 15
  //   strval = "3"
  //     read_pre_order("1 2 null null 3 null null ", 16)
  //     next = 20
  //     strval = "null"
  //     return (nullptr,21)
  //     read_pre_order("1 2 null null 3 null null ", 21)
  //     next = 25
  //     strval = "null"
  //     return (nullptr,26)
  //   return (node(3),26)
  // return (node(1),26)
  //   
  ::std::size_t next = preorder.find_first_of(" ",offset);
  ::std::string strval = preorder.substr(offset,next-offset);
  if (strval == "null") return ::std::make_pair(nullptr, next+1);
  TreeNode *root = new TreeNode(::std::stoi(strval));
  auto left = read_pre_order(preorder, next+1); 
  root->left = left.first;
  auto right = read_pre_order(preorder, left.second);
  root->right = right.first;
  return ::std::make_pair(root,right.second);

}

#endif

#ifndef __LINKED_LIST__
#define  __LINKED_LIST__
#include <iostream>

struct Node {
  Node(int val) : val(val), next(nullptr) {};
  int val;
  Node *next;
};

Node *add_to_tail(Node* head, Node *n) {
  if (!head) return n;
  Node *tail = head;
  while(tail->next) tail=tail->next;
  tail->next = n;
  return head;
}

Node *add_to_tail(Node* head, int val) {
  Node *n = new Node(val);
  return add_to_tail(head,n);
}

void print(Node* head) {
  while (head) {
    ::std::cout << head->val << " ";
    head = head->next;
  }
  ::std::cout << ::std::endl;
}


#endif

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt
 * to change this license Click
 * nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this
 * template
 */

#include "Tree.h"
#include <algorithm>
#include <iostream>
using namespace std;

void Tree::display(Node *ptr, int level) {
  int i;
  if (ptr != nullptr) {
    display(ptr->right, level + 1);
    cout << endl;
    if (ptr == root)
      cout << "R -> ";
    for (i = 0; i < level && ptr != root; i++)
      cout << "     ";
    cout << ptr->val;
    display(ptr->left, level + 1);
  }
}

int Tree::height(Node *node) {
  if (node == nullptr)
    return 0;
  return node->height;
}
int Tree::balFact(Node *node) {
  if (node == nullptr)
    return 0;
  return height(node->left) - height(node->right);
}

Node *Tree::rotL(Node *node) {
  Node *r = node->right;
  node->right = r->left;
  r->left = node;
  node->height = max(height(node->left), height(node->right)) + 1;
  r->height = max(height(r->left), height(r->right)) + 1;
  return r;
}

Node *Tree::rotR(Node *node) {
  Node *r = node->left;
  node->left = r->right;
  r->right = node;
  node->height = max(height(node->left), height(node->right)) + 1;
  r->height = max(height(r->left), height(r->right)) + 1;
  return r;
}

Node *Tree::balance(Node *node) {
  int bf = balFact(node);

  // Right Heavy with all links in straight chain
  if (bf < -1 && balFact(node->right) <= 0) {
    return rotL(node);
  }

  // Right Heavy with not all links being in a straight chain
  //    5 BF : -2 Need to Rotate Right Node Right First to Fix Non-Straight
  //    Chain
  //     \ 
    //     7 BF : -1
  //     /
  //    6 BF : 0
  //
  //
  // After Right Rotation Looks like this
  //    5 BF : -2 Need to Rotate Left Now
  //     \ 
    //     6 BF : -1
  //       \ 
    //       7 BF : 0
  //
  // After Left Rotation Looks like this
  //    6 BF: 0
  //    / \
    // 5   7 BF : 0 BF: 0
  //  Clearly Tree is Now Balanced as all balance factors fall within given
  //  tolerance BF -> [-1, 1] while still following rules of BST
  // Operations Performed
  // 1. Insert Node (already performed by insert function before calling
  // balance)
  // 2. Attempt to Return to Root node
  // 3. Once a unbalanced node has been found check if the value just inserted
  // was to the left or right of its left or right nodes
  // 4. If value was inserted to the left of the nodes right node then we must
  // rotate twice.
  // 5. Rotate about the right node of the node we are currently on to get all
  // nodes into straight chain
  // 6. Rotate Left about our current node

  if (bf < -1 && balFact(node->right) > 0) {
    node->right = rotR(node->right);
    return rotL(node);
  }

  // Left Heavy with not all links being in a straight chain (same steps as in
  // right heavy with not all links in straight chain just reversed)
  if (bf > 1 && balFact(node->left) < 0) {
    node->left = rotL(node->left);
    return rotR(node);
  }

  // Left Heavy with all links being straight chain
  if (bf > 1 && balFact(node->left) >= 0) {
    return rotR(node);
  }

  return node;
}

Node *Tree::insert(Node *node, int val) {
  if (node == nullptr) {
    Node *r = new Node;
    r->val = val;
    r->left = nullptr;
    r->right = nullptr;
    r->height = 1;
    return r;
  }
  if (val < node->val)
    node->left = insert(node->left, val);
  else
    node->right = insert(node->right, val);

  node->height = max(height(node->right), height(node->left)) + 1;
  return balance(node);
}

void Tree::inOrder(Node *node) {
  if (node == nullptr)
    return;
  inOrder(node->left);
  cout << (char)node->val;
  inOrder(node->right);
}

void Tree::prntLev(Node *node, int level) {
  if (node == nullptr)
    return;
  if (level == 1)
    cout << (char)node->val << " ";
  else if (level > 1) {
    prntLev(node->left, level - 1);
    prntLev(node->right, level - 1);
  }
}

void Tree::prntLev(Node *node) {
  int h = height(node);
  for (int i = 1; i <= h; i++)
    prntLev(node, i);
}

void Tree::preOrdr(Node *node) {
  if (node == nullptr)
    return;
  cout << node->val << " ";
  preOrdr(node->left);
  preOrdr(node->right);
}

void Tree::pstOrdr(Node *node){
    if (node == nullptr) return;
    pstOrdr(node->left);
    pstOrdr(node->right);
    cout<<node->val<<" ";
}

void Tree::insert(int val) { root = insert(root, val); }

void Tree::clean(Node *node) {
  if (node != nullptr) {
    clean(node->right);
    clean(node->left);
    delete node;
  }
}

Node *Tree::find(Node *node, int val) {
  if (node == nullptr)
    return node;
  else if (val == node->val)
    return node;
  else if (val > node->val) {
    node = find(node->right, val);
  } else if (val < node->val) {
    node = find(node->left, val);
  }

  return node;
}

Node *Tree::findMax(Node *node) {
  if (node == nullptr)
    return node;
  while (node->right != nullptr)
    node = node->right;
  return node;
}

Node *Tree::delNode(Node *node, int val) {
  // Check to see if node entered is valid
  if (node == nullptr)
    return node;
  if (val < node->val) 
    node->left = delNode(node->left, val);
  else if (val > node->val) 
    node->right = delNode(node->right, val);
  else {
    if (node->left == nullptr ||node->right == nullptr) { 
      Node *temp = node->left? node->left: node->right; 
      if (temp == nullptr) { 
        temp = node;
        node = nullptr;
        delete temp;
      } else {
        Node *temp2 = node;
        node = temp;
        delete temp2;
      }
    } else {
      Node *temp = findMax(node->left);
      node->val = temp->val;
      node->left = delNode(node->left, temp->val);
    }
  }

  if (node == nullptr)
    return node;
  node->height = max(height(node->left), height(node->right))+1;

  balance(node);

  return node;
}

Tree::~Tree() { clean(root); }

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt
 * to change this license Click
 * nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this
 * template
 */

/*
 * File:   Tree.h
 * Author: Daniel
 *
 * Created on May 27, 2023, 1:03 PM
 */

#ifndef TREE_H
#define TREE_H

struct Node {
  int val;
  Node *left;
  Node *right;
  int height;
};

class Tree {
private:
  int height(Node *);
  int balFact(Node *);
  Node *rotL(Node *);
  Node *rotR(Node *);
  Node *findMax(Node *);
  Node *balance(Node *);
  Node *insert(Node *, int);
  void prntLev(Node *, int);

public:
  Node *root;
  void insert(int);
  void inOrder(Node *);
  void prntLev(Node *);
  Node *find(Node *, int);
  Node *delNode(Node *, int);
  void preOrdr(Node *);
  void pstOrdr(Node *);
  Tree() { root = nullptr; }
  ~Tree();
  void clean(Node *);
  void display(Node *, int);
};

#endif /* TREE_H */

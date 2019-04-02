#ifndef __TREE_H
#define __TREE_H

#include "Node.h"

class Tree {
private:
  Node *root;

public: //given
  Tree();
  ~Tree();
  void insert(const string &);
  void preOrder() const;
  void inOrder() const;
  void postOrder() const;
  void remove(const string &);
  bool search (const string &) const;

private: //created :(
  string smallestNode(Node *, const string &);
  string middleNode(Node *, const string &);
  string largestNode(Node *, const string &);
  void split(Node *, const string &, Node *, Node *, Node*, Node*);
  void removeNodes(Node *);                     
  bool isTwo(Node *) const;
  bool isThree(Node *) const;
  bool isLeaf(Node *) const;
  void preOrder(Node *) const;
  void inOrder(Node *) const;
  void postOrder(Node *) const;
  Node* getSibling(Node *);
  Node* search(Node *, const string &) const;
  Node* getNext(Node *, const string &) const;
  void deleteNode(Node *);
};

#endif

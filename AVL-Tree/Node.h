#pragma once
#include <iostream>
#include "NodeInterface.h"
using namespace std;

class Node: public NodeInterface {
friend class AVL;
public:
	Node() {}
  Node(int input_data) {
    data = input_data;
  }
	~Node() {}

	//@return the data stored in this node.
	int getData() const;

	//@return the left child of this node or null if empty left child.
	NodeInterface * getLeftChild() const;

	//@return the right child of this node or null if empty right child.
	NodeInterface * getRightChild() const;

	//@return the height of this tree with this node as the local root.
	int getHeight();
private:
  int data;
  Node* leftChild = NULL;
  Node* rightChild = NULL;
  int height = 0;
};

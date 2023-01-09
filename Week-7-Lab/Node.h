#pragma once

#include <iostream>
#include "NodeInterface.h"

class Node: public NodeInterface {
friend class BST;
public:
	Node() {}
  Node(int input_data) {
    data = input_data;
  }
	~Node() {}

	int getData() const;

	NodeInterface * getLeftChild() const;

	NodeInterface * getRightChild() const;
private:
  int data;
  Node* leftChild = NULL;
  Node* rightChild = NULL;
};
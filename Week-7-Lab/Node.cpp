#include <iostream>
#include "Node.h"

/*
* Returns the data that is stored in this node
*/
int Node::getData() const {
  return data;
};

/*
* Returns the left child of this node or null if it doesn't have one.
*/
NodeInterface * Node::getLeftChild() const {
  return leftChild;
};

/*
* Returns the right child of this node or null if it doesn't have one.
*/
NodeInterface * Node::getRightChild() const {
  return rightChild;
};
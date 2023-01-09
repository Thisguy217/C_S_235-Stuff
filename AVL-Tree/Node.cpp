#include <iostream>
#include "Node.h"
using namespace std;

int Node::getData() const{
  return data;
}

//@return the left child of this node or null if empty left child.
NodeInterface * Node::getLeftChild() const{
  return leftChild;
}

//@return the right child of this node or null if empty right child.
NodeInterface * Node::getRightChild() const{
  return rightChild;
}

//@return the height of this tree with this node as the local root.
int Node::getHeight() {
  return height;
}
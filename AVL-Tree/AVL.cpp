#include "AVL.h"
#include <iostream>
using namespace std;

//@return the root node for this tree.
NodeInterface *AVL::getRootNode() const { return root_node; }

//@return true if added
//@return false if unsuccessful (i.e. the int is already in tree)
bool AVL::add(int data) { return addChild(root_node, data); }

//@return true if successfully removed
//@return false if remove is unsuccessful(i.e. the int is not in the tree)
bool AVL::remove(int data) { return removeRecurse(root_node, data); }

void AVL::clear() { 
  DeleteNode(root_node); 
}

bool AVL::addChild(Node *&root, int looking_for) {
  bool returnVal = false;
  if (root == NULL) {
    root = new Node(looking_for);
    returnVal = true;
  }
  if (root->data > looking_for) {
    returnVal = addChild(root->leftChild, looking_for);
  } else if (root->data < looking_for) {
    returnVal = addChild(root->rightChild, looking_for);
  }
  updateHeight(root);
  rebalanceTree(root);
  return returnVal;
}

bool AVL::removeRecurse(Node *&root, int looking_for) {
  bool returnVal = false;
  if (root == NULL) {
    updateHeight(root);
    rebalanceTree(root);
    return false;
  }
  if (root->data < looking_for) {
    bool specialVal = removeRecurse(root->rightChild, looking_for);
    if (specialVal) {
      updateHeight(root);
      rebalanceTree(root);
    }
    return specialVal;
  } else if (root->data > looking_for) {
    bool specialVal = removeRecurse(root->leftChild, looking_for);
    if (specialVal) {
      updateHeight(root);
      rebalanceTree(root);
    }
    return specialVal;
  }
  if (root->data == looking_for) {
    if (root->rightChild == NULL && root->leftChild == NULL) {
      delete root;
      root = NULL;
      returnVal = true;
      updateHeight(root);
      rebalanceTree(root);
    } else if (root->rightChild != NULL && root->leftChild != NULL) {
      Node *temp = root->leftChild;
      //Node *temp2 = root;
      while (temp->rightChild != NULL) {
        //temp2 = temp;
        temp = temp->rightChild;
      }
      root->data = temp->data;
      removeRecurse(root->leftChild, temp->data);
      /*if (temp2 == root) {
        temp2->leftChild = temp->leftChild;
      } else {
        temp2->rightChild = temp->leftChild;
      }
      delete temp;
      temp = NULL;*/
      returnVal = true;
      updateHeight(root);
      rebalanceTree(root);
    } else if (root->rightChild != NULL && root->leftChild == NULL) {
      //Node *temp = root;
      //root = root->rightChild;
      //delete temp;
      //temp = NULL;
      Node *temp = root->rightChild;
      root->data = temp->data;
      root->rightChild = temp->rightChild;
      root->leftChild = temp->leftChild;
      delete temp;
      temp = NULL;
      returnVal = true;
      updateHeight(root);
      rebalanceTree(root);
    } else if (root->rightChild == NULL && root->leftChild != NULL) {
      Node *temp = root->leftChild;
      root->data = temp->data;
      root->rightChild = temp->rightChild;
      root->leftChild = temp->leftChild;
      delete temp;
      temp = NULL;
      returnVal = true;
      updateHeight(root);
      rebalanceTree(root);
    }
  }
  updateHeight(root);
  rebalanceTree(root);
  return returnVal;
}

void AVL::DeleteNode(Node *&node) {
  if (node == NULL) {
    return;
  }
  if (node->leftChild == NULL && node->rightChild == NULL) {
    delete node;
    node = NULL;
    return;
  } else if (node->leftChild != NULL && node->rightChild != NULL) {
    DeleteNode(node->leftChild);
    DeleteNode(node->rightChild);
    delete node;
    node = NULL;
    return;
  } else if (node->leftChild == NULL && node->rightChild != NULL) {
    DeleteNode(node->rightChild);
    delete node;
    node = NULL;
    return;
  } else if (node->leftChild != NULL && node->rightChild == NULL) {
    DeleteNode(node->leftChild);
    delete node;
    node = NULL;
    return;
  }
  return;
}

void AVL::updateHeight(Node *&node) {
  if (node == NULL) {
    return;
  }
  int right, left;
  if (node->rightChild == NULL) {
    right = -1;
  } else {
    right = node->rightChild->height;
  }
  if (node->leftChild == NULL) {
    left = -1;
  } else {
    left = node->leftChild->height;
  }
  node->height = ((left > right) * left + (right >= left) * right) + 1;
  // get height left child if left child is null height  = -1
  // get height right child if right child is null height = -1
  // node->height=(left>right*left+right>=left*right)+1
}

void AVL::rebalanceTree(Node *&node) {
  if (node == NULL) {
    return;
  }
  int right;
  int left; 
  int balance;
  Node *heavySide;
  Node *heaviestSide;
  if (node->rightChild == NULL && node->leftChild == NULL) {
    return;
  }
  if (node->rightChild == NULL) {
    right = -1;
  } else {
    right = node->rightChild->height;
  }
  if (node->leftChild == NULL) {
    left = -1;
  } else {
    left = node->leftChild->height;
  }
  balance = left - right;
  if (balance > 1) {
    heavySide = node->leftChild;
    heaviestSide = heightChecker(heavySide);
    if (heavySide->rightChild == heaviestSide) {
      leftRotate(node->leftChild);
    }
    //if heavySide->left == heaviestSide run rightRotate (node->leftChild)
    rightRotate(node);
  } else if (balance < -1) {
    heavySide = node->rightChild;
    heaviestSide = 
      heightChecker(heavySide);
    if (heavySide->leftChild == heaviestSide) {
      rightRotate(node->rightChild);
    }
    leftRotate(node);
  }
  // balance = left - right > 1
  // if balance > 1 check left
  // if balance < 1 check right
  // check the two children of chosen side
  // do rotations on which subtree is heavier
  // rebalance the tree
}

void AVL::rightRotate(Node *&node) {
  Node *temp = node->leftChild;
  node->leftChild = temp->rightChild;
  temp->rightChild = node;
  node = temp;
  updateHeight(temp->rightChild);
  updateHeight(temp);
}

void AVL::leftRotate(Node *&node) {
  Node *temp = node->rightChild;
  node->rightChild = temp->leftChild;
  temp->leftChild = node;
  node = temp;
  updateHeight(temp->leftChild);
  updateHeight(temp);
}

Node *AVL::heightChecker(Node *node) {
  int left, right;
  if (node->rightChild == NULL) {
    right = -1;
  } else {
    right = node->rightChild->height;
  }
  if (node->leftChild == NULL) {
    left = -1;
  } else {
    left = node->leftChild->height;
    }
  if (left > right) {
    return node->leftChild;
  } else if (left < right) {
    return node->rightChild;
  } else if (right == left) {
    return NULL;
  }
  return NULL;
}
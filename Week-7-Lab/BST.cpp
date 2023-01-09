#include "Node.h"
#include "BST.h"

using namespace std;

/*
* Returns the root node for this tree
*/
NodeInterface * BST::getRootNode() const {
  return root_node;
};

/*
* Attempts to add the given int to the BST tree
* @return true if added
* @return false if unsuccessful (i.e. the int is already in tree)
*/
bool BST::add(int data) {
  return addChild(root_node, data);
}

/*
* Attempts to remove the given int from the BST tree
* @return true if successfully removed
* @return false if remove is unsuccessful(i.e. the int is not in the tree)
*/
bool BST::remove(int data) {
  return removeRecurse(root_node, data);
}

/*
* Removes all nodes from the tree, resulting in an empty tree.
*/
void BST::clear() {
  DeleteNode(root_node);
};

bool BST::addChild(Node *&root, int looking_for) {
  if (root == NULL) {
    root = new Node(looking_for);
    return true;
  } 
  if (root->data > looking_for) {
    return addChild(root->leftChild, looking_for);
  } else if (root->data < looking_for) {
    return addChild(root->rightChild, looking_for);
  }
  return false;
};

bool BST::removeRecurse(Node *&root, int looking_for) {
  if (root == NULL) {
    return false;
  }
  if (root->data < looking_for) {
    return removeRecurse(root->rightChild, looking_for);
  } else if (root->data > looking_for) {
    return removeRecurse(root->leftChild, looking_for);
  }
  if (root->data == looking_for) {
    if (root->rightChild == NULL && root->leftChild == NULL) {
      delete root;
      root = NULL;
      return true;
    } else if (root->rightChild != NULL && root->leftChild != NULL) {
      Node *temp = root->leftChild;
      Node *temp2 = root;
      while (temp->rightChild != NULL) {
        temp2 = temp;
        temp = temp->rightChild;
      }
      root->data = temp->data;
      if (temp2 == root) {
        temp2->leftChild = temp->leftChild;
      } else {
        temp2->rightChild = temp->leftChild;
      }
      delete temp;
      temp = NULL;
      return true;
    } else if (root->rightChild != NULL && root->leftChild == NULL) {
      Node *temp = root->rightChild;
      root->data = temp->data;
      root->rightChild = temp->rightChild;
      root->leftChild = temp->leftChild;
      delete temp;
      return true;
    } else if (root->rightChild == NULL && root->leftChild != NULL) {
      Node *temp = root->leftChild;
      root->data = temp->data;
      root->rightChild = temp->rightChild;
      root->leftChild = temp->leftChild;
      delete temp;
      return true;
    }
  }
  if (root->data != looking_for && root->rightChild == NULL && root->leftChild == NULL) {
    return false;
  }
  return false;
}

bool BST::DeleteNode(Node *&node) {
  if (node == NULL) {
    return true;
  }
  if (node->leftChild == NULL && node->rightChild == NULL) {
    delete node;
    node = NULL;
    return true;
  } else if (node->leftChild != NULL && node->rightChild != NULL) {
    DeleteNode(node->leftChild);
    DeleteNode(node->rightChild);
    delete node;
    node = NULL;
    return true;
  } else if (node->leftChild == NULL && node->rightChild != NULL) {
    DeleteNode(node->rightChild);
    delete node;
    node = NULL;
    return true;
  } else if (node->leftChild != NULL && node->rightChild == NULL) {
    DeleteNode(node->leftChild);
    delete node;
    node = NULL;
    return true;
  }
  return false;
}
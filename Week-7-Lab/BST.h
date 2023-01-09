#pragma once

#include "Node.h"
#include "BSTInterface.h"

using namespace std;

class BST : public BSTInterface {
public:
	BST() {}
  BST(int input_data) {
    root_node->data = input_data;
  }
	~BST() { clear(); }

	NodeInterface * getRootNode() const;

	bool add(int data);

	bool remove(int data);

	void clear();

  bool addChild(Node *&root, int looking_for);

  bool removeRecurse(Node *&root, int looking_for);

  bool DeleteNode(Node *&node);
private:
  Node *root_node = NULL;
};
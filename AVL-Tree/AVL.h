#pragma once
#include <iostream>
#include "AVLInterface.h"
#include "Node.h"

using namespace std;

class AVL : public AVLInterface {
public:
	AVL() {}
	~AVL() { clear(); }

	/*
	* Returns the root node for this tree
	*
	* @return the root node for this tree.
	*/
	NodeInterface * getRootNode() const;

	/*
	* Attempts to add the given int to the AVL tree
	* Rebalances the tree if data is successfully added
	*
	* @return true if added
	* @return false if unsuccessful (i.e. the int is already in tree)
	*/
	bool add(int data);

	/*
	* Attempts to remove the given int from the AVL tree
	* Rebalances the tree if data is successfully removed
	*
	* @return true if successfully removed
	* @return false if remove is unsuccessful(i.e. the int is not in the tree)
	*/
	bool remove(int data);

	/*
	* Removes all nodes from the tree, resulting in an empty tree.
	*/
	void clear();

  bool addChild(Node *&root, int looking_for);

  bool removeRecurse(Node *&root, int looking_for);

  void DeleteNode(Node *&node);

  void updateHeight(Node *&node);

  void rebalanceTree(Node *&node);

  void rightRotate(Node *&node);

  void leftRotate(Node *&node);

  Node* heightChecker(Node *node);
private:
  Node *root_node = NULL;
};
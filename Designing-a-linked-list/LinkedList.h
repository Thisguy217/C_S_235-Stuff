#pragma once

#include "LinkedListInterface.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template <typename T>

class LinkedList : public LinkedListInterface<T> {
private:
  struct Node {
    T data;
    Node *next;
    Node(const T &the_data, Node *next_val = NULL) : data(the_data) {
      next = next_val;
    }
  };
  Node *mylist;
  int listSize = 0;

public:
  LinkedList() {
    mylist = NULL;
    listSize = 0;
  };
  ~LinkedList(){};
  /*
  A node with the given value should be inserted at the beginning of the list.
  Do not allow duplicate values in the list.
  */
  void insertHead(T value) {
    for (Node *ptr = mylist; ptr != NULL; ptr = ptr->next) {
      if (ptr->data == value) {
        return;
      }
    }
    Node *ptr = mylist;
    mylist = new Node(value);
    mylist->next = ptr;
    listSize++;
  }

  /*
  A node with the given value should be inserted at the end of the list.
  Do not allow duplicate values in the list.
  */
  void insertTail(T value) {
    for (Node *ptr = mylist; ptr != NULL; ptr = ptr->next) {
      if (ptr->data == value) {
        return;
      }
    }
    Node *newTail = new Node(value);
    if (listSize == 0) {
      mylist = newTail;
    } else {
      Node *lastNode = mylist;
      while (lastNode->next != NULL) {
        lastNode = lastNode->next;
      }
      lastNode->next = newTail;
    }
    listSize++;
  };

  /*
  A node with the given value should be inserted immediately after the
  node whose value is equal to insertionNode.
  A node should only be added if the node whose value is equal to
  insertionNode is in the list. Do not allow duplicate values in the list.
  */
  void insertAfter(T value, T insertionNode) {
    for (Node *ptr = mylist; ptr != NULL; ptr = ptr->next) {
       if (ptr->data != insertionNode && ptr->next == NULL) {
        return;
        }
      }
    Node *temp;
    for (Node *ptr = mylist; ptr != NULL; ptr = ptr->next) {
      if (ptr->data == value) {
        return;
        }
      if (ptr->data == insertionNode) {
        temp = ptr;
        break;
      }
    }
    Node *newInsert = new Node(value, temp->next);
    temp->next = newInsert;
    listSize++;
  };

  /*
  The node with the given value should be removed from the list.
  The list may or may not include a node with the given value.
  */
  void remove(T value) { 
    if (mylist->data == value) {
      Node *temp = mylist;
      mylist = mylist->next;
      delete temp;
      listSize--;
      return;
    }
    for (Node *ptr = mylist; ptr != NULL; ptr = ptr->next) {
      if (ptr->next == NULL) {
        return;
      }
      if (ptr->next->data == value) {
        Node *prev = ptr;
        Node *temp = ptr->next;
        Node *nextNode = ptr->next->next;
        prev->next = nextNode;
        delete temp;
        listSize--;
        return;
      }
    }
  };

  /*
  Remove all nodes from the list.
  */
  void clear(){
    while(listSize != 0) {
      Node *temp = mylist;
      mylist = mylist->next;
      delete temp;
      listSize--;
    }
  };

  /*
  Returns the value of the node at the given index. The list begins at
  index 0.
  If the given index is out of range of the list, throw an out of range
  exception.
  */
  T at(int index) {
    try {
      if (index <  0 || index > listSize-1) {
        throw(index);
        }
    } catch (int out_of_range) {
      cout << "at "<< out_of_range << " out_of_range";
    }
    int count = 0;
    T returnData;
    for (Node *ptr = mylist; ptr != NULL; ptr = ptr->next) {
      if (count == index) {
        returnData = ptr->data;
      }
      count++;
    }
    return returnData;
  };

  /*
  Returns the number of nodes in the list.
  */
  int size() { return listSize; }

  /*
  Returns a string representation of the list, with the value of each node
  listed in order (Starting from the head) and separated by a single space There
  should be no trailing space at the end of the string For example, a LinkedList
  containing the value 1, 2, 3, 4, and 5 should return "1 2 3 4 5"
  */
  string toString() {
    stringstream ss;
    if (listSize == 0) {
      return "";
    }
    for (Node *ptr = mylist; ptr != NULL; ptr = ptr->next) {
      ss << ptr->data;
      if (ptr->next != NULL) {
        ss << " ";
      }
    }
    return (ss.str());
  };
};
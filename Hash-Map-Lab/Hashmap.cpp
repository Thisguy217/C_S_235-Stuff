#include "Hashmap.h"
#include <iostream>
#include <queue>
#include <sstream>
#include <stdexcept>
#define BUCKETS 10

using namespace std;

Hashmap::Hashmap() {
  for (int i = 0; i < BUCKETS; i++) {
    buckets[i] = NULL;
  }
  mapSize = 0;
}
Hashmap::~Hashmap() { clear(); }

void Hashmap::insert(string key, int value) {
  unsigned int hashVal = hash(key);// if hashVal gives us a NULL we then make a new node linked list and insert
  if (buckets[hashVal] == NULL) {// if hashVal gives us a Node find if the value exists if not insert on it
    buckets[hashVal] = new Node(key, value);
    mapSize++;
    return;
  } else if (buckets[hashVal]->key == key) {
    buckets[hashVal]->value = value;
    return;
  } else {
    Node *temp = buckets[hashVal];
    while (temp->next != NULL) {
      if (temp->key == key) {
        temp->value = value;
        return;
      }
      temp = temp->next;
    }
    if (temp->key == key) {
      temp->value = value;
      return;
    } else {
      temp->next = new Node(key, value);
      mapSize++;
      return;
    }
  }
}

bool Hashmap::contains(string key) const {
  unsigned int hashVal = hash(key);// go to hashVal and run down the nodes there, if the node has value == key
  if (buckets[hashVal] == NULL) {// return true else false
    return false;
  } else if (buckets[hashVal]->key == key) {
    return true;
  } else {
    Node *temp = buckets[hashVal];
    while (temp->next != NULL) {
      if (temp->key == key) {
        return true;
      }
      temp = temp->next;
    }
    if (temp->key == key) {
      return true;
    } else {
      return false;
    }
  }
}

int Hashmap::get(string key) const {
  unsigned int hashVal = hash(key);// go to hashVal run down through the nodes, if the node has the value == key
  if (buckets[hashVal] == NULL) {// return the value store else throw error
    throw invalid_argument("Key does not exist in Hash Map");
  } else if (buckets[hashVal]->key == key) {
    return buckets[hashVal]->value;
  } else {
    Node *temp = buckets[hashVal];
    while (temp->next != NULL) {
      if (temp->key == key) {
        return temp->value;
      }
      temp = temp->next;
    }
    if (temp->key == key) {
      return temp->value;
    } else {
    throw invalid_argument("Key does not exist in Hash Map");
    }
  }
}

int& Hashmap::operator[](string key) {
  unsigned int hashVal = hash(key);
  if (buckets[hashVal] == NULL) {
    buckets[hashVal] = new Node(key, 0);
    mapSize++;
    return buckets[hashVal]->value;
  } else if (buckets[hashVal]->key == key) {
    return buckets[hashVal]->value;
  } else {
    Node *temp = buckets[hashVal];
    while (temp->next != NULL) {
      if (temp->key == key) {
        return temp->value;
      }
      temp = temp->next;
    }
    if (temp->key == key) {
      return temp->value;
    } else {
      temp->next = new Node(key, 0);
      mapSize++;
      return temp->next->value;
    }
  }
}

bool Hashmap::remove(string key) {
  unsigned int hashVal = hash(key);
  if (buckets[hashVal]->key == key) {
    Node *temp = buckets[hashVal];
    buckets[hashVal] = buckets[hashVal]->next;
    delete temp;
    mapSize--;
    return true;
  }
  for (Node *ptr = buckets[hashVal]; ptr != NULL; ptr = ptr->next) {
    if (ptr->next == NULL) {
      return false;
    }
    if (ptr->next->key == key) {
      Node *prev = ptr;
      Node *temp = ptr->next;
      Node *nextNode = ptr->next->next;
      prev->next = nextNode;
      delete temp;
      mapSize--;
      return true;
    }
  }
  return false;
}

void Hashmap::clear() {
  for (int i = 0; i < BUCKETS; i++) {
    while (buckets[i] != NULL) {
      Node *temp = buckets[i];
      buckets[i] = temp->next;
      delete temp;
      temp = NULL;
    }
    buckets[i] = NULL;
  }
  mapSize = 0;
}

string Hashmap::toString() const {
  stringstream ss;
  for (int i = 0; i < BUCKETS; i++) {
    //ss out i
    //while temp != NULL
    //ss << " " << temp->key << " => " << temp->value << "," << endl;
    Node *temp = buckets[i];
      while (temp != NULL) {
        ss << i << " " << temp->key << " => " << temp->value << "," << endl;
        temp = temp->next;
    }
  }
  return ss.str();
}

int Hashmap::size() const { return mapSize; }

/*
 * Get string representation of all keys and related values
 *  Sort by values in descending order
 *   For nodes that have the same value, sort alphabetically by key in ascending
 * order. You should use the NodeCompare struct to sort nodes. Because a hashmap
 * cannot sort items, you will have to use a different data structure to do the
 * sorting. Use a priority queue to do a heapsort. Each key/value pair in the
 * map should be on its own line with no leading or trailing spaces:
 *
 *  key => value
 *
 * For example:
 *  bob => 13
 *  alice => 9
 *  eve => 3
 *  steve => 3
 *  nancy => 1
 *  tom => 1
 */
string Hashmap::toSortedString() const {
  stringstream ss;
  priority_queue<Node *, vector<Node *>, NodeCompare> nodeHeap;
  for (int i = 0; i < BUCKETS; i++) {
    // Iterate through each bucket. Use nodeHeap.push to push all Node* onto
    // heap.
    Node *temp = buckets[i];
    while (temp != NULL) {
      nodeHeap.push(temp);
      temp = temp->next;
    }
  }
  while (!nodeHeap.empty()) {
    Node *top = nodeHeap.top(); // Get top node (next node in sorted order)
    ss << top->key << " => " << top->value
       << endl;     // Add node data to stringstream
    nodeHeap.pop(); // Pop it off
  }
  return ss.str();
}

unsigned int Hashmap::hash(string Key) const {
  unsigned int hash = 7;
  for (int i = 0; i < Key.length(); i++) {
    hash = hash * 31 + Key.at(i);
  }
  return hash % BUCKETS;
}
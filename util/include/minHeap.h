#ifndef __MINHEAP__
#define __MINHEAP__

#include "building.h"
#include "redBlackTree.h"
#include <iostream>
#include <vector>
using namespace std;

class heapNode{
private:
  building* dataNode;
  RBNode* RBPtr;

public:
  heapNode(building* dataNode);
  heapNode(building* dataNode, RBNode* RBPtr);
  void updateRBPtr(RBNode* RBPtr);
  RBNode* getRBPtr();

  friend class minHeap;
};

class minHeap{
private:
  vector<heapNode> hNodes;

/* Helper Functuons */
  int parent(int);
  int left(int);
  int right(int);
  void heapifyUp(int index);
  void heapifyDown(int);
  int size();
public:

  /* main functions */
  void insertNode(heapNode hNode);
  void removeMin();
  heapNode getMin();
  void print();
};

#endif

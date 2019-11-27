#ifndef __REDBLACK__
#define __REDBLACK__


#include "building.h"

enum Color {RED, BLACK};

class RBNode{
private:
  building* dataNode;
  //minHeap* heapPtr;
  RBNode* left;
  RBNode* right;
  RBNode* parent;
  bool color; //1: Black, 0: Red
  friend class redBlack;

  /* Helper Funtions */
  RBNode* uncle();
  RBNode* sibling();
  bool isOnLeft();
  bool hasRedChild();
  void moveDown(RBNode *nParent);

public:
  RBNode(building* dataNode);
  void print();
};

class redBlack{
private:
   RBNode *root;

  RBNode* BSTInsert(RBNode* root, RBNode* newNode);
  void rotateRight(RBNode*& root, RBNode*& newNode);
  void rotateLeft(RBNode*& root, RBNode*& newNode);
  void fixViolation(RBNode*& root, RBNode*& newNode);
  void inorderHelper(RBNode *root);
  void rightRotate(RBNode *);
  void leftRotate(RBNode *);

  void swapLeft(RBNode *, RBNode *);
  void swapRight(RBNode *, RBNode *);
  void swapParent(RBNode *, RBNode *);
  void swapNodes(RBNode *, RBNode *);
  void fixRedRed(RBNode *);
  void fixDoubleBlack(RBNode *);
  RBNode* successor(RBNode *);
  RBNode* BSTreplace(RBNode *);
  void search(RBNode *, int);
  void searchRange(RBNode *,int , int);
  void rangeInorder(RBNode *,int , int);
public:
  redBlack();
  void insertNode(RBNode *);
  void deleteNode(RBNode *);
  void printInOrder();
  void printBuilding(int);
  void printBuildingRange(int lower, int upper);

};

#endif

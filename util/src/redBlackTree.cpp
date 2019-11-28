#include "redBlackTree.h"
#include <iostream>
using namespace std;

int comma = 0;
/*struct RBNode{
  building* dataNode;
  //minHeap* heapnewNoder;
  redBlack* left;
  redBlack* right;
  redBlack* parent;
  bool color; //1: Black, 0: Red
}*/

RBNode::RBNode(building* dataNode){
  this->dataNode = dataNode;
  left = right = parent = NULL;
  color = RED;
}

void RBNode::print(){
  this->dataNode->print();
}

redBlack::redBlack(){
  root = NULL;
}

bool RBNode :: isOnLeft() { return this == parent->left; }

RBNode* RBNode:: sibling() {
    // sibling null if no parent
    if (parent == NULL)
      return NULL;

    if (isOnLeft())
      return parent->right;

    return parent->left;
  }

RBNode* RBNode :: uncle() {
    // If no parent or gParent, then no uncle
    if (parent == NULL or parent->parent == NULL)
      return NULL;

    if (parent->isOnLeft())
      // uncle on right
      return parent->parent->right;
    else
      // uncle on left
      return parent->parent->left;
}

void RBNode :: moveDown(RBNode *nParent) {
  if (parent != NULL) {
    if (isOnLeft()) {
      parent->left = nParent;
    } else {
      parent->right = nParent;
    }
  }
  nParent->parent = parent;
  parent = nParent;
}

bool RBNode :: hasRedChild() {
  return (left != NULL and left->color == RED) or
         (right != NULL and right->color == RED);
}

void redBlack:: insertNode(RBNode* newNode){
  root = BSTInsert(root, newNode);
  fixViolation(root, newNode);
}

RBNode* redBlack:: BSTInsert(RBNode* root, RBNode* newNode){
    /* If the tree is emnewNodey, return a new node */
    if (root == NULL)
       return newNode;
    int comparator = newNode->dataNode->compareBuildNum(root->dataNode);
    if(comparator == EQUAL){
      cout<<"Found Equal:Duplicate Entry:Exit"<<endl;
        exit(0);
    }
    else if (comparator == LESS){
        root->left  = BSTInsert(root->left, newNode);
        root->left->parent = root;
    }
    else{
        root->right = BSTInsert(root->right, newNode);
        root->right->parent = root;
    }
    return root;
}

void redBlack::leftRotateforInsert(RBNode *&root, RBNode *&newNode){
    //cout<<"leftRotateforInsert"<<endl;
    RBNode *newNode_right = newNode->right;
    newNode->right = newNode_right->left;
    if (newNode->right != NULL)
        newNode->right->parent = newNode;
    newNode_right->parent = newNode->parent;

    if (newNode->parent == NULL)
        root = newNode_right;
    else if (newNode == newNode->parent->left)
        newNode->parent->left = newNode_right;
    else
        newNode->parent->right = newNode_right;

    newNode_right->left = newNode;
    newNode->parent = newNode_right;
}

void redBlack::rightRotateforInsert(RBNode *&root, RBNode *&newNode){
    //cout<<"rightRotateforInsert"<<endl;
    RBNode *newNode_left = newNode->left;
    newNode->left = newNode_left->right;
    if (newNode->left != NULL)
        newNode->left->parent = newNode;

    newNode_left->parent = newNode->parent;

    if (newNode->parent == NULL)
        root = newNode_left;
    else if (newNode == newNode->parent->left)
        newNode->parent->left = newNode_left;
    else
        newNode->parent->right = newNode_left;

    newNode_left->right = newNode;
    newNode->parent = newNode_left;
}

void redBlack::fixViolation(RBNode *&root, RBNode *&newNode){
    //cout<<"lets fix"<<endl;
    RBNode *parentNewNode = NULL;
    RBNode *gParentNewNode = NULL;

    while ((newNode != root) && (newNode->color != BLACK) &&
           (newNode->parent->color == RED)){

        parentNewNode = newNode->parent;
        gParentNewNode = newNode->parent->parent;

        /*  Case : A
            Parent of newNode is left child of Grand-parent of newNode */
        if (parentNewNode == gParentNewNode->left){
            RBNode *uncleNewNode = gParentNewNode->right;

            /* Case : 1 */
            if (uncleNewNode != NULL && uncleNewNode->color == RED){
                gParentNewNode->color = RED;
                parentNewNode->color = BLACK;
                uncleNewNode->color = BLACK;
                newNode = gParentNewNode;
            }

            else{
                /* Case : 2
                   newNode is right child of its parent
                   Left-rotation required */
                if (newNode == parentNewNode->right){
                    leftRotateforInsert(root, parentNewNode);
                    newNode = parentNewNode;
                    parentNewNode = newNode->parent;
                }
                rightRotateforInsert(root, gParentNewNode);
                swap(parentNewNode->color, gParentNewNode->color);
                newNode = parentNewNode;
            }
        }
        else{
            RBNode *uncleNewNode = gParentNewNode->left;

            if ((uncleNewNode != NULL) && (uncleNewNode->color == RED)){
                gParentNewNode->color = RED;
                parentNewNode->color = BLACK;
                uncleNewNode->color = BLACK;
                newNode = gParentNewNode;
            }
            else{
                if (newNode == parentNewNode->left){
                    rightRotateforInsert(root, parentNewNode);
                    newNode = parentNewNode;
                    parentNewNode = newNode->parent;
                }

                leftRotateforInsert(root, gParentNewNode);
                swap(parentNewNode->color, gParentNewNode->color);
                newNode = parentNewNode;
            }
        }
    }
    //mark root to black
    root->color = BLACK;
}

void redBlack:: printInOrder(){
  cout<<"RB Tree Inorder Traversal"<<endl;
  inorderHelper(root);
}

void redBlack:: inorderHelper(RBNode *root){
    if (root == NULL)
        return;

    inorderHelper(root->left);
    cout<<"color"<<" "<<root->color<<" ";
    root->dataNode->print();
    inorderHelper(root->right);
}

void redBlack:: fixRedRed(RBNode *theNode) {
    // if theNode is root color it black and return
    if (theNode == root) {
      theNode->color = BLACK;
      return;
    }

    // initialize parent, gParent, uncle
    RBNode *parent = theNode->parent, *gParent = parent->parent,
         *uncle = theNode->uncle();

    if (parent->color != BLACK) {
      if (uncle != NULL && uncle->color == RED) {
        // uncle red, perform recoloring and recurse
        parent->color = BLACK;
        uncle->color = BLACK;
        gParent->color = RED;
        fixRedRed(gParent);
      } else {
        // Else perform LR, LL, RL, RR
        if (parent->isOnLeft()) {
          if (theNode->isOnLeft()) {
            // for left right
            swap(parent->color, gParent->color);
          } else {
            leftRotateforDelete(parent);
            swap(theNode->color, gParent->color);
          }
          // for left left and left right
          rightRotateforDelete(gParent);
        } else {
          if (theNode->isOnLeft()) {
            // for right left
            rightRotateforDelete(parent);
            swap(theNode->color, gParent->color);
          } else {
            swap(parent->color, gParent->color);
          }

          // for right right and right left
          leftRotateforDelete(gParent);
        }
      }
    }
  }

void redBlack:: fixDoubleBlack(RBNode *theNode) {
      //theNode->print();
      if (theNode == root)
        // Reached root
        return;

      RBNode *sibling = theNode->sibling(), *parent = theNode->parent;
      if (sibling == NULL) {
        // No sibiling, double black pushed up
        fixDoubleBlack(parent);
      } else {
        if (sibling->color == RED) {
          // Sibling red
          parent->color = RED;
          sibling->color = BLACK;
          if (sibling->isOnLeft()) {
            // left case
            rightRotateforDelete(parent);
          } else {
            // right case
            leftRotateforDelete(parent);
          }
          fixDoubleBlack(theNode);
        } else {
          // Sibling black
          if (sibling->hasRedChild()) {
            // at least 1 red children
            if (sibling->left != NULL and sibling->left->color == RED) {
              if (sibling->isOnLeft()) {
                // left left
                sibling->left->color = sibling->color;
                sibling->color = parent->color;
                rightRotateforDelete(parent);
              } else {
                // right left
                sibling->left->color = parent->color;
                rightRotateforDelete(sibling);
                leftRotateforDelete(parent);
              }
            } else {
              if (sibling->isOnLeft()) {
                // left right
                sibling->right->color = parent->color;
                leftRotateforDelete(sibling);
                rightRotateforDelete(parent);
              } else {
                // right right
                sibling->right->color = sibling->color;
                sibling->color = parent->color;
                leftRotateforDelete(parent);
              }
            }
            parent->color = BLACK;
          } else {
            // 2 black children
            sibling->color = RED;
            if (parent->color == BLACK)
              fixDoubleBlack(parent);
            else
              parent->color = BLACK;
          }
        }
      }
    }

RBNode* redBlack:: successor(RBNode *theNode) {
    RBNode *temp = theNode;

    while (temp->left != NULL)
      temp = temp->left;

    return temp;
  }

RBNode* redBlack:: BSTreplace(RBNode *theNode) {
    // when node have 2 children
    if (theNode->left != NULL and theNode->right != NULL)
      return successor(theNode->right);

    // No successor for leaf node
    if (theNode->left == NULL and theNode->right == NULL)
      return NULL;

    // when single child
    if (theNode->left != NULL)
      return theNode->left;
    else
      return theNode->right;
  }

void redBlack:: swapLeft(RBNode* theNode, RBNode* y){
  if(theNode->left)
    theNode->left->parent = y;
  swap(theNode->left, y->left);
}

/*
 * This function will swap position of Nodes by
 * changing pointers and not data swapping
 */
void redBlack:: swapNodes(RBNode* theNode, RBNode* y){

  /*swapLeft;
  swapParent;
  swapRight;
  */

  if(theNode->left)
    theNode->left->parent = y;
  swap(theNode->left, y->left);

  if(theNode->parent){
    if(theNode->parent->left == theNode)
      theNode->parent->left = y;
    else
      theNode->parent->right = y;
  }
  if(y->parent->left == y){
    y->parent->left = theNode;
    swap(theNode->parent, y->parent);

    if(theNode->right && y->right)
        swap(theNode->right->parent, y->right->parent);
    else if(theNode->right)
        theNode->right->parent = y;
    else if(y->right)
        y->right->parent = theNode;
    swap(theNode->right, y->right);
  }else{
    if(y->right){
      y->right->parent = theNode;
      theNode->right = y->right;
    }else{
      theNode->right = NULL;
    }
    y->right = theNode;
    y->parent = theNode->parent;
    theNode->parent = y;
  }
}
/*
 * function to delete node from RB Tree
 */
void redBlack:: deleteNode(RBNode* theNode){
  if(theNode == NULL)
    return;
  RBNode *successor = BSTreplace(theNode);

      // True when u and v are both black
      bool uvBlack = ((successor == NULL or successor->color == BLACK) and (theNode->color == BLACK));
      RBNode *parent = theNode->parent;

      if (successor == NULL) {
        // successor is NULL therefore v is leaf
        if (theNode == root) {
          //cout<<"Delete case 1"<<endl;

          // v is root, making root null
          //cout<<"reached here";
          root = NULL;
        } else {
          //cout<<"Delete case 2"<<endl;
          if (uvBlack) {
            // u and v both black
            // v is leaf, fix double black at v
            fixDoubleBlack(theNode);
          } else {
            // successor or v is red
            if (theNode->sibling() != NULL)
              // sibling is not null, make it red"
              theNode->sibling()->color = RED;
          }

          // delete v from the tree
          if (theNode->isOnLeft()) {
            parent->left = NULL;
          } else {
            parent->right = NULL;
          }
        }
        delete theNode;
        return;
      }

      if (theNode->left == NULL or theNode->right == NULL) {

        // theNode has 1 child
        if (theNode == this->root) {
          //cout<<"Delete case 3"<<endl;

          // v is root, assign the value of successor to v,
          //theNode->dataNode = u->dataNode;
          //cout<<"Making u root"<<endl;
          theNode->left = theNode->right = NULL;
          this->root = successor;
          successor->parent = NULL;
          delete theNode;
          return;
        } else {
          //cout<<"Delete case 4";

          // Detach v from tree and move u up
          if (theNode->isOnLeft()) {
            parent->left = successor;
          } else {
            parent->right = successor;
          }
          delete theNode;
          successor->parent = parent;
          if (uvBlack) {
            //u->print();
            //cout<<" Fixing uvBlack"<<endl;
            // u and v both black, fix double black at u
            fixDoubleBlack(successor);
          } else {
            // u or v red, color u black
            successor->color = BLACK;
          }
        }
        return;
      }

      // theNode has 2 children, swap two nodes such that it changes all values with successor]

      //swap Nodes
      //cout<<"Delete case 5"<<endl;
      if(this->root == theNode)
        this->root = successor;
      swapNodes(theNode,successor);
      deleteNode(theNode);
}

void redBlack:: leftRotateforDelete(RBNode *theNode) {
    // new parent will be node's right child
    RBNode *nParent = theNode->right;

    // update root if current node is root
    if (theNode == root)
      root = nParent;

    theNode->moveDown(nParent);

    // connect theNode with new parent's left element
    theNode->right = nParent->left;
    // connect new parent's left element with node
    // if it is not null
    if (nParent->left != NULL)
      nParent->left->parent = theNode;

    // connect new parent with theNode
    nParent->left = theNode;
  }

void redBlack :: rightRotateforDelete(RBNode *theNode) {
    // new parent will be node's left child
    RBNode *nParent = theNode->left;

    // update root if current node is root
    if (theNode == root)
      root = nParent;

    theNode->moveDown(nParent);

    // connect theNode with new parent's right element
    theNode->left = nParent->right;
    // connect new parent's right element with node
    // if it is not null
    if (nParent->right != NULL)
      nParent->right->parent = theNode;

    // connect new parent with theNode
    nParent->right = theNode;
  }

void redBlack:: printBuilding(int buildingNum){
  search(this->root, buildingNum);
}

void redBlack:: search(RBNode *theNode, int buildingNum){
  if (theNode == NULL){
    cout<<"(0,0,0)"<<endl;
    return;
  }
  if(theNode->dataNode->getBuildingNum() == buildingNum){
      theNode->dataNode->print();
      cout<<endl;
  }
  else if (theNode->dataNode->getBuildingNum() > buildingNum){
      search(theNode->left, buildingNum);
  }
  else{
      search(theNode->right, buildingNum);
  }
}

void redBlack:: printBuildingRange(int lower, int upper){
  searchRange(this->root, lower, upper);
  cout<<endl;
}

void redBlack:: searchRange(RBNode *theNode, int lower, int upper){
  comma = 0;
  if (theNode == NULL){
    cout<<"(0,0,0)";
    return;
  }
  if (theNode->dataNode->getBuildingNum() > upper){
    searchRange(theNode->left, lower, upper);
  }else if(theNode->dataNode->getBuildingNum() < lower){
    searchRange(theNode->right, lower, upper);
  }else{
    rangeInorder(theNode, lower, upper);
  }
}

void redBlack:: rangeInorder(RBNode *root, int lower, int upper){
    if (root == NULL)
        return;
    if (root->dataNode->getBuildingNum() >= lower && root->dataNode->getBuildingNum() <= upper){
      rangeInorder(root->left, lower, upper);
      if(comma)
        cout<<",";
      root->dataNode->print();
      comma=1;
      rangeInorder(root->right, lower, upper);
    }
}

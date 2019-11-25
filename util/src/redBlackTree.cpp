#include "redBlackTree.h"
#include <iostream>
using namespace std;


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
  cout<<"color : "<<color<<" ";
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
    // If no parent or grandparent, then no uncle
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
    if (comparator == LESS){
        root->left  = BSTInsert(root->left, newNode);
        root->left->parent = root;
    }
    else{
        root->right = BSTInsert(root->right, newNode);
        root->right->parent = root;
    }
    return root;
}

void redBlack::rotateLeft(RBNode *&root, RBNode *&newNode){
    //cout<<"rotateLeft"<<endl;
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

void redBlack::rotateRight(RBNode *&root, RBNode *&newNode){
    //cout<<"rotateRight"<<endl;
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
    RBNode *grandParentNewNode = NULL;

    while ((newNode != root) && (newNode->color != BLACK) &&
           (newNode->parent->color == RED)){

        parentNewNode = newNode->parent;
        grandParentNewNode = newNode->parent->parent;

        /*  Case : A
            Parent of newNode is left child of Grand-parent of newNode */
        if (parentNewNode == grandParentNewNode->left){

            RBNode *uncleNewNode = grandParentNewNode->right;

            /* Case : 1
               The uncle of newNode is also red
               Only Recoloring required */
            if (uncleNewNode != NULL && uncleNewNode->color == RED){
                grandParentNewNode->color = RED;
                parentNewNode->color = BLACK;
                uncleNewNode->color = BLACK;
                newNode = grandParentNewNode;
            }

            else{
                /* Case : 2
                   newNode is right child of its parent
                   Left-rotation required */
                if (newNode == parentNewNode->right){
                    rotateLeft(root, parentNewNode);
                    newNode = parentNewNode;
                    parentNewNode = newNode->parent;
                }

                rotateRight(root, grandParentNewNode);
                swap(parentNewNode->color, grandParentNewNode->color);
                newNode = parentNewNode;
            }
        }
        else{
            RBNode *uncleNewNode = grandParentNewNode->left;

            if ((uncleNewNode != NULL) && (uncleNewNode->color == RED)){
                grandParentNewNode->color = RED;
                parentNewNode->color = BLACK;
                uncleNewNode->color = BLACK;
                newNode = grandParentNewNode;
            }
            else{
                if (newNode == parentNewNode->left){
                    rotateRight(root, parentNewNode);
                    newNode = parentNewNode;
                    parentNewNode = newNode->parent;
                }

                rotateLeft(root, grandParentNewNode);
                swap(parentNewNode->color, grandParentNewNode->color);
                newNode = parentNewNode;
            }
        }
    }

    root->color = BLACK;
    //root->dataNode->print();
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

void redBlack:: fixRedRed(RBNode *x) {
    // if x is root color it black and return
    if (x == root) {
      x->color = BLACK;
      return;
    }

    // initialize parent, grandparent, uncle
    RBNode *parent = x->parent, *grandparent = parent->parent,
         *uncle = x->uncle();

    if (parent->color != BLACK) {
      if (uncle != NULL && uncle->color == RED) {
        // uncle red, perform recoloring and recurse
        parent->color = BLACK;
        uncle->color = BLACK;
        grandparent->color = RED;
        fixRedRed(grandparent);
      } else {
        // Else perform LR, LL, RL, RR
        if (parent->isOnLeft()) {
          if (x->isOnLeft()) {
            // for left right
            swap(parent->color, grandparent->color);
          } else {
            leftRotate(parent);
            swap(x->color, grandparent->color);
          }
          // for left left and left right
          rightRotate(grandparent);
        } else {
          if (x->isOnLeft()) {
            // for right left
            rightRotate(parent);
            swap(x->color, grandparent->color);
          } else {
            swap(parent->color, grandparent->color);
          }

          // for right right and right left
          leftRotate(grandparent);
        }
      }
    }
  }

void redBlack:: fixDoubleBlack(RBNode *x) {
      if (x == root)
        // Reached root
        return;

      RBNode *sibling = x->sibling(), *parent = x->parent;
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
            rightRotate(parent);
          } else {
            // right case
            leftRotate(parent);
          }
          fixDoubleBlack(x);
        } else {
          // Sibling black
          if (sibling->hasRedChild()) {
            // at least 1 red children
            if (sibling->left != NULL and sibling->left->color == RED) {
              if (sibling->isOnLeft()) {
                // left left
                sibling->left->color = sibling->color;
                sibling->color = parent->color;
                rightRotate(parent);
              } else {
                // right left
                sibling->left->color = parent->color;
                rightRotate(sibling);
                leftRotate(parent);
              }
            } else {
              if (sibling->isOnLeft()) {
                // left right
                sibling->right->color = parent->color;
                leftRotate(sibling);
                rightRotate(parent);
              } else {
                // right right
                sibling->right->color = sibling->color;
                sibling->color = parent->color;
                leftRotate(parent);
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

RBNode* redBlack:: successor(RBNode *x) {
    RBNode *temp = x;

    while (temp->left != NULL)
      temp = temp->left;

    return temp;
  }

RBNode* redBlack:: BSTreplace(RBNode *x) {
    // when node have 2 children
    if (x->left != NULL and x->right != NULL)
      return successor(x->right);

    // when leaf
    if (x->left == NULL and x->right == NULL)
      return NULL;

    // when single child
    if (x->left != NULL)
      return x->left;
    else
      return x->right;
  }

void redBlack:: swapLeft(RBNode* x, RBNode* y){
  x->left->parent = y;
  swap(x->left, y->left);
}
void redBlack:: swapRight(RBNode* x, RBNode* y){
  if(x->right && y->right)
    swap(x->right->parent, y->right->parent);
  else if(x->right)
    x->right->parent = y;
  else if(y->right)
    y->right->parent = x;
  if(x->parent->left == x)
    swap(x->right, y->right);
  else{
    x->right = y->right;
    y->right = x;
  }
}
void redBlack:: swapParent(RBNode* x, RBNode* y){
  //RBNode *xParentChild = NULL, *yParentChild = NULL;
  if(x->parent){
    if(x->parent->left == x)
      x->parent->left = y;
    else
      x->parent->right = y;
  }
  if(y->parent->left == y){
    y->parent->left = x;
    swap(x->parent, y->parent);
  }else{
    x->parent = y;
  }
}

void redBlack:: swapNodes(RBNode* x, RBNode* y){
  /*
  //swap parents
    swapParent(x,y);
  //swap left
    swapLeft(x,y);
  //swap righ
    swapRight(x,y);
  */
  swapLeft(x,y);
  swapParent(x,y);
  swapRight(x,y);


}
void redBlack:: deleteNode(RBNode* v){
  RBNode *u = BSTreplace(v);

      // True when u and v are both black
      bool uvBlack = ((u == NULL or u->color == BLACK) and (v->color == BLACK));
      RBNode *parent = v->parent;

      if (u == NULL) {
        // u is NULL therefore v is leaf
        if (v == root) {
          // v is root, making root null
          root = NULL;
        } else {
          if (uvBlack) {
            // u and v both black
            // v is leaf, fix double black at v
            fixDoubleBlack(v);
          } else {
            // u or v is red
            if (v->sibling() != NULL)
              // sibling is not null, make it red"
              v->sibling()->color = RED;
          }

          // delete v from the tree
          if (v->isOnLeft()) {
            parent->left = NULL;
          } else {
            parent->right = NULL;
          }
        }
        delete v;
        return;
      }

      if (v->left == NULL or v->right == NULL) {
        // v has 1 child
        if (v == root) {
          // v is root, assign the value of u to v, and delete u
          v->dataNode = u->dataNode;
          v->left = v->right = NULL;
          delete u;
        } else {
          // Detach v from tree and move u up
          if (v->isOnLeft()) {
            parent->left = u;
          } else {
            parent->right = u;
          }
          delete v;
          u->parent = parent;
          if (uvBlack) {
            // u and v both black, fix double black at u
            fixDoubleBlack(u);
          } else {
            // u or v red, color u black
            u->color = BLACK;
          }
        }
        return;
      }

      // v has 2 children, swap values with successor and recurse
      //swap(u->dataNode, v->dataNode);

      //swap Nodes
      if(this->root == v)
        this->root = u;
      swapNodes(v,u);
      deleteNode(v);
}

void redBlack:: leftRotate(RBNode *x) {
    // new parent will be node's right child
    RBNode *nParent = x->right;

    // update root if current node is root
    if (x == root)
      root = nParent;

    x->moveDown(nParent);

    // connect x with new parent's left element
    x->right = nParent->left;
    // connect new parent's left element with node
    // if it is not null
    if (nParent->left != NULL)
      nParent->left->parent = x;

    // connect new parent with x
    nParent->left = x;
  }

void redBlack :: rightRotate(RBNode *x) {
    // new parent will be node's left child
    RBNode *nParent = x->left;

    // update root if current node is root
    if (x == root)
      root = nParent;

    x->moveDown(nParent);

    // connect x with new parent's right element
    x->left = nParent->right;
    // connect new parent's right element with node
    // if it is not null
    if (nParent->right != NULL)
      nParent->right->parent = x;

    // connect new parent with x
    nParent->right = x;
  }

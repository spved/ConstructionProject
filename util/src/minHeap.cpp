#include "minHeap.h"

heapNode:: heapNode(building* dataNode){
  this->dataNode = dataNode;
  this->RBPtr = NULL;
}

heapNode:: heapNode(building* dataNode, RBNode* RBPtr){
  this->dataNode = dataNode;
  this->RBPtr = RBPtr;
}

void heapNode:: updateRBPtr(RBNode* RBPtr){
  this->RBPtr = RBPtr;
}

RBNode* heapNode:: getRBPtr(){
  return this->RBPtr;
}

building* heapNode:: getBuilding(){
  return this->dataNode;
}

int minHeap:: parent(int i){
  return (i - 1) / 2;
}

int minHeap:: left(int i){
  return 2*i+1;
}

int minHeap:: right(int i){
  return 2*i+2;
}

int minHeap:: size(){
  return hNodes.size();
}

void minHeap:: heapifyUp(int index){
		// check if node at index i and its parent violates
		// the heap property
    int comparator = hNodes[index].dataNode->compareExecuteTime(hNodes[parent(index)].dataNode);
		if (index && comparator == LESS)
		{
			// swap the two if heap property is violated
			swap(hNodes[index], hNodes[parent(index)]);

			// call Heapify-up on the parent
			heapifyUp(parent(index));
		}
}

void minHeap:: heapifyDown(int index){
    int size = this->size();
		// get left and right child of node at index i
		int leftChild = left(index);
		int rightChild = right(index);

		int smallest = index;

		// compare A[i] with its left and right child
		// and find smallest value
    if(size > leftChild && LESS == hNodes[leftChild].dataNode->compareExecuteTime(hNodes[index].dataNode))
			smallest = leftChild;
    if(size > rightChild && LESS == hNodes[rightChild].dataNode->compareExecuteTime(hNodes[smallest].dataNode))
			smallest = rightChild;

		// swap with child having lesser value and
		// call heapify-down on the child
		if (smallest != index) {
			swap(hNodes[index], hNodes[smallest]);
			heapifyDown(smallest);
		}
	}

/* main functions */
void minHeap::insertNode(heapNode hNode){
  hNodes.push_back(hNode);

		// get element index and call heapify-up procedure
		int index = size() - 1;
		heapifyUp(index);
}

void minHeap:: removeMin(){
  //cout<<"Heap Size : "<<size();
  if (size() == 0){
		cout<<"Empty Heap";
    return;
  }
			// replace the root of the heap with the last element
			// of the vector
	hNodes[0] = hNodes.back();
  hNodes.pop_back();
	// call heapify-down on root node
	heapifyDown(0);
  //cout<<"Heap Size : "<<size();
}

heapNode minHeap:: getMin(){
  return hNodes[0];
}

void minHeap:: print(){
  cout<<"Min Heap: ";
  for(int i = 0; i<size(); i++){
    hNodes[i].dataNode->print();
    hNodes[i].RBPtr->print();
  }
}

bool minHeap:: isEmpty(){
  if(size() > 0)
    return false;
  return true;
}

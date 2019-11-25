/*
g++ -g -I util/include/ -c util/src/redBlackTree.cpp
g++ -g -I util/include/ -c util/src/building.cpp
g++ -g -I util/include/ -c util/src/minHeap.cpp
g++ -g -I util/include/ risingCity.cpp util/src/building.cpp util/src/redBlackTree.cpp -o risingCity minHeap.o
*/
#include <iostream>
#include <fstream>
#include "building.h"
#include "minHeap.h"
#include "redBlackTree.h"

#define INSERT "insert"
#define PRINT "print"

using namespace std;

void getData(string line, int &time, int &buildingNum, int &totalTime, string &operation){
  size_t current, previous = 0;
  string delim  = " ";
  current = line.find(delim);
  string temp[4];
  int i = 0;
  while (current != string::npos) {
      temp[i] = line.substr(previous, current - previous);
      previous = current + 1;
      current = line.find(delim, previous);
      i++;
  }
  temp[i] = line.substr(previous, current - previous);
  time = stoi(temp[0]);
  operation = temp[1];
  buildingNum = stoi(temp[2]);
  totalTime = stoi(temp[3]);
}

int main(int argc, char** argv){
  if(argc != 2 ){
    cout<<"Invalid Arguments"<<endl;
    exit(0);
  }
  string filename = argv[1];
  string line;
  ifstream inputFile;
  redBlack redBlackTree;
  RBNode *t;
  minHeap H;
  inputFile.open(filename);
  if (inputFile.is_open()){
    while ( getline (inputFile,line) ){
      int time, buildingNum, totalTime;
      string operation;
      if(line.length()>0){
        getData(line, time, buildingNum, totalTime, operation);
        building *x = new building(buildingNum, totalTime);
        x->print();
        RBNode *r = new RBNode(x);
        redBlackTree.insertNode(r);
        heapNode hN(x,r);
        H.insertNode(hN);
        t = r;
      }
    }
    H.getMin().getRBPtr()->print();
    cout<<"delete"<<endl;
    redBlackTree.deleteNode(H.getMin().getRBPtr());
    H.removeMin();
    H.print();
    cout<<"Next Delete: ";
    H.getMin().getRBPtr()->print();
    redBlackTree.deleteNode(H.getMin().getRBPtr());
    redBlackTree.printInOrder();
    H.print();
    H.removeMin();
    redBlackTree.deleteNode(H.getMin().getRBPtr());
    redBlackTree.printInOrder();
    H.print();
    H.removeMin();
    redBlackTree.deleteNode(H.getMin().getRBPtr());
    redBlackTree.printInOrder();
    H.print();
    H.removeMin();
    redBlackTree.deleteNode(H.getMin().getRBPtr());
    redBlackTree.printInOrder();
    H.print();
    H.removeMin();
    redBlackTree.deleteNode(H.getMin().getRBPtr());
    redBlackTree.printInOrder();
    H.print();
    H.removeMin();
    redBlackTree.deleteNode(H.getMin().getRBPtr());
    redBlackTree.printInOrder();
    H.print();
    H.removeMin();
    redBlackTree.deleteNode(H.getMin().getRBPtr());
    redBlackTree.printInOrder();
    H.print();
    H.removeMin();
    redBlackTree.deleteNode(H.getMin().getRBPtr());
    redBlackTree.printInOrder();
    H.print();
    H.removeMin();
    redBlackTree.printInOrder();
    H.print();
    inputFile.close();
  }
  else cout << "Unable to open file: "<<filename;
  return 0;

}

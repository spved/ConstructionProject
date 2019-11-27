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

#define INSERTOP "Insert"
#define PRINTOP "PrintBuilding"
#define COLON ":"
#define OPENBRACKET "("
#define CLOSEBRACKET ")"
#define COMMA ","

using namespace std;

enum Operation {INSERT, PRINTBUILDING, PRINTRANGE};
/*
File Input Format
0: Insert(50,20)
16: PrintBuilding(0,100)
*/

void getData(string line, int &time, int &num1, int &num2, int &operation){
  size_t current, previous = 0;
  string deling;
  num1 = -1;
  num2 = -1;

  //get counter
  current = line.find(COLON);
  time = stoi(line.substr(previous, current - previous));
  previous = current + 2;

  //get operation
  current = line.find(OPENBRACKET, previous);
  string tmpOperation = line.substr(previous, current - previous);
  previous = current + 1;
  cout<<tmpOperation<<" "<<INSERTOP;
  if(tmpOperation == INSERTOP){
    cout<<"Set Insert"<<endl;
    operation = INSERT;
  }else{
    operation = PRINTBUILDING;
  }

  //get buildingNum
  current = line.find(COMMA, previous);
  if(current != std::string::npos){
    num1 = stoi(line.substr(previous, current - previous));
    previous = current + 1;
    if(operation == PRINTBUILDING)
      operation = PRINTRANGE;
  }

  //read num2 or totalTime
  current = line.find(CLOSEBRACKET, previous);
  num2 = stoi(line.substr(previous, current - previous));
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
  RBNode *t, *r;
  building *x;
  minHeap H;
  inputFile.open(filename);
  if (inputFile.is_open()){
    while ( getline (inputFile,line) ){
      int time, num1, num2, operation;
      if(line.length()>0){
        cout<<line<<endl;
        getData(line, time, num1, num2, operation);
        cout<<time<<" "<<num1<<" "<<num2<<" "<<operation<<endl;
        switch (operation) {
          case INSERT:
            {
              x = new building(num1, num2);
              x->print();
              r = new RBNode(x);
              redBlackTree.insertNode(r);
              heapNode hN(x,r);
              H.insertNode(hN);
              t = r;
            }
            break;
          case PRINTBUILDING:
            redBlackTree.printBuilding(num2);
            break;
          case PRINTRANGE:
            redBlackTree.printBuildingRange(num1, num2);
            break;
        }
      }
    }
    
    H.getMin().getRBPtr()->print();
    cout<<"delete"<<endl;
    redBlackTree.deleteNode(H.getMin().getRBPtr());
    H.removeMin();
    H.print();
    cout<<"Find"<<endl;
    redBlackTree.printBuilding(23);
    redBlackTree.printBuilding(90);
    redBlackTree.printBuilding(88);
    cout<<"range 23-90"<<endl;
    redBlackTree.printBuildingRange(23, 90);
    inputFile.close();
  }
  else cout << "Unable to open file: "<<filename;
  return 0;

}

/*
g++ -g -I util/include/ -c util/src/redBlackTree.cpp
g++ -g -I util/include/ -c util/src/building.cpp
g++ -g -I util/include/ -c util/src/minHeap.cpp
g++ -g -I util/include/ risingCity.cpp util/src/building.cpp util/src/redBlackTree.cpp -o risingCity minHeap.o
*/
#include <cstdio>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "building.h"
#include "minHeap.h"
#include "redBlackTree.h"

#define INSERTOP "Insert"
#define PRINTOP "PrintBuilding"
#define COLON ":"
#define OPENBRACKET "("
#define CLOSEBRACKET ")"
#define COMMA ","

#define RUNCOUNTER 5

using namespace std;

static long global_counter;
enum Operation {INSERT, PRINTBUILDING, PRINTRANGE};
/*
File Input Format
0: Insert(50,20)
16: PrintBuilding(0,100)
*/
void performOp(int num1, int num2, int operation, redBlack *redBlackTree, minHeap *H){
  RBNode *r;
  building *x;


    //if global counter matches, perform the operation
    switch (operation) {
      case INSERT:
        {
          x = new building(num1, num2);
          r = new RBNode(x);
          redBlackTree->insertNode(r);
          heapNode hN(x,r);
          H->insertNode(hN);
        }
        break;
      case PRINTBUILDING:
        redBlackTree->printBuilding(num2);
        break;
      case PRINTRANGE:
        redBlackTree->printBuildingRange(num1, num2);
        break;
    }

}
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
  if(tmpOperation == INSERTOP){
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
  freopen("output.txt","w",stdout);
  string filename = argv[1];
  string line;
  ifstream inputFile;
  redBlack redBlackTree;
  minHeap H;

  bool readLine = true, isDataPresesnt = true;
  inputFile.open(filename);
  if (inputFile.is_open()){
    int time, num1, num2, operation;

    if(getline (inputFile,line)){
      if(line.length()>0){
        getData(line, time, num1, num2, operation);
        //cout<<time<<" "<<num1<<" "<<num2<<" "<<operation<<endl;
        performOp( num1, num2, operation, &redBlackTree, &H);

        global_counter++;
        while(isDataPresesnt || !H.isEmpty()){
        //cout<<line<<endl;
          //H.print();
          if(H.isEmpty()){
            if(readLine && isDataPresesnt){
              if(getline (inputFile,line)){
                if(line.length()>0)
                  //cout<<line<<endl;
                  getData(line, time, num1, num2, operation);
                }else{
                  isDataPresesnt = false;
                }
            }
            if(time > global_counter){
              readLine = false;
            }else if(time == global_counter){
              //cout<<global_counter<<endl;
              readLine = true;
              performOp( num1, num2, operation, &redBlackTree, &H);
            }
            global_counter++;
            continue;
          }
          heapNode currentWorking = H.getMin();
          H.removeMin();
          int runtime = min(RUNCOUNTER, currentWorking.getBuilding()->getTimeToComplete());

          for(int i = 0; i < runtime; i++){
            currentWorking.getBuilding()->updateExecutedTime(1);
            if(readLine && isDataPresesnt){
              if(getline (inputFile,line)){
                if(line.length()>0)
                  //cout<<line<<endl;
                  getData(line, time, num1, num2, operation);
                }else{
                  isDataPresesnt = false;
                }
            }
            if(time > global_counter){
              readLine = false;
            }else if(time == global_counter){
              readLine = true;
              performOp( num1, num2, operation, &redBlackTree, &H);
            }
            //increment executed getTime
            global_counter++;
          }//end of counter for

          if(currentWorking.getBuilding()->getTimeToComplete() == 0){
            //cout<<"completed : "<<global_counter-1<<" ";
            cout<<"("<<currentWorking.getBuilding()->getBuildingNum()<<","<<global_counter-1<<")"<<endl;
            //currentWorking.getRBPtr()->print();
            //cout<<endl;
            redBlackTree.deleteNode(currentWorking.getRBPtr());
            //H.print();
            //redBlackTree.ino
          }else{
            H.insertNode(currentWorking);
          }
        }//end of while
      }
    }//end of line present
    inputFile.close();
  }//end of is file open
  else cout << "Unable to open file: "<<filename;
  return 0;

}//end of main

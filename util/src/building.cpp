#include "building.h"
#include <iostream>
using namespace std;

building:: building (int buildingNum, int totalTime){
  this->buildingNum = buildingNum;
  this->totalTime = totalTime;
  this->executedTime = 0;
}

void building:: print(){
  cout<<"("<<buildingNum<<","<<executedTime<<","<<totalTime<<")";
}

void building:: updateExecutedTime(int executedTime){
  this->executedTime += executedTime;
}

int building:: compareBuildNum(building *a){
  if(this->buildingNum > a->buildingNum){
    return LARGE;
  }
  if(this->buildingNum < a->buildingNum){
    return LESS;
  }
  return EQUAL;
}

int building:: compareExecuteTime(building *a){
  if(this->executedTime > a->executedTime){
    return LARGE;
  }
  if(this->executedTime < a->executedTime){
    return LESS;
  }

  /* will reach here if executedTime are same*/
  if(this->buildingNum > a->buildingNum){
    return LARGE;
  }
  if(this->buildingNum < a->buildingNum){
    return LESS;
  }
  return EQUAL;
}

int building:: getBuildingNum(){
  return this->buildingNum;
}

int building:: getTimeToComplete(){
  return this->totalTime - this->executedTime;
}

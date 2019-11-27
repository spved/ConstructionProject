#ifndef __BUILDING__
#define __BUILDING__

enum Comparator{LESS, LARGE, EQUAL};

class building{
private:
  int buildingNum;
  int executedTime;
  int totalTime;

  //friend class minHeap;
public:
  building(int buildingNum, int totalTime);
  void print();
  void updateExecutedTime(int executedTime);
  int compareBuildNum(building *);
  int compareExecuteTime(building *);
  int getBuildingNum();
};

#endif

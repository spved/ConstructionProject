CC=g++
CFLAGS=-g -I
INCLUDES=util/include
SRC=util/src
all: minHeap.o \
	risingCity.o

minHeap.o: util/src/minHeap.cpp 
	$(CC) $(CFLAGS) $(INCLUDES) -c util/src/minHeap.cpp

risingCity.o: risingCity.cpp $(SRC)/building.cpp $(SRC)/redBlackTree.cpp 
	$(CC) $(CFLAGS) $(INCLUDES) risingCity.cpp $(SRC)/building.cpp $(SRC)/redBlackTree.cpp -o risingCity minHeap.o

clean:
	rm *.o

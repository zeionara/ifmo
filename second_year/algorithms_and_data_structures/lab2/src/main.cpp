#include <stdio.h>
#include <string.h>
#include <fstream>
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

#define HEAP_SIZE_DEFAULT 0x8000

typedef struct _PriorityQueueRecord{
  DWORD name;
  DWORD key;
} PriorityQueueRecord, *PriorityQueueRecordPointer;

typedef struct _GraphAdjRecord GraphAdjRecord, *GraphAdjRecordPointer;

typedef struct _GraphAdjRecord{
  DWORD name;
  DWORD weight;
  GraphAdjRecordPointer next;
} GraphAdjRecord, *GraphAdjRecordPointer;

//
//
//Graph Generating Methods
//
//

bool wasTheConnection(GraphAdjRecordPointer graphAdjRecord, DWORD vertexName){
  while (graphAdjRecord != NULL){
    if (graphAdjRecord->name == vertexName) return true;
    graphAdjRecord = graphAdjRecord->next;
  }
  return false;
}

GraphAdjRecordPointer generateGraphAdj(HANDLE hGraphAdjHeap, DWORD graphSize, DWORD graphDensity, DWORD minWeight, DWORD maxWeight){
  GraphAdjRecordPointer graphAdj = (GraphAdjRecordPointer)HeapAlloc(hGraphAdjHeap, HEAP_ZERO_MEMORY, graphSize*sizeof(GraphAdjRecord));
  GraphAdjRecordPointer currentAdjRecord = graphAdj;
  DWORD vertexName = 0;
  srand(time(NULL));
  for (DWORD i = 0; i < graphSize; i++){  // for each v
    currentAdjRecord = &graphAdj[i];
    currentAdjRecord->next = NULL;
    if (graphDensity == 0) continue;
    vertexName = i;
    while ((vertexName == i) || (wasTheConnection(&graphAdj[i],vertexName))) vertexName = rand() % (graphSize);
    currentAdjRecord->weight = rand() % (maxWeight - minWeight) + minWeight;
    currentAdjRecord->name = vertexName;
    for (DWORD j = 0; j < graphDensity - 1; j++){
      currentAdjRecord->next = (GraphAdjRecordPointer)HeapAlloc(hGraphAdjHeap, HEAP_ZERO_MEMORY, sizeof(GraphAdjRecord));
      currentAdjRecord = currentAdjRecord->next;
      vertexName = i;
      while ((vertexName == i) || (wasTheConnection(&graphAdj[i],vertexName))) vertexName = rand() % (graphSize);
      currentAdjRecord->weight = rand() % (maxWeight - minWeight) + minWeight;
      currentAdjRecord->name = vertexName;
      currentAdjRecord->next = NULL;
    }
  }
  return graphAdj;
}

int showGraph(GraphAdjRecordPointer graphAdj, DWORD graphSize, DWORD graphDensity){
  GraphAdjRecordPointer currentAdjRecord = graphAdj;
  for (int i = 0; i < graphSize; i++){
    currentAdjRecord = &graphAdj[i];
    cout << "Vertex " << i << " : " << endl;
    for (int i = 0; i < graphDensity; i++){
      cout << "  ";
      cout << currentAdjRecord->name << " with weight " << currentAdjRecord->weight << endl;
      currentAdjRecord = currentAdjRecord->next;
    }
  }
  return 0;
}

//
//
//Priority Queue Methods
//
//

int showChilds(PriorityQueueRecordPointer priorityQueue, DWORD recordIndex, DWORD queueLength, int queueWidth){
  if (recordIndex >= queueLength) return 0;
  DWORD numOfSpaces = recordIndex;
  while (numOfSpaces > 0){
    cout << "        ";
    numOfSpaces = (numOfSpaces-1)/queueWidth;
  }
  cout << "Name = " << priorityQueue[recordIndex].name << " Key = " << priorityQueue[recordIndex].key << endl;
  DWORD childIndex = recordIndex*queueWidth + 1;
  DWORD childMaxIndex = (recordIndex+1)*queueWidth;
  for (DWORD childIndex = recordIndex*queueWidth + 1; childIndex <= (recordIndex+1)*queueWidth; childIndex++)
    showChilds(priorityQueue, childIndex, queueLength, queueWidth);
  return 0;
}

int showPriorityQueue(PriorityQueueRecordPointer priorityQueue,DWORD queueLength,int queueWidth){
  showChilds(priorityQueue, 0, queueLength, queueWidth);
  return 0;
}

PriorityQueueRecordPointer generatePriorityQueue(HANDLE hPriorityQueueHeap, DWORD queueLength, int minName, int maxName, int minKey, int maxKey){
  PriorityQueueRecordPointer priorityQueue = (PriorityQueueRecordPointer)HeapAlloc(hPriorityQueueHeap, HEAP_ZERO_MEMORY, queueLength*sizeof(PriorityQueueRecord));
  srand(time(NULL));
  for (int i = 0; i < queueLength; i++){
    priorityQueue[i].name = rand() % (maxName - minName) + minName;
    priorityQueue[i].key = rand() % (maxKey - minKey) + minKey;
  }
  return priorityQueue;
}

DWORD firstChildIndex(DWORD queueLength, int queueWidth, DWORD recordIndex){
  DWORD firstChildIndex = recordIndex*queueWidth + 1;
  if (firstChildIndex > queueLength) return queueLength;
  return firstChildIndex;
}

DWORD lastChildIndex(DWORD queueLength, int queueWidth, DWORD recordIndex){
  DWORD firstChildId = firstChildIndex(queueLength, queueWidth, recordIndex);
  if (firstChildId == queueLength) return queueLength;
  DWORD lastChildIndex = firstChildId + queueWidth - 1;
  if (lastChildIndex > queueLength) return queueLength;
  return lastChildIndex;
}

DWORD minChildIndex(DWORD queueLength, int queueWidth, DWORD recordIndex, PriorityQueueRecordPointer priorityQueue){ // asymptotically O(d)
  DWORD firstChildId = firstChildIndex(queueLength, queueWidth, recordIndex);
  if (firstChildId == queueLength) return queueLength;
  DWORD lastChildId = lastChildIndex(queueLength, queueWidth, recordIndex);
  DWORD minChildId = firstChildId;
  for (int i = firstChildId+1; i <= lastChildId; i++){  // gives O(d)
    if (priorityQueue[minChildId].key > priorityQueue[i].key){
      minChildId = i;
    }
  }
  return minChildId;
}

DWORD parentIndex(DWORD queueLength, int queueWidth, DWORD recordIndex){
  if (recordIndex == 0) return 0;
  return (recordIndex - 1)/ queueWidth;
}

int moveDown(DWORD queueLength, int queueWidth, DWORD recordIndex, PriorityQueueRecordPointer priorityQueue, LPDWORD indexes){// asymptotically O(dlog(n))
  DWORD recordKey = priorityQueue[recordIndex].key;
  DWORD recordName = priorityQueue[recordIndex].name;

  DWORD minChildId = minChildIndex(queueLength, queueWidth, recordIndex, priorityQueue);
  if (!((minChildId != queueLength) && (recordKey > priorityQueue[minChildId].key))) return 0;
  while ((minChildId != queueLength) && (recordKey > priorityQueue[minChildId].key)){ // gives log(n)
      priorityQueue[recordIndex].key = priorityQueue[minChildId].key;
      priorityQueue[recordIndex].name = priorityQueue[minChildId].name;
      indexes[priorityQueue[recordIndex].name] = recordIndex;
      recordIndex = minChildId;
      minChildId = minChildIndex(queueLength, queueWidth, recordIndex, priorityQueue); //gives d
  }

  priorityQueue[recordIndex].key = recordKey;
  priorityQueue[recordIndex].name = recordName;

  indexes[priorityQueue[recordIndex].name] = recordIndex;

  return 0;
}

int moveUp(DWORD queueLength, int queueWidth, DWORD recordIndex, PriorityQueueRecordPointer priorityQueue, LPDWORD indexes){// asymptotically O(log(n))
  DWORD recordKey = priorityQueue[recordIndex].key;
  DWORD recordName = priorityQueue[recordIndex].name;
  DWORD parentId = parentIndex(queueLength, queueWidth, recordIndex);
  DWORD childIndex = recordIndex;

  if (!((parentId != 0) && (priorityQueue[parentId].key > recordKey))) return 0;
  while ((parentId != 0) && (priorityQueue[parentId].key > recordKey)){ // gives log(n)
    childIndex = recordIndex;
    priorityQueue[recordIndex].key = priorityQueue[parentId].key;
    priorityQueue[recordIndex].name = priorityQueue[parentId].name;
    indexes[priorityQueue[recordIndex].name] = recordIndex;
    recordIndex = parentId;
    parentId = parentIndex(queueLength, queueWidth, recordIndex);

    //cout << "moved---" << endl;
    //showPriorityQueue(priorityQueue, queueLength, queueWidth);
    //cout << "next will be " << priorityQueue[parentId].key << " and our " << recordKey << endl;
    //cout << "record Index = " << recordIndex << endl;
  }
  /*if (priorityQueue[recordIndex].key <= recordKey){
    priorityQueue[childIndex].key = recordKey;
    priorityQueue[childIndex].name = recordName;

    indexes[priorityQueue[childIndex].name] = childIndex;
    return 0;
  };*/

  priorityQueue[recordIndex].key = priorityQueue[parentId].key;
  priorityQueue[recordIndex].name = priorityQueue[parentId].name;
  indexes[priorityQueue[recordIndex].name] = recordIndex;

  if (priorityQueue[parentId].key > recordKey){
    priorityQueue[parentId].key = recordKey;
    priorityQueue[parentId].name = recordName;
    indexes[priorityQueue[parentId].name] = parentId;
  } else {
    priorityQueue[recordIndex].key = recordKey;
    priorityQueue[recordIndex].name = recordName;
    indexes[priorityQueue[recordIndex].name] = recordIndex;
  }


  return 0;
}

PriorityQueueRecord takeMininum(DWORD queueLength, int queueWidth, PriorityQueueRecordPointer priorityQueue, LPDWORD indexes){ // asymptotically O(dlog(n))
  PriorityQueueRecord minRecord;
  minRecord.key = priorityQueue[0].key;
  minRecord.name = priorityQueue[0].name;
  indexes[priorityQueue[0].name] = queueLength - 1;
  priorityQueue[0].key = priorityQueue[queueLength - 1].key;
  priorityQueue[0].name = priorityQueue[queueLength - 1].name;
  indexes[priorityQueue[0].name] = 0;

  priorityQueue[queueLength - 1].key = minRecord.key;
  priorityQueue[queueLength - 1].name = minRecord.name;
  if (queueLength == 0) return minRecord;
  if (queueLength - 1 > 1) moveDown(queueLength - 1, queueWidth, 0, priorityQueue, indexes); // gives O(dlog(n))
  return minRecord;
}

int makePriorityQueue(DWORD queueLength, int queueWidth, PriorityQueueRecordPointer priorityQueue, LPDWORD indexes){// asymptotically O(n)
  for (int recordIndex = queueLength - 1; recordIndex >= 0; recordIndex--){// gives O(n)
    moveDown(queueLength, queueWidth, recordIndex, priorityQueue, indexes);// gives O(dlog(n))
  }
  return 0;
}

//
//
//Dijkstra algorythm methods
//
//
int showArr(LPDWORD arr, DWORD length){
  for (int i = 0; i < length; i++){
    cout << " " << arr[i];
  }
  cout << endl;
  return 0;
}

int findShortestWays(DWORD numberOfVertexes, DWORD queueWidth, DWORD startVertex, GraphAdjRecordPointer graphAdj, //asymptotically O((n+m)logn)
                    LPDWORD distances, LPDWORD vertexes, LPDWORD indexes, PriorityQueueRecordPointer priorityQueue){
  for (int i = 0; i < numberOfVertexes; i++){
    distances[i] = 0xffffff;
    vertexes[i] = numberOfVertexes;
    indexes[i] = i; // vertex with name i at the index i (on it's place)
    priorityQueue[i].name = i;
    priorityQueue[i].key = 0xffffff;
  }

  priorityQueue[startVertex].key = 0; // current evaluation of shortest path to the start vertex gives 0 length (because it's beginning of a route)
  DWORD numberOfUncheckedVertexes = numberOfVertexes; // no one vertex checked at the moment
  makePriorityQueue(numberOfVertexes, queueWidth, priorityQueue, indexes);  // move start vertex to the top (after that vertex with name s has index 0)

  PriorityQueueRecord minRecord;  // here we will extract vertex with shortest path to that
  DWORD nameOfMinimalVertex;  // here we will keep the name of the vertex with shortest path to that
  GraphAdjRecordPointer linkedVertexAdjRecord; // temporary variable for keeping vertex linked with minimal
  GraphAdjRecordPointer tmpl;
  DWORD nameOfLinkedVertex; // temporary variable for keeping linked vertex's name
  DWORD indexOfLinkedVertexInPriorityQueue; // index in priority queue and name are different (for example, vertex s now has index 0, so index[s]=0)
  while (numberOfUncheckedVertexes > 0){  // while there are unchecked vertexes (gives O(n))
    //showArr(indexes, numberOfVertexes);
    //showPriorityQueue(priorityQueue,numberOfUncheckedVertexes,queueWidth);

    minRecord = takeMininum(numberOfUncheckedVertexes, queueWidth, priorityQueue, indexes);  // extract vertex with minimal path to that from the s (gives O(dlogn))

    //showArr(indexes, numberOfVertexes);
    //showPriorityQueue(priorityQueue,numberOfUncheckedVertexes,queueWidth);
    numberOfUncheckedVertexes--;

    nameOfMinimalVertex = minRecord.name; // save name of minimal vertex in a temporary variable
    //cout << "take vertex " << nameOfMinimalVertex << " having " << minRecord.key << endl;
    //cout << "Select " << nameOfMinimalVertex << " and " << minRecord.key << endl;
    distances[nameOfMinimalVertex] = minRecord.key; // update shortest path to minimal vertex in result array
    linkedVertexAdjRecord = &graphAdj[nameOfMinimalVertex];// take first linked vertex in list of vertex with minimal path to that from the s
    if (linkedVertexAdjRecord->weight == 0) continue;
    while (linkedVertexAdjRecord != NULL){ // while there are linked vertexes (gives O(m/n))

      nameOfLinkedVertex = linkedVertexAdjRecord->name; // save name of linked vertex
      //cout << "take it's linked " << nameOfLinkedVertex << endl;
      //cout << "Watch " << nameOfLinkedVertex << endl;
      indexOfLinkedVertexInPriorityQueue = indexes[nameOfLinkedVertex]; // save index of linked vertex in priority queue
      //cout << indexOfLinkedVertexInPriorityQueue << endl;
      //showPriorityQueue(priorityQueue,numberOfVertexes,queueWidth);
      if (distances[nameOfMinimalVertex] >= 0xffffff){
        linkedVertexAdjRecord = linkedVertexAdjRecord->next;
        continue;
      }
      if (priorityQueue[indexes[nameOfLinkedVertex]].key > distances[nameOfMinimalVertex] + linkedVertexAdjRecord->weight){
          // if the known minimal length of path to the linked vertex more than one which we can make if will go through current minimal vertex
          priorityQueue[indexOfLinkedVertexInPriorityQueue].key = distances[nameOfMinimalVertex] + linkedVertexAdjRecord->weight; // decrease length of path
          //showPriorityQueue(priorityQueue, numberOfVertexes, queueWidth);
          //cout << "before moving up" << endl;
          //showPriorityQueue(priorityQueue, numberOfVertexes, queueWidth);
          moveUp(numberOfUncheckedVertexes, queueWidth, indexOfLinkedVertexInPriorityQueue, priorityQueue, indexes); // and move it upper if possibly (gives O(logn))
          //cout << "after moving up" << endl;
          //showPriorityQueue(priorityQueue, numberOfVertexes, queueWidth);
          //showPriorityQueue(priorityQueue, numberOfVertexes, queueWidth);

          vertexes[nameOfLinkedVertex] = nameOfMinimalVertex;

        }

        linkedVertexAdjRecord = linkedVertexAdjRecord->next;

    }

  }
  return 0;
}

int findShortestWaysByMarks(DWORD numberOfVertexes, DWORD queueWidth, DWORD startVertex, GraphAdjRecordPointer graphAdj, LPDWORD distances, LPDWORD vertexes, DWORD graphDensity){
  LPDWORD concludings = (LPDWORD)malloc(numberOfVertexes*sizeof(DWORD)); //concludings[i] shows is shortest path builded for the vertex i
  for (int i = 0; i < numberOfVertexes; i++){
    distances[i] = 0xffffff;
    vertexes[i] = numberOfVertexes;
    concludings[i] = 0;
  }
  distances[startVertex] = 0;
  DWORD numberOfUncheckedVertexes = numberOfVertexes; // no one vertex checked at the moment
  DWORD nameOfFirstUncheckedVertex;
  DWORD nameOfOneUncheckedVertex;
  DWORD nameOfAnotherUncheckedVertex;
  DWORD nameOfLinkedVertex;
  GraphAdjRecordPointer linkedVertexAdjRecord;
  while (numberOfUncheckedVertexes > 0){  // while there are unchecked vertexes (gives O(n))

    nameOfFirstUncheckedVertex = 0;
    while (concludings[nameOfFirstUncheckedVertex] != 0) nameOfFirstUncheckedVertex++;
    nameOfOneUncheckedVertex = nameOfFirstUncheckedVertex;
    for (DWORD nameOfAnotherUncheckedVertex = nameOfOneUncheckedVertex + 1; nameOfAnotherUncheckedVertex < numberOfVertexes; nameOfAnotherUncheckedVertex++){
      if (concludings[nameOfAnotherUncheckedVertex] == 0){
        if (distances[nameOfOneUncheckedVertex] > distances[nameOfAnotherUncheckedVertex]){
          nameOfOneUncheckedVertex = nameOfAnotherUncheckedVertex;
        }
      }
    }
    //after O(n) got name of unchecked vertex having minimal distance
    concludings[nameOfOneUncheckedVertex] = 1;
    numberOfUncheckedVertexes--;
    linkedVertexAdjRecord = &graphAdj[nameOfOneUncheckedVertex];// take first linked vertex in list of vertex with minimal path to that from the s
    if (linkedVertexAdjRecord->weight == 0) continue;
    while (linkedVertexAdjRecord != NULL){
      nameOfLinkedVertex = linkedVertexAdjRecord->name;
      if (concludings[nameOfLinkedVertex] == 0){
        if (distances[nameOfLinkedVertex] > distances[nameOfOneUncheckedVertex] + linkedVertexAdjRecord->weight){
          distances[nameOfLinkedVertex] = distances[nameOfOneUncheckedVertex] + linkedVertexAdjRecord->weight;
          vertexes[nameOfLinkedVertex] = nameOfOneUncheckedVertex;
          //showArr(distances, numberOfVertexes);
        }
      }
      linkedVertexAdjRecord = linkedVertexAdjRecord->next;
    }
  }
  return 0;
}

//
//
// Common methods
//
//

int main(int argc, char* argv[]){


  //ofstream out("log.txt");
  //cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

  int queueWidth = 2;
  DWORD graphSize = 100;
  DWORD graphDensity = 5;
  DWORD queueLength = graphSize;

  DWORD numberOfVertexes = 25;
  DWORD maxNumberOfEdges = 500;
  DWORD minNumberOfEdges = 0;
  DWORD stepNumberOfEdges = 25;

  HANDLE hPriorityQueueHeap = HeapCreate(HEAP_GENERATE_EXCEPTIONS | HEAP_NO_SERIALIZE, numberOfVertexes*sizeof(PriorityQueueRecord)+1, 0);

  LPDWORD indexes = (LPDWORD)malloc(numberOfVertexes*sizeof(DWORD));
  LPDWORD distances = (LPDWORD)malloc(numberOfVertexes*sizeof(DWORD));
  LPDWORD vertexes = (LPDWORD)malloc(numberOfVertexes*sizeof(DWORD));
  HANDLE hGraphAdjHeap;
  float ffTimeStart = clock()/(float)CLOCKS_PER_SEC;
  float ffTimeStop;
  float fTimeStart = 0;
  float fTimeStop = 0;
  float fTimeMiddle = 0;
  for (DWORD numberOfEdges = minNumberOfEdges; numberOfEdges < maxNumberOfEdges; numberOfEdges += stepNumberOfEdges){
    graphDensity = numberOfEdges / numberOfVertexes;
    hGraphAdjHeap = HeapCreate(HEAP_GENERATE_EXCEPTIONS | HEAP_NO_SERIALIZE, numberOfEdges*sizeof(GraphAdjRecord)+1, 0);

    GraphAdjRecordPointer graphAdj = generateGraphAdj(hGraphAdjHeap, numberOfVertexes, graphDensity, 1, 1000000);

    //showGraph(graphAdj, graphSize, graphDensity)
    PriorityQueueRecordPointer priorityQueue = generatePriorityQueue(hPriorityQueueHeap, numberOfVertexes, 0, numberOfVertexes, 0, 10);
    makePriorityQueue(numberOfVertexes,4,priorityQueue,indexes);
    //showGraph(graphAdj, numberOfVertexes, graphDensity);
    fTimeStart = clock()/(float)CLOCKS_PER_SEC;
    findShortestWays(numberOfVertexes, queueWidth, 2, graphAdj, distances, vertexes, indexes, priorityQueue);
    showArr(distances, numberOfVertexes);
    fTimeMiddle = clock()/(float)CLOCKS_PER_SEC;
    findShortestWaysByMarks(numberOfVertexes, queueWidth, 2, graphAdj, distances, vertexes, graphDensity);
    showArr(distances, numberOfVertexes);
    fTimeStop = clock()/(float)CLOCKS_PER_SEC;
    cout << numberOfEdges << "\t" << fTimeMiddle - fTimeStart << "\t" << fTimeStop - fTimeMiddle << endl;
    if (hGraphAdjHeap != NULL) HeapDestroy(hGraphAdjHeap);
  }
  ffTimeStop = clock()/(float)CLOCKS_PER_SEC;
  cout << " Finished in " << ffTimeStop - ffTimeStart << "secs " << endl;
}

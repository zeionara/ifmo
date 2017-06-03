#include <stdio.h>
#include <string.h>
#include <fstream>
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <sstream>
using namespace std;

#define HEAP_SIZE_DEFAULT 0x8000


typedef struct _QueueRecord QueueRecord, *QueueRecordPointer;
typedef struct _GraphAdjRecord GraphAdjRecord, *GraphAdjRecordPointer;

typedef struct _GraphAdjRecord{
  unsigned name;
  GraphAdjRecordPointer next;
} GraphAdjRecord, *GraphAdjRecordPointer;

typedef struct _QueueRecord{
  unsigned name;
  QueueRecordPointer next;
  QueueRecordPointer prev;
} QueueRecord, *QueueRecordPointer;

typedef struct _Path{
  int length;
  int* values;
} Path, *PathPointer;

int showArr(int* arr, int length){
  for (int i = 0; i <= length; i++){
    cout << " " << arr[i];
  }
  cout << endl;
  return 0;
}

void enqueue (QueueRecordPointer* queueStart, QueueRecordPointer* queueEnd, int value){
  cout << "start enqueue for" << value << endl;
  QueueRecordPointer newQueueRecord = (QueueRecordPointer)malloc(sizeof(QueueRecord));
  newQueueRecord->name = value;
  newQueueRecord->next = NULL;
  newQueueRecord->prev = (*queueEnd);
  if ((*queueEnd) != NULL) (*queueEnd)->next = newQueueRecord; else (*queueStart) = newQueueRecord;
  (*queueEnd) = newQueueRecord;
  cout << "end enqueue for " << value << endl;
}

int dequeue (QueueRecordPointer* queueStart, QueueRecordPointer* queueEnd){
  cout << "start dequeue" << endl;
  QueueRecordPointer firstQueueRecord = (*queueStart);
  int value = firstQueueRecord->name;
  (*queueStart) = firstQueueRecord->next;
  if ((*queueStart) != NULL) (*queueStart)->prev = NULL; else (*queueEnd) = NULL;
  cout << "end dequeue" << endl;
  return value;
}

void addNewEdge(string pair, GraphAdjRecordPointer graphAdj){
  int spacePosition = pair.find(' ');
  int firstVertex = atoi(pair.substr(0,spacePosition).c_str());
  int secondVertex = atoi(pair.substr(spacePosition + 1,pair.length() - spacePosition).c_str());
  GraphAdjRecordPointer last = &graphAdj[firstVertex];
  while (last->next != NULL) last = last->next;
  last->next = (GraphAdjRecordPointer)malloc(sizeof(GraphAdjRecord));
  last = last->next;
  last->name = secondVertex;
  last->next = NULL;
}

int showGraph(GraphAdjRecordPointer graphAdj, unsigned numberOfVertexes){
  GraphAdjRecordPointer currentAdjRecord = graphAdj;
  for (int i = 1; i <= numberOfVertexes; i++){
    currentAdjRecord = &graphAdj[i];
    cout << "Vertex " << i << " : ";
    if (currentAdjRecord->next == NULL){ cout << endl; continue;}
    do{
      currentAdjRecord = currentAdjRecord->next;
      cout << "  " << currentAdjRecord->name;
    } while(currentAdjRecord->next != NULL);
    cout << endl;
  }
  return 0;
}

bool BreadthFirstSearch(short* color, int* predecessor, int numberOfVertexes, GraphAdjRecordPointer graphAdj, int startVertex, int endVertex){
  for (int i = 0; i <= numberOfVertexes; i++){
    color[i] = 0;
    predecessor[i] = 0;
  }
  color[startVertex] = 1;
  QueueRecordPointer queueStart = NULL;
  QueueRecordPointer queueEnd = NULL;
  enqueue(&queueStart, &queueEnd, startVertex);
  int exploringVertex;
  GraphAdjRecordPointer connectedVertex;
  cout << "Want to find "<<endVertex << " from " << startVertex << endl;
  while (queueEnd != NULL){
    exploringVertex = dequeue(&queueStart, &queueEnd);
    cout << "exploring " << exploringVertex << "..." << endl;
    connectedVertex = graphAdj[exploringVertex].next;
    while (connectedVertex != NULL){
      if (color[connectedVertex->name] == 0){
        color[connectedVertex->name] = 1;
        predecessor[connectedVertex->name] = exploringVertex;
        if (connectedVertex->name == endVertex) return true;
        enqueue(&queueStart, &queueEnd, connectedVertex->name);
      }
      connectedVertex = connectedVertex->next;
    }
    cout << "finished exploring" << endl;
    color[exploringVertex] = 2;
  }
  return false;
}

PathPointer findPath(GraphAdjRecordPointer graphAdj, int numberOfVertexes, int startVertex, int endVertex, int midVertex, int numberOfEdges){
  short* color = (short*)malloc((numberOfVertexes + 1) * sizeof(short));
  int* predecessor = (int*)malloc((numberOfVertexes + 1) * sizeof(int));

  bool result = BreadthFirstSearch(color, predecessor, numberOfVertexes, graphAdj, midVertex, endVertex);
  if (result == false) return NULL;
  showArr(predecessor, numberOfVertexes);

  int pathVertexIndex = 0;
  int currentPathVertex = endVertex;
  PathPointer path = (PathPointer)malloc(sizeof(PathPointer));
  path->values = (int*)malloc(numberOfEdges * sizeof(int));

  while (currentPathVertex != 0){
    path->values[pathVertexIndex] = currentPathVertex;
    pathVertexIndex++;
    currentPathVertex = predecessor[currentPathVertex];
  }

  result = BreadthFirstSearch(color, predecessor, numberOfVertexes, graphAdj, startVertex, midVertex);
  if (result == false) return NULL;
  showArr(predecessor, numberOfVertexes);

  currentPathVertex = predecessor[midVertex];

  while (currentPathVertex != 0){
    path->values[pathVertexIndex] = currentPathVertex;
    pathVertexIndex++;
    currentPathVertex = predecessor[currentPathVertex];
  }

  cout << pathVertexIndex << endl;

  path->length = pathVertexIndex;

  return path;
}

int main(int argc, char* argv[]){

  //
  // Parsing file
  //

  string readStr;
  ifstream file("path.in");

  getline(file, readStr);
  int numberOfVertexes = atoi(readStr.c_str());

  getline(file, readStr);
  int numberOfEdges = atoi(readStr.c_str());

  GraphAdjRecordPointer graphAdj = ( GraphAdjRecordPointer )malloc( (numberOfVertexes + 1) * sizeof(GraphAdjRecord) );

  for (int i = 0; i <= numberOfVertexes; i++){
    graphAdj[i].next = NULL;
    graphAdj[i].name = 0;
  }

  for (int i = 0; i < numberOfEdges; i++) { getline(file, readStr); addNewEdge(readStr, graphAdj); }

  showGraph(graphAdj, numberOfVertexes);

  getline(file, readStr);

  file.close();

  int firstSpacePosition = readStr.find(' ');
  int secondSpacePosition = readStr.find(' ', firstSpacePosition + 1);

  int startVertex = atoi(readStr.substr(0,firstSpacePosition).c_str());
  int endVertex = atoi(readStr.substr(firstSpacePosition + 1,secondSpacePosition - firstSpacePosition - 1).c_str());
  int midVertex = atoi(readStr.substr(secondSpacePosition + 1,readStr.length() - secondSpacePosition).c_str());

  cout << "From " << startVertex << " to " << endVertex << " via " << midVertex << endl;

  //
  // Counting
  //

  QueueRecordPointer queueStart = NULL;
  QueueRecordPointer queueEnd = NULL;

  PathPointer path = findPath(graphAdj, numberOfVertexes, startVertex, endVertex, midVertex, numberOfEdges);

  //
  // Writing to an output file
  //

  ofstream myfile;

  myfile.open ("path.out");
  if (path == NULL){
    myfile << "-1";
  } else {
    myfile << path->length << endl;
    for (int i = path->length - 1; i >= 0; i--) myfile << path->values[i] << " ";
    myfile << endl;
  }

  myfile.close();

}

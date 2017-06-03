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

typedef struct _DisjointSetObject DisjointSetObject, *DisjointSetObjectPointer;

typedef struct _Edge{
  unsigned anode;
  unsigned bnode;
} Edge, *EdgePointer;

typedef struct _EdgeEx{
  DisjointSetObjectPointer anode;
  DisjointSetObjectPointer bnode;
} EdgeEx, *EdgeExPointer;

typedef struct _GraphAdjRecord GraphAdjRecord, *GraphAdjRecordPointer;

typedef struct _GraphAdjRecord{
  unsigned name;
  unsigned weight;
  GraphAdjRecordPointer next;
  GraphAdjRecordPointer last;
} GraphAdjRecord, *GraphAdjRecordPointer;

//
//
// Graph Making
//
//

int showGraph(GraphAdjRecordPointer graphAdj, unsigned numberOfVertexes){
  GraphAdjRecordPointer currentAdjRecord = graphAdj;
  for (int i = 1; i <= numberOfVertexes; i++){
    currentAdjRecord = &graphAdj[i];
    cout << "Vertex " << i << " : ";
    do{
      currentAdjRecord = currentAdjRecord->next;
      cout << "  " << currentAdjRecord->name << " (" << currentAdjRecord->weight << ") ";
    } while(currentAdjRecord->next != NULL);
    cout << endl;
  }
  return 0;
}

bool isThereEdge(unsigned firstVertex, unsigned secondVertex, EdgePointer edges, int indexOfLastEdge){
  for (int i = 1; i <= indexOfLastEdge; i++){
    if (((edges[i].anode == firstVertex) && (edges[i].bnode == secondVertex)) || ((edges[i].anode == secondVertex) && (edges[i].bnode == firstVertex))){
      return true;
    }
  }
  return false;
}

int showGraph(EdgePointer edges, unsigned* weights, unsigned numberOfEdges){
  cout << "Graph : " << endl;
  for (int i = 1; i <= numberOfEdges; i++){
    cout << " " << edges[i].anode << " - " << edges[i].bnode << " " << " weight = " << weights[i] << " " << endl;
  }
  return 0;
}

int showMST(unsigned* edgesMST, unsigned* weights, EdgePointer edges, unsigned numberOfVertexes){
  unsigned totalWeight = 0;
  cout << "MST : " << endl;
  for (int i = 1; i < numberOfVertexes; i++){
    cout << " " << edges[edgesMST[i]].anode << " - " << edges[edgesMST[i]].bnode << " " << " weight = " << weights[edgesMST[i]] << " " << endl;
    totalWeight += weights[edgesMST[i]];
  }
  cout << "Total weight : " << totalWeight << endl;
  return 0;
}

bool setUpVertex(GraphAdjRecordPointer graphAdj, unsigned firstVertex, unsigned secondVertex){

  GraphAdjRecordPointer currentAdjRecord = &graphAdj[firstVertex];

  GraphAdjRecordPointer lastRecord = currentAdjRecord->last;
  lastRecord->next = (GraphAdjRecordPointer)malloc(sizeof(GraphAdjRecord));
  currentAdjRecord->last = lastRecord->next;
  currentAdjRecord = lastRecord->next;
  currentAdjRecord->name = secondVertex;
  currentAdjRecord->next = NULL;

  return true;
}

bool setUpVertexWeight(GraphAdjRecordPointer graphAdj, unsigned firstVertex, unsigned secondVertex, unsigned weight){

  GraphAdjRecordPointer currentAdjRecord = &graphAdj[firstVertex];

  while (currentAdjRecord->next != NULL){
    currentAdjRecord = currentAdjRecord->next;
    if (currentAdjRecord->name == secondVertex){
      currentAdjRecord->weight = weight;
      return true;
    }
  }

  return false;
}

bool appendConnectedVertex(GraphAdjRecordPointer graphAdj, unsigned firstVertex, unsigned secondVertex){
  setUpVertex(graphAdj, firstVertex, secondVertex);
  setUpVertex(graphAdj, secondVertex, firstVertex);
  return true;
}

bool appendWeightToConnectedVertex(GraphAdjRecordPointer graphAdj, unsigned firstVertex, unsigned secondVertex, unsigned weight){
  setUpVertexWeight(graphAdj, firstVertex, secondVertex, weight);
  setUpVertexWeight(graphAdj, secondVertex, firstVertex, weight);
  return true;
}

EdgePointer makeConnectedGraph(unsigned numberOfVertexes, unsigned numberOfEdges, GraphAdjRecordPointer graphAdj){
  srand(time(NULL));
  GraphAdjRecordPointer currentAdjRecord = graphAdj;

  for (unsigned i = 1; i <= numberOfVertexes; i++){  // for each v
    currentAdjRecord = &graphAdj[i];
    currentAdjRecord->next = NULL;
    currentAdjRecord->last = currentAdjRecord;
  }


  EdgePointer edges = (EdgePointer)malloc((numberOfEdges+1)*sizeof(Edge));
  unsigned firstVertex;
  unsigned secondVertex;
  for (int i = 1; i < numberOfVertexes; i++){
    edges[i].anode = i;
    edges[i].bnode = i+1;
    appendConnectedVertex(graphAdj, i, i+1);
  }



  edges[numberOfVertexes].anode = numberOfVertexes;
  edges[numberOfVertexes].bnode = 1;
  appendConnectedVertex(graphAdj, numberOfVertexes, 1);
  for (unsigned i = numberOfVertexes+1; i <= numberOfEdges; i++){
    //do{
      firstVertex = (rand() % numberOfVertexes) + 1;
      secondVertex = (rand() % numberOfVertexes) + 1;
    //} while((firstVertex == secondVertex) || isThereEdge(firstVertex, secondVertex, edges, i-1));
    edges[i].anode = firstVertex;
    edges[i].bnode = secondVertex;
    appendConnectedVertex(graphAdj, firstVertex, secondVertex);
  }

  return edges;
}

unsigned* makeWeights(unsigned numberOfEdges, unsigned minWeight, unsigned maxWeight, GraphAdjRecordPointer graphAdj, EdgePointer edges){
  srand(time(NULL));
  unsigned* weights = (unsigned*)malloc((numberOfEdges + 1)*sizeof(unsigned));
  for (int i = 1; i <= numberOfEdges; i++){
    weights[i] = (rand() % (maxWeight - minWeight)) + minWeight;
    appendWeightToConnectedVertex(graphAdj, edges[i].anode, edges[i].bnode, weights[i]);
  }
  return weights;
}

//
//
//Disjoint Set
//
//

typedef struct _DisjointSetObject{
  unsigned value;
  unsigned rank;
  DisjointSetObjectPointer parent;
} DisjointSetObject, *DisjointSetObjectPointer;

DisjointSetObjectPointer makeSet(unsigned x){
  DisjointSetObjectPointer newSet = (DisjointSetObjectPointer)malloc(sizeof(DisjointSetObject));
  newSet->rank = 0;
  newSet->value = x;
  newSet->parent = newSet;
  return newSet;
}

DisjointSetObjectPointer findSet(DisjointSetObjectPointer x){
  if (x != x->parent) x->parent = findSet(x->parent);
  return x->parent;
}

DisjointSetObjectPointer link(DisjointSetObjectPointer x, DisjointSetObjectPointer y){
  DisjointSetObjectPointer head;
  if (x->rank > y->rank){
    y->parent = x;
    head = x;
  } else {
    x->parent = y;
    if (x->rank == y->rank) y->rank = y->rank + 1;
    head = y;
  }
  return head;
}

DisjointSetObjectPointer makeUnion(DisjointSetObjectPointer x, DisjointSetObjectPointer y){
  return link(findSet(x),findSet(y));
}

//
//
//Boruvka
//
//


bool findMinimalIncidentEdge(unsigned* minimalIncidentEdge, DisjointSetObjectPointer* sets, unsigned numberOfVertexes, unsigned numberOfEdges, EdgeExPointer edgeExs, unsigned* weights){
  bool result = false;
  DisjointSetObjectPointer anode;
  DisjointSetObjectPointer bnode;
  unsigned firstSetName;
  unsigned secondSetName;
  //cout << "Find minimal incident edge ----------------------------------" << endl;
  for (int i = 1; i <= numberOfEdges; i++){
    //cout << "I've got " << i << endl;
    anode = edgeExs[i].anode;
    bnode = edgeExs[i].bnode;
    firstSetName = findSet(anode)->value;
    secondSetName = findSet(bnode)->value;
    if (firstSetName != secondSetName){
      //cout << "Something new !" << endl;
      if ((minimalIncidentEdge[firstSetName] == 0) || (weights[i] < weights[minimalIncidentEdge[firstSetName]])){
        minimalIncidentEdge[firstSetName] = i;
        result = true;
      }
      if ((minimalIncidentEdge[secondSetName] == 0) || (weights[i] < weights[minimalIncidentEdge[secondSetName]])){
        minimalIncidentEdge[secondSetName] = i;
        result = true;
      }
    }
  }
  //cout << result << endl;
  return result;
}

int showMinimals(unsigned* mins, unsigned numberOfVertexes){
  for (int i = 1; i <= numberOfVertexes; i++){
    cout << mins[i] << " ";
  }
  cout << endl;
  return 0;
}

unsigned* mst_boruvka(unsigned numberOfEdges, unsigned numberOfVertexes, EdgePointer edges, unsigned* weights){
  unsigned edgesMSTIndex = 0;
  unsigned* minimalIncidentEdge = (unsigned*)malloc((numberOfVertexes+1)*sizeof(unsigned));
  DisjointSetObjectPointer* sets = (DisjointSetObjectPointer*)malloc((numberOfVertexes+1)*sizeof(DisjointSetObjectPointer));
  unsigned* edgesMST = (unsigned*)malloc((numberOfVertexes+1)*sizeof(unsigned));
  EdgeExPointer edgeExs = (EdgeExPointer)malloc((numberOfEdges+1)*sizeof(EdgeEx));
  for (int i = 1; i <= numberOfVertexes; i++){
    minimalIncidentEdge[i] = 0;
    sets[i] = makeSet(i);
  }
  for (int i = 1; i <= numberOfEdges; i++){
    edgeExs[i].anode = sets[edges[i].anode];
    edgeExs[i].bnode = sets[edges[i].bnode];
  }

  DisjointSetObjectPointer anode;
  DisjointSetObjectPointer bnode;

  unsigned firstSetName;
  unsigned secondSetName;

  //cout << "Boruvka's inititalization successful" << endl;

  while (findMinimalIncidentEdge(minimalIncidentEdge, sets, numberOfVertexes, numberOfEdges, edgeExs, weights) || (edgesMSTIndex < numberOfVertexes - 1)){
    //showGraph(edges,weights,numberOfEdges);
    //showMST(edgesMST, weights, edges, edgesMSTIndex);
    //cout << "before " << endl;
    //showMinimals(minimalIncidentEdge, numberOfVertexes);
    //cout << "I've found some new minimal edges" << endl;
    for (int i = 1; i <= numberOfVertexes; i++){
      if (minimalIncidentEdge[i] > 0){
        //cout << "That's one of them! It has number " << minimalIncidentEdge[i] << endl;
        anode = edgeExs[minimalIncidentEdge[i]].anode;
        bnode = edgeExs[minimalIncidentEdge[i]].bnode;
        firstSetName = findSet(anode)->value;
        secondSetName = findSet(bnode)->value;
        //cout << "So, the first set is " << firstSetName << " and the second is " << secondSetName << endl;
        if (firstSetName != secondSetName){
          //cout << "They're not equals, then add the edge to minimal tree" << endl;
          edgesMSTIndex++;
          edgesMST[edgesMSTIndex] = minimalIncidentEdge[i];
          //cout << "And make union" << endl;
          makeUnion(findSet(anode),findSet(bnode));
        }// if it is not one set
        minimalIncidentEdge[i] = 0;
      }// if there is minimal edge incident the vertex
    }// for each vertex
    //cout << "after " << endl;
    //showMinimals(minimalIncidentEdge, numberOfVertexes);
  }// while find new minimal edges
  return edgesMST;
}

//
//
//Prim
//
//

unsigned findNextVertex(unsigned* minimalIncidentEdgeWeight, unsigned* inMST, unsigned numberOfVertexes, unsigned maxWeight){
  unsigned minimalWeight = maxWeight + 1;
  unsigned indexOfMinimal = 0;
  for (int i = 1; i <= numberOfVertexes; i++){
    if ((minimalIncidentEdgeWeight[i] < minimalWeight) && (inMST[i] == 0)){
      minimalWeight = minimalIncidentEdgeWeight[i];
      indexOfMinimal = i;
    }
  }
  return indexOfMinimal;
}

unsigned getEdgeNum(unsigned firstVertex, unsigned secondVertex, EdgePointer edges, unsigned numberOfEdges){
  for (int i = 1; i <= numberOfEdges; i++){
    if (((edges[i].anode == firstVertex) && (edges[i].bnode == secondVertex)) || ((edges[i].anode == secondVertex) && (edges[i].bnode == firstVertex))){
      return i;
    }
  }
  return 0;
}

unsigned* mst_prim(unsigned numberOfVertexes, unsigned numberOfEdges, GraphAdjRecordPointer graphAdj, unsigned maxWeight, EdgePointer edges){
  unsigned seed = 1;
  unsigned* minimalIncidentEdgeWeight = (unsigned*)malloc((numberOfVertexes+1)*sizeof(unsigned));
  unsigned* edgesMST = (unsigned*)malloc((numberOfVertexes+1)*sizeof(unsigned));
  unsigned* anotherVertexOfMinimalIncidentEdgeWeight = (unsigned*)malloc((numberOfVertexes+1)*sizeof(unsigned));
  unsigned* inMST = (unsigned*)malloc((numberOfVertexes+1)*sizeof(unsigned));
  unsigned edgesMSTIndex = 0;
  //EdgePointer edgesMST = (EdgePointer)malloc((numberOfEdges+1)*sizeof(Edge));

  DisjointSetObjectPointer* sets = (DisjointSetObjectPointer*)malloc((numberOfVertexes+1)*sizeof(DisjointSetObjectPointer));

  for (int i = 1; i <= numberOfVertexes; i++){
    inMST[i] = 0;
    minimalIncidentEdgeWeight[i] = maxWeight + 1;
    anotherVertexOfMinimalIncidentEdgeWeight[i] = 0;
  }
  inMST[seed] = 1;

  GraphAdjRecordPointer currentAdjRecord = &graphAdj[seed];
  while(currentAdjRecord->next != NULL){
    currentAdjRecord = currentAdjRecord->next;
    minimalIncidentEdgeWeight[currentAdjRecord->name] = currentAdjRecord->weight;
    anotherVertexOfMinimalIncidentEdgeWeight[currentAdjRecord->name] = seed;
  }

  //showMinimals(minimalIncidentEdgeWeight, numberOfVertexes);
  unsigned nextVertex;
  unsigned preVertex;
  unsigned vertexNum;
  while (edgesMSTIndex < numberOfVertexes - 1){
    nextVertex = findNextVertex(minimalIncidentEdgeWeight, inMST, numberOfVertexes, maxWeight);
    if (minimalIncidentEdgeWeight[nextVertex] > maxWeight){
      cout << "Graph is not connected" << endl;
      return edgesMST;
    }
    preVertex = anotherVertexOfMinimalIncidentEdgeWeight[nextVertex];
    inMST[nextVertex] = 1;
    edgesMSTIndex ++;
    //edgesMST[edgesMSTIndex].anode = nextVertex;
    //edgesMST[edgesMSTIndex].bnode = preVertex;
    vertexNum = getEdgeNum(nextVertex, preVertex, edges, numberOfEdges);
    edgesMST[edgesMSTIndex] = vertexNum;


    GraphAdjRecordPointer currentAdjRecord = &graphAdj[nextVertex];
    while(currentAdjRecord->next != NULL){
      currentAdjRecord = currentAdjRecord->next;
      if (inMST[currentAdjRecord->name] == 0){
        if (minimalIncidentEdgeWeight[currentAdjRecord->name] > currentAdjRecord->weight){
          minimalIncidentEdgeWeight[currentAdjRecord->name] = currentAdjRecord->weight;
          anotherVertexOfMinimalIncidentEdgeWeight[currentAdjRecord->name] = nextVertex;
        }
      }
    }
  }
  return edgesMST;
}

int main(int argc, char* argv[]){

  ofstream out("log.txt");
  //cout << "OK" << endl;
  cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

  unsigned numberOfVertexes = 10001;
  unsigned numberOfEdges = 5000000;
  unsigned step = 100000;
  unsigned minWeight = 1;
  unsigned maxWeight = 1000000;

  EdgePointer edges;
  unsigned* weights;
  GraphAdjRecordPointer graphAdj = NULL;
  unsigned* edgesMSTp;
  unsigned* edgesMSTb;

  float ffTimeStart = clock()/(float)CLOCKS_PER_SEC;
  float ffTimeStop;
  float fTimeStart = 0;
  float fTimeStop = 0;
  float fTimeMiddle = 0;
  cout << "wtf" << endl;
  while (numberOfEdges < 10000000){

    graphAdj = (GraphAdjRecordPointer)realloc(graphAdj,(numberOfVertexes+1)*sizeof(GraphAdjRecord));
    //cout << "making graph" << endl;
    edges = makeConnectedGraph(numberOfVertexes, numberOfEdges, graphAdj);
    //cout << "made graph" << endl;
    weights = makeWeights(numberOfEdges, minWeight, maxWeight, graphAdj, edges);
    fTimeStart = clock()/(float)CLOCKS_PER_SEC;
    //cout << "graph made in " << fTimeStart - fTimeStop << endl;
    edgesMSTp = mst_prim(numberOfVertexes, numberOfEdges, graphAdj, maxWeight, edges);
    fTimeMiddle = clock()/(float)CLOCKS_PER_SEC;
    edgesMSTb = mst_boruvka(numberOfEdges, numberOfVertexes, edges, weights);
    fTimeStop = clock()/(float)CLOCKS_PER_SEC;
    cout << numberOfEdges << "\t" << fTimeMiddle - fTimeStart << "\t" << fTimeStop - fTimeMiddle << endl;
    numberOfEdges+=step;
    delete graphAdj;
    graphAdj = NULL;
  }
  ffTimeStop = clock()/(float)CLOCKS_PER_SEC;
  cout << " Finished in " << ffTimeStop - ffTimeStart << "secs (" << (ffTimeStop - ffTimeStart)/60.0 << " mins)" << endl;

  /*if (argc != 5){
    cout << "usage : main numberOfVertexes numberOfEdges minWeight maxWeight" << endl;
    return 1;
  }

  istringstream ss1(argv[1]);
  if (!(ss1 >> numberOfVertexes)) cerr << "Invalid number " << argv[1] << '\n';
  istringstream ss2(argv[2]);
  if (!(ss2 >> numberOfEdges)) cerr << "Invalid number " << argv[2] << '\n';
  istringstream ss3(argv[3]);
  if (!(ss3 >> minWeight)) cerr << "Invalid number " << argv[3] << '\n';
  istringstream ss4(argv[4]);
  if (!(ss4 >> maxWeight)) cerr << "Invalid number " << argv[4] << '\n';

  if ((numberOfEdges < numberOfVertexes - 1) || (minWeight >= maxWeight)){
    cout << "Invalid arguments" << endl;
    return 1;
  }

  GraphAdjRecordPointer graphAdj = (GraphAdjRecordPointer)malloc((numberOfVertexes+1)*sizeof(GraphAdjRecord));

  EdgePointer edges = makeConnectedGraph(numberOfVertexes, numberOfEdges, graphAdj);
  unsigned* weights = makeWeights(numberOfEdges, minWeight, maxWeight, graphAdj, edges);
  //showGraph(edges,weights,numberOfEdges);
  //showGraph(graphAdj, numberOfVertexes);
  unsigned* edgesMSTp = mst_prim(numberOfVertexes, numberOfEdges, graphAdj, maxWeight, edges);
  //showMST(edgesMSTp, weights, edges, numberOfVertexes);
  unsigned* edgesMSTb = mst_boruvka(numberOfEdges, numberOfVertexes, edges, weights);
  //showMST(edgesMSTb, weights, edges, numberOfVertexes);*/
}

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <sstream>
using namespace std;

typedef struct _Node Node, *PNode;

typedef struct _Link{
  PNode nextNode;
  char symbol;
} Link, *PLink;

typedef struct _Node{
  unsigned numberOfLinks;
  bool isFinish;
  PLink links;
} Node, *PNode;

bool checkSentence(PNode startNode, string sentence){
  int length = sentence.length();
  bool broken = false;
  PNode currentNode = startNode;
  for (int i = 0; i < length; i++){
    for (int j = 0; j < currentNode->numberOfLinks; j++){
      if (currentNode->links[j].symbol == sentence[i]){
        currentNode = currentNode->links[j].nextNode;
        broken = true;
        break;
      }
    }
    if (!broken) return false;
    broken = false;
  }
  if (currentNode->isFinish == true) return true;
  return false;
}

PNode getDKA(){
  PNode startNode = (PNode)malloc(sizeof(Node));
  PNode currentNode;

  //state 1
  startNode->isFinish = false;
  startNode->numberOfLinks = 1;
  startNode->links = (PLink)malloc(sizeof(Link));

  startNode->links[0].nextNode = (PNode)malloc(sizeof(Node));
  startNode->links[0].symbol = 'b';

  //state 2
  currentNode = startNode->links[0].nextNode;
  currentNode->isFinish = false;
  currentNode->numberOfLinks = 1;
  currentNode->links = (PLink)malloc(sizeof(Link));

  currentNode->links[0].nextNode = (PNode)malloc(sizeof(Node));
  currentNode->links[0].symbol = 'a';

  //state 3
  currentNode = currentNode->links[0].nextNode;
  currentNode->isFinish = true;
  currentNode->numberOfLinks = 1;
  currentNode->links = (PLink)malloc(sizeof(Link));

  currentNode->links[0].nextNode = (PNode)malloc(sizeof(Node));
  currentNode->links[0].symbol = 'a';

  //state 4
  currentNode = currentNode->links[0].nextNode;
  currentNode->isFinish = false;
  currentNode->numberOfLinks = 2;
  currentNode->links = (PLink)malloc(2*sizeof(Link));

  currentNode->links[0].nextNode = (PNode)malloc(sizeof(Node));
  currentNode->links[0].symbol = 'b';

  currentNode->links[1].nextNode = (PNode)malloc(sizeof(Node));
  currentNode->links[1].symbol = 'c';

  PNode pFourthNode = currentNode;

  //state 5
  currentNode = currentNode->links[0].nextNode;
  currentNode->isFinish = true;
  currentNode->numberOfLinks = 1;
  currentNode->links = (PLink)malloc(sizeof(Link));

  currentNode->links[0].nextNode = pFourthNode;
  currentNode->links[0].symbol = 'a';

  //state 6
  currentNode = pFourthNode->links[1].nextNode;
  currentNode->isFinish = true;
  currentNode->numberOfLinks = 1;
  currentNode->links = (PLink)malloc(sizeof(Link));

  currentNode->links[0].nextNode = pFourthNode;
  currentNode->links[0].symbol = 'a';

  return startNode;
}

int main(int argc, char* argv[]){
  char identifier[256];
  PNode startNode = getDKA();
  string sentence = "";
  while(true){
    cout << "Type sentence for checking : " << endl;
    getline(cin, sentence);
    cout << "Result : ";
    if (checkSentence(startNode, sentence)){
      cout << "valid";
    } else {
      cout << "invalid";
    }
    cout << endl;
  }
}

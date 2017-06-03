#include <stdio.h>
#include <string.h>
#include <fstream>
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <sstream>
using namespace std;

#define NO_BASIS 0
#define BASIS 1
#define BEGIN_BASIS 2
#define END_BASIS 3

typedef struct _StackSymbolsNode StackSymbolsNode, *PStackSymbolsNode;
typedef struct _StackRelationsNode StackRelationsNode, *PStackRelationsNode;

typedef struct _PredecessorMatrix{
  unsigned** matrix;
  char* rows;
  char* cols;
  unsigned length;
} PredecessorMatrix, *PPredecessorMatrix;

typedef struct _Grammar{
  char** lefts;
  char** rights;
  unsigned length;
} Grammar, *PGrammar;

typedef struct _StackSymbolsNode{
  PStackSymbolsNode nextNode;
  char symbol;
} StackSymbolsNode, *PStackSymbolsNode;

typedef struct _StackRelationsNode{
  PStackRelationsNode nextNode;
  unsigned relationCode;
} StackRelationsNode, *PStackRelationsNode;

char pop(PStackSymbolsNode* pHead){
  PStackSymbolsNode head = *pHead;
  if (head == NULL) return 0;
  *pHead = head->nextNode;
  return head->symbol;
}

unsigned pop(PStackRelationsNode* pHead){
  PStackRelationsNode head = *pHead;
  if (head == NULL) return 0;
  *pHead = head->nextNode;
  return head->relationCode;
}

void push(PStackSymbolsNode* pHead, char symbol){
  PStackSymbolsNode pNode = (PStackSymbolsNode)malloc(sizeof(StackSymbolsNode));
  pNode->nextNode = *pHead;
  pNode->symbol = symbol;
  *pHead = pNode;
  return;
}

void push(PStackRelationsNode* pHead, unsigned relationCode){
  PStackRelationsNode pNode = (PStackRelationsNode)malloc(sizeof(StackRelationsNode));
  pNode->nextNode = *pHead;
  pNode->relationCode = relationCode;
  *pHead = pNode;
  return;
}

//predecessorMatrix
// ; ; ; ; ;
// ; ;=; ;<;
// ; ; ; ; ;
// ; ;>; ;>;
// ; ; ; ; ;

PredecessorMatrix getPredecessorMatrix(){
  PredecessorMatrix predecessorMatrix;
  unsigned** matrix = (unsigned**)malloc(5*sizeof(unsigned*));
  for (int i = 0; i < 5; i++)
  {
    matrix[i] = (unsigned*)malloc(5*sizeof(unsigned));
    for (int j = 0; j < 5; j++) matrix[i][j] = NO_BASIS;
  }
  matrix[1][2] = BASIS;
  matrix[1][4] = BEGIN_BASIS;
  matrix[3][2] = END_BASIS;
  matrix[3][4] = END_BASIS;

  char* symbs = (char*)malloc(5*sizeof(char));
  symbs[0] = 'F'; symbs[1] = 'A'; symbs[2] = 'B'; symbs[3] = 'c'; symbs[4] = 'b';
  predecessorMatrix.matrix = matrix;
  predecessorMatrix.rows = symbs;
  predecessorMatrix.cols = symbs;
  predecessorMatrix.length = 5;
  return predecessorMatrix;
}

PGrammar getGrammar(){
  PGrammar grammar = (PGrammar)malloc(sizeof(Grammar));
  char** lefts = (char**)malloc(3*sizeof(char*));
  char** rights = (char**)malloc(3*sizeof(char*));
  for (int i = 0; i < 3; i++){
    lefts[i] = (char*)malloc(5*sizeof(char));
    rights[i] = (char*)malloc(5*sizeof(char));
  }
  strcpy(lefts[0], "F");
  strcpy(lefts[1], "A");
  strcpy(lefts[2], "B");
  strcpy(rights[0], "AB");
  strcpy(rights[1], "c");
  strcpy(rights[2], "b");
  grammar->lefts = lefts;
  cout << "-- " << lefts[0] << endl;
  grammar->rights = rights;
  grammar->length = 3;
  return grammar;
}

unsigned getRelation(char rowSymbol, char colSymbol, PPredecessorMatrix predecessorMatrix){
  char* rowSymbols = predecessorMatrix->rows;
  char* colSymbols = predecessorMatrix->cols;
  unsigned rowNum = 0;
  for (int i = 0; i < predecessorMatrix->length; i++) if (rowSymbols[i] == rowSymbol){
    rowNum = i;
    break;
  }
  unsigned colNum = 0;
  for (int i = 0; i < predecessorMatrix->length; i++) if (colSymbols[i] == colSymbol){
    colNum = i;
    break;
  }
  return predecessorMatrix->matrix[rowNum][colNum];
}

string check(Grammar* grammar, string checked){
  cout << grammar->lefts[0] << endl;
  for (int i = 0; i < grammar->length; i++) {
    cout << "ccc " << checked << " " << grammar->rights[i] << endl;
    cout << grammar->lefts[i] << endl;
    if (strcmp(grammar->rights[i], checked.c_str()) == 0) return grammar->lefts[i];
  }
  return "";
}

bool checkSentence(string sentence, PredecessorMatrix predecessorMatrix, PGrammar pGrammar){
  Grammar grammar = *pGrammar;
  cout << "-- " << grammar.lefts[0] << endl;
  PStackSymbolsNode pSymbols = NULL;
  PStackRelationsNode pRelations = NULL;
  PStackSymbolsNode pUnchecked = NULL;
  string sub = "";

  int length = sentence.length();
  bool broken = false;
  unsigned relation = 0;
  char symb;
  unsigned rel;
  string llop;
  string tmp;
  stringstream tmps;
  char currentSymbol;
  for (int i = length-1; i >= 0; i--){
    push(&pUnchecked, sentence[i]);
  }
  while (true){
    if (pUnchecked == NULL) {
      cout << "END" << endl;
      sub = "";
      cout << pSymbols << endl;
      relation = END_BASIS;
      while ((pSymbols != NULL) && (relation != BEGIN_BASIS)){
        tmp = "";
        cout << "................" << endl;
        tmps.clear();
        tmps << pop(&pSymbols);
        tmps >> tmp;
        cout << "-----------------------" << tmp;
        sub.insert(0,tmp);
        relation = pop(&pRelations);
      }
      cout << "OK " << "<" <<  sub << ">" << endl;
      llop = check(&grammar, sub);
      cout << "checked " << llop << endl;
      if (llop.empty()) return false;
      cout << "CH " << llop << endl;
      for (int i = llop.length() - 1; i >= 0; i--){
        push(&pUnchecked, llop[i]);
      }
      //return false;
    }
    currentSymbol = pop(&pUnchecked);
    cout << "current is " << currentSymbol << endl;
    if (currentSymbol == 'F') return true;
    if (pSymbols == NULL){
      cout << "psymbs empty" << endl;
      push(&pSymbols, currentSymbol);
      cout << pSymbols->symbol << endl;
      cout << "pushed" << endl;
      continue;
    }
    relation = getRelation(pSymbols->symbol, currentSymbol, &predecessorMatrix);
    cout << "relation is " << relation << endl;
    if ((relation == BASIS) || (relation == BEGIN_BASIS)){
      cout << "begin basis" << endl;
      cout << currentSymbol << endl;
      push(&pSymbols, currentSymbol);
      push(&pRelations, relation);
      cout << pSymbols << endl;
      continue;
    }
    if (relation == END_BASIS){
      push(&pUnchecked, currentSymbol);
      cout << "END" << endl;
      sub = "";
      while ((pSymbols != NULL) && (relation != BEGIN_BASIS)){
        tmp = "";
        tmps.clear();
        tmps << pop(&pSymbols);
        tmps >> tmp;
        sub.insert(0,tmp);
        relation = pop(&pRelations);
      }
      cout << "OK " << sub << endl;
      llop = check(&grammar, sub);
      cout << "checked " << llop << endl;
      if (llop.empty()) return false;
      cout << "CH " << llop << endl;
      for (int i = llop.length() - 1; i >= 0; i--){
        push(&pUnchecked, llop[i]);
      }
      cout << "wtf" << endl;
      if (pSymbols != NULL) cout << " at the top " << pSymbols->symbol << endl;
      //return true;
    }
  }



  return true;
}


int main(int argc, char* argv[]){
  PredecessorMatrix predecessorMatrix = getPredecessorMatrix();
  PGrammar grammar = getGrammar();
  cout << "-- " << grammar->lefts[0] << endl;
  char identifier[256];
  string sentence = "";
  while(true){
    cout << "Type sentence for checking : " << endl;
    getline(cin, sentence);
    cout << "Result : ";
    if (checkSentence(sentence, predecessorMatrix, grammar)){
      cout << "valid";
    } else {
      cout << "invalid";
    }
    cout << endl;
  }
}

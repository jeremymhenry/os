#ifndef LAB3_LIST_H
#define LAB3_LIST_H

#include "Node.h"

class List
{
   private:

   Node *headPtr;
   int numOfItemsInList;
   int pageIndex;
   int time;
   bool calledFromSearch = false;
   int frames;

   public:
   List();
   ~List();
   void insertAtBack(int);
   void insertAtBackOptimal(int, int);
   void insertAtBackFaults(float);
   void insertAtFront(int);
   void insertAtFrontOptimal(int, int);
   void insertAtFrontFaults(float);
   bool insertAtPosition(int, int);
   bool insertAtPositionOptimal(int, int);
   void removeAtBack();
   void removeAtFront();
   bool removeAtPosition(int);
   int size();
   int get(int);
   int getIndex(int);
   bool search(int);
   bool search(int, int);
   void incrementCount();
   int mostFrequentlyUsed();
   int findFurthestOccurrence(Node*);
   Node* getNode(int);
   Node* getHeadPtr() { return headPtr; }
};

#endif //LAB3_LIST_H

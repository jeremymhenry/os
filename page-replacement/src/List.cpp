#include <iostream>
#include "List.h"

List::List()
{
   headPtr = nullptr;
   pageIndex = 1;
   time = 1;
   frames = 0;
   this->numOfItemsInList = 0;
}

List::~List()
{
   Node* temp = headPtr;        //ptr points to first node in list

   while (temp != nullptr)
   {
      headPtr->next = temp->next;
      temp->next = nullptr;
      delete temp;
      temp = headPtr->next;
      numOfItemsInList--;
   }
}

void List::insertAtFront(int page)
{
   if (calledFromSearch)
   {
      pageIndex--;
      calledFromSearch = false;
   }
   Node* tempPtr = new Node;      //create new temp pointer
   tempPtr->page = page;           //set temp pointer data to num
   tempPtr->next = headPtr;       //assign address of headPtr to tempPtr
   tempPtr->index = pageIndex;
   tempPtr->lastUsedAt = time;
   tempPtr->arrivalTime = time;
   headPtr = tempPtr;             //headPtr now points to tempPtr
   numOfItemsInList++;
   pageIndex++;
   time++;
}

void List::insertAtBack(int queue)
{
   if (calledFromSearch)
   {
      pageIndex--;
      calledFromSearch = false;
   }
   Node* temp = new Node;      //create new node
   temp = headPtr;             //temp points to first node in the list
   //travese through the list until nullptr is reached
   while (temp->next != nullptr)
   {
      temp = temp->next;
   }
   Node* temp1 = new Node;     //create new node temp1
   temp1->page = queue;          //set data of temp1 to num
   temp1->index = pageIndex;
   temp1->lastUsedAt = time;
   temp1->arrivalTime = time;
   temp1->next = nullptr;      //temp1 points to nullptr
   temp->next = temp1;         //temp now points to temp1
   numOfItemsInList++;
   pageIndex++;
   time++;
}

bool List::insertAtPosition(int page, int index)
{
   List list;
   Node* insertPtr = new Node;     //create new node
   Node* pointerBefore = new Node;
   insertPtr = headPtr;            //insertPtr points to first node in the list

   //index validator
   if (index < 1)
   {
      return false;
   }

   //insert at front
   if (index == 1)
   {
      calledFromSearch = true;
      insertAtFront(page);
      return true;
   }

   //traverse through the list until the index is reached
   for (int i = 1; i < index; i++)
   {
      if (i == (index - 1))
      {
         pointerBefore = insertPtr;
      }
      insertPtr = insertPtr->next;
      if (insertPtr == nullptr)
      {
         calledFromSearch = true;
         insertAtBack(page);
         return true;
      }
   }
   Node* tempPtr = new Node;           //create new node
   tempPtr->page = page;              //set tempPtr data to _data
   tempPtr->next = insertPtr;    //assign address of next node in the list
   tempPtr->index = index;
   tempPtr->lastUsedAt = time;
   tempPtr->arrivalTime = time;
   //to tempPtr next node
   //insertPtr->next = tempPtr;          //insertPtr will now point to tempPtr;
   pointerBefore->next = tempPtr;
   time++;
   return true;
}

void List::removeAtBack()
{
   Node* deletePtr = new Node;        //create new node and allocate space
   deletePtr = headPtr;               //assign address of headPtr ot deletePtr
   Node* tempPtr = new Node;           //create new temp node and allocate space


   //if deletePtr is not null, assign address of deletePtr to tempPtr
   //and assign the address of next node in the list to deletePtr
   while (deletePtr->next != nullptr)
   {
      tempPtr = deletePtr;
      deletePtr = deletePtr->next;
   }

   tempPtr->next = nullptr;    //tempPtr node now points to nullptr
   delete deletePtr;          //free deletePtr from memory
   numOfItemsInList--;
}

void List::removeAtFront()
{
   Node* deletePtr = new Node;     //create new node
   deletePtr = headPtr;            //assign address of headPtr to deletePtr
   headPtr = deletePtr->next;      //assign address of next node to headPtr
   delete deletePtr;               //delete deletePtr node
   numOfItemsInList--;
}

bool List::removeAtPosition(int index)
{
   Node* deletePtr = new Node;     //create new node
   deletePtr = headPtr;            //assign address of headPtr to deletePtr

   Node* tempPtr = new Node;       //create new temp node
   tempPtr = deletePtr;            //assign address of deletePtr to tempPtr

   //Index cannot be 0
   if (index < 1)
   {
      return false;
   }

   if (index == 1)
   {
      removeAtFront();
      return true;
   }

   for (int i = 1; i < index; i++)
   {
      tempPtr = deletePtr;            //assign address of deletePtr to tempPtr
      deletePtr = deletePtr->next;    //assign address of next node to deletePtr
      //index is out of range
      if (deletePtr == nullptr)
      {
         return false;
      }

   }

   tempPtr->next = deletePtr->next;    //assign address of deletePtr next node to tempPtr next node
   delete deletePtr;                   //delete deletePtr node

   return true;
}

int List::size()
{
   return numOfItemsInList;
}

int List::get(int i)
{
   int count = 0;
   Node* displayPtr = new Node;
   displayPtr = headPtr;   //assign address of headPtr to displayPtr

   //if displayPtr is not null, then display data in displayPtr node
   //and assign address of displayPtr to next node in the list
   while (displayPtr != nullptr)
   {
      if (count == i)
      {
         return displayPtr->page;
      }
      count++;
      displayPtr = displayPtr->next;
   }
   return displayPtr->page;
}

int List::getIndex(int i)
{
   int count = 0;
   Node* displayPtr = new Node;
   displayPtr = headPtr;   //assign address of headPtr to displayPtr

   //if displayPtr is not null, then display data in displayPtr node
   //and assign address of displayPtr to next node in the list
   while (displayPtr != nullptr)
   {
      if (count == i)
      {
         return displayPtr->index;
      }
      count++;
      displayPtr = displayPtr->next;
   }
   return displayPtr->index;
}

// return Node at given index
Node* List::getNode(int i)
{
   int count = 0;
   Node* displayPtr = new Node;
   displayPtr = headPtr;   //assign address of headPtr to displayPtr

   //if displayPtr is not null, then display data in displayPtr node
   //and assign address of displayPtr to next node in the list
   while (displayPtr != nullptr)
   {
      if (count == i)
      {
         return displayPtr;
      }
      count++;
      displayPtr = displayPtr->next;
   }
   return displayPtr;
}

bool List::search(int i, int simTime)
{
   //int count = 0;
   Node* displayPtr = new Node;
   displayPtr = headPtr;   //assign address of headPtr to displayPtr

   //if displayPtr is not null, then display data in displayPtr node
   //and assign address of displayPtr to next node in the list
   while (displayPtr != nullptr)
   {
      if (displayPtr->page == i)
      {
         //return displayPtr->page;
         displayPtr->lastUsedAt = time;
         displayPtr->count++;
         time++;
         return true;
      }
      displayPtr = displayPtr->next;
   }
   return false;
   //return displayPtr->page;
}

bool List::search(int i)
{
   return search(i, 0);
}

// count frequency of page elements
void List::incrementCount()
{
   Node* displayPtr = new Node;
   Node* tempPtr = new Node;
   int count = 0;

   if (headPtr == nullptr)
   {
      std::cout << "Error";
   }
   else
   {
      displayPtr = headPtr;
      tempPtr = displayPtr;
      while (tempPtr->next != nullptr)
      {

         while (displayPtr != nullptr)
         {
            count++;
            if (tempPtr->page == displayPtr->page)
            {
               tempPtr->count++;
            }
            displayPtr = displayPtr->next;
         }
         displayPtr = headPtr;
         tempPtr = tempPtr->next;
      }
   }
}

// return index of page that has been most frequently used
// (this is in terms of how many occurrences of a page)
int List::mostFrequentlyUsed()
{
   Node* tempPtr = new Node;
   tempPtr = headPtr;
   Node* mostUsedPage = headPtr;
   int mostUsed = tempPtr->count;
   int index = 1;    // page frame list index

   while (tempPtr->next != nullptr)
   {
      // both pages have the same count
      // we then break the tie using FIFO
      if (mostUsedPage->count == tempPtr->next->count)
      {
         if (mostUsedPage->arrivalTime > tempPtr->next->arrivalTime)
         {
            mostUsedPage = tempPtr->next;
            index = tempPtr->next->index;
         }
      }
      // if next node has the higher count, that node
      // then becomes the most used node
      else if (mostUsedPage->count < tempPtr->next->count)
      {
         mostUsedPage = tempPtr->next;
         index = tempPtr->next->index;
      }
      tempPtr = tempPtr->next;
   }
   return index;
}

// return the index of the page that occurs farthest in the future
// input: current Node or pageFrameList?
int List::findFurthestOccurrence(Node* currentNode)
{
   Node* displayPtr = new Node;
   List tempList;
   displayPtr = headPtr;
   int page = displayPtr->page;
   int nextOccurrence = 0;
   int furthestOccurrence = 0;
   Node* tempNode = currentNode;
   int pageToReplace = 0;
   bool nextOccurrenceExists;
   int pageFrameIndex = 0;

   furthestOccurrence = currentNode->index;

   // frame list
   while (displayPtr != nullptr)
   {
      nextOccurrenceExists = false;
      while (tempNode->next != nullptr)
      {
         if (displayPtr->page == tempNode->next->page)
         {
            // if the next node available occurs farther in the future
            // this node is designated as the least recently used
            if (furthestOccurrence < tempNode->next->index)
            {
               if (tempNode->next != nullptr)
               {
                  furthestOccurrence = tempNode->next->index;
                  pageToReplace = tempNode->next->page;
                  pageFrameIndex = displayPtr->index;
               }
            }
            //nextOccurrence = tempNode->next->index;
            nextOccurrenceExists = true;
            break;
         }
         tempNode = tempNode->next;
      }
      // if page does not have occur again in the page string list
      // this page is the least used so return its index
      if (!nextOccurrenceExists)
      {
         pageToReplace = displayPtr->page;
         pageFrameIndex = displayPtr->index;
         return pageFrameIndex;
      }
      tempNode = currentNode;
      displayPtr = displayPtr->next;
   }

   return pageFrameIndex;
}

// designed for Optimal algorithm
void List::insertAtFrontOptimal(int page, int index)
{
   Node* tempPtr = new Node;      //create new temp pointer
   tempPtr->page = page;           //set temp pointer data to num
   tempPtr->next = headPtr;       //assign address of headPtr to tempPtr
   if (calledFromSearch)
   {
      tempPtr->index = index;
      calledFromSearch = false;
   }
   else
   {
      tempPtr->index = pageIndex;
   }
   tempPtr->lastUsedAt = time;
   headPtr = tempPtr;             //headPtr now points to tempPtr
   numOfItemsInList++;
   pageIndex++;
   time++;
}

// design for Optimal algorithm
void List::insertAtBackOptimal(int page, int index)
{
   Node* temp = new Node;      //create new node
   temp = headPtr;             //temp points to first node in the list
   //travese through the list until nullptr is reached
   while (temp->next != nullptr)
   {
      temp = temp->next;
   }
   Node* temp1 = new Node;     //create new node temp1
   temp1->page = page;          //set data of temp1 to num
   if (calledFromSearch)
   {
      temp1->index = index;
      calledFromSearch = false;
   }
   else
   {
      temp1->index = pageIndex;
   }
   temp1->lastUsedAt = time;
   temp1->next = nullptr;      //temp1 points to nullptr
   temp->next = temp1;         //temp now points to temp1
   numOfItemsInList++;
   pageIndex++;
   time++;
}

bool List::insertAtPositionOptimal(int page, int index)
{
   List list;
   Node* insertPtr = new Node;     //create new node
   Node* pointerBefore = new Node;
   insertPtr = headPtr;            //insertPtr points to first node in the list

   //index validator
   if (index < 1)
   {
      return false;
   }

   //insert at front
   if (index == 1)
   {
      calledFromSearch = true;
      insertAtFrontOptimal(page, index);
      return true;
   }

   //traverse through the list until the index is reached
   for (int i = 1; i < index; i++)
   {
      if (i == (index - 1))
      {
         pointerBefore = insertPtr;
      }
      insertPtr = insertPtr->next;
      if (insertPtr == nullptr)
      {
         calledFromSearch = true;
         insertAtBackOptimal(page, index);
         return true;
      }
   }
   Node* tempPtr = new Node;           //create new node
   tempPtr->page = page;              //set tempPtr data to _data
   tempPtr->next = insertPtr;    //assign address of next node in the list
   tempPtr->index = index;
   tempPtr->lastUsedAt = time;
   //to tempPtr next node
   //insertPtr->next = tempPtr;          //insertPtr will now point to tempPtr;
   pointerBefore->next = tempPtr;
   time++;
   return true;
}


// insertions for storing and calculating page fault rates
// of each algorithm
void List::insertAtFrontFaults(float faultRate)
{
   Node* tempPtr = new Node;      //create new temp pointer
   tempPtr->faultRate = faultRate;           //set temp pointer data to num
   tempPtr->next = headPtr;       //assign address of headPtr to tempPtr
   headPtr = tempPtr;             //headPtr now points to tempPtr
   numOfItemsInList++;
}

void List::insertAtBackFaults(float faultRates)
{
   Node* temp = new Node;      //create new node
   temp = headPtr;             //temp points to first node in the list
   //travese through the list until nullptr is reached
   while (temp->next != nullptr)
   {
      temp = temp->next;
   }
   Node* temp1 = new Node;     //create new node temp1
   temp1->faultRate = faultRates;          //set data of temp1 to num
   temp1->index = pageIndex;
   temp1->lastUsedAt = time;
   temp1->next = nullptr;      //temp1 points to nullptr
   temp->next = temp1;         //temp now points to temp1
   numOfItemsInList++;
   pageIndex++;
   time++;
}

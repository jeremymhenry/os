#include <iostream>
#include <iomanip>
#include <sstream>
#include "PageReplacement.h"

PageReplacement::PageReplacement()
{
   numPageFaults = 0;
   numFrames = 0;
   time = 0;
   numPages = 0;
}

// add page fault rates to list
void PageReplacement::addPageFaults(int pageFaults)
{
   float pageFaultRate = 0.0;
   if (pageFaultList.size() == 0)
   {
      pageFaultRate = pageFaults / (float) time;
      pageFaultList.insertAtFrontFaults(pageFaultRate);
   }
   else
   {
      pageFaultRate = pageFaults / (float) time;
      pageFaultList.insertAtBackFaults(pageFaultRate);
   }
}

// calculate page fault rates at these intervals
void PageReplacement::pageFaultCalcTime(int pageFaults)
{
   if (time == 1999 || time == 3999 || time == 5999 || time == 7999 || time == 9999)
   {
      addPageFaults(pageFaults);
   }
}

// calculate and print results of the simulation, which include
// which algorithms were used, the total number of page faults,
// frame size, and the page fault rates of each algorithm at intervals
// of 2000 pages
std::string PageReplacement::printResults(int alg)
{
   std::string algorithm;
   int i = 1;
   switch(alg)
   {
      case 1:
         algorithm = "FIFO";
         break;
      case 2:
         algorithm = "LRU";
         break;
      case 3:
         algorithm = "MFU";
         break;
      case 4:
         algorithm = "Optimal";
         break;
      default:
         break;
   }

   std::stringstream output;
   output   << "  " << std::left << std::setprecision(3) << std::fixed
            << std::setw(14) << algorithm
            << std::setw(14) << numPageFaults;

   /*
   if (pageFaultList.size() > 5)
   {
      i = pageFaultList.size() - 4;
   }
   while (i <= pageFaultList.size())
   {
      output << pageFaultList.getNode(i - 1)->faultRate << " ";
      i++;
   }
    */
   output << std::endl;
   return output.str();
}

// search for incoming page within the page frame table
bool PageReplacement::search(List &pageFramesList, int page, int time)
{
   return pageFramesList.search(page, time);
}

// search for incoming page within the page frame table
bool PageReplacement::search(List &pageFramesList, int page)
{
   return search(pageFramesList, page, 0);
}

void PageReplacement::OPTIMAL(List& list)
{
   bool found, insertedAtFront = false;
   int incomingPage = 0;
   int index = 0;
   List pageFramesList, pageFaultList;
   numPageFaults = 0;

   for (time = 0; time < list.size(); time++)
   {
      pageFaultCalcTime(numPageFaults);
      if (pageFramesList.size() < numFrames)
      {
         if (!insertedAtFront)
         {
            incomingPage = list.get(time);
            index = list.getIndex(time);
            pageFramesList.insertAtFrontOptimal(incomingPage, index);
            insertedAtFront = true;
            numPageFaults++;
         }
         else
         {
            incomingPage = list.get(time);
            index = list.getIndex(time);
            found = search(pageFramesList, incomingPage);
            if (!found)
            {
               pageFramesList.insertAtBackOptimal(list.get(time), index);
               numPageFaults++;
            }
         }
      }
         // Optimal page replacements
      else
      {
         incomingPage = list.get(time);
         found = search(pageFramesList, incomingPage, time);
         // here, page was not found in the page frame table, thus a page fault
         // occurs and Optimal page replacement happens
         if (!found)
         {
            // retrieve current node
            // from this node, we need to calculate which page in the page
            // frame table will occur the farthest in the future. If found, this
            // is the page we wish to replace. If page is not found at all, we
            // stop the search and remove this page
            Node* currentNode = list.getNode(time);
            int optimalIndex = pageFramesList.findFurthestOccurrence(currentNode);
            pageFramesList.removeAtPosition(optimalIndex);
            pageFramesList.insertAtPositionOptimal(list.get(time), optimalIndex);
            numPageFaults++;
         }
      }
   }
}

void PageReplacement::MFU(List& list)
{
   bool found, insertedAtFront = false;
   int leastUsedIndex = 0;
   int incomingPage = 0;
   List pageFramesList;
   numPageFaults = 0;

   for (time = 0; time < list.size(); time++)
   {
      pageFaultCalcTime(numPageFaults);
      if (pageFramesList.size() < numFrames)
      {
         if (!insertedAtFront)
         {
            incomingPage = list.get(time);
            pageFramesList.insertAtFront(incomingPage);
            insertedAtFront = true;
            numPageFaults++;
         }
         else
         {
            incomingPage = list.get(time);
            found = search(pageFramesList, incomingPage);
            if (!found)
            {
               pageFramesList.insertAtBack(list.get(time));
               numPageFaults++;
            }
         }
      }
      // MFU page replacements
      else
      {
         incomingPage = list.get(time);
         found = search(pageFramesList, incomingPage, time);
         // here, page was not found in the page frame table, thus a page fault
         // occurs and MFU page replacement happens
         if (!found)
         {
            // here, we want to replace the page which has the highest
            // count (number of hits in the current page frame table)
            int mfuIndex = pageFramesList.mostFrequentlyUsed();
            pageFramesList.removeAtPosition(mfuIndex);
            pageFramesList.insertAtPosition(list.get(time), mfuIndex);
            numPageFaults++;
         }
      }
   }
}

// Least Recently Used Algorithm
void PageReplacement::LRU(List& list)
{
   bool found, insertedAtFront = false;
   int leastUsedIndex = 0;
   int incomingPage = 0;
   List pageFramesList;
   numPageFaults = 0;

   // simulation runs until end of page string reference
   for (time = 0; time < list.size(); time++)
   {
      pageFaultCalcTime(numPageFaults);
      if (pageFramesList.size() < numFrames)
      {
         if (!insertedAtFront)
         {
            incomingPage = list.get(time);
            pageFramesList.insertAtFront(incomingPage);
            insertedAtFront = true;
            numPageFaults++;
         }
         else
         {
            incomingPage = list.get(time);
            found = search(pageFramesList, incomingPage);
            if (!found)
            {
               pageFramesList.insertAtBack(list.get(time));
               numPageFaults++;
            }
         }
      }
      // LRU page replacements
      else
      {
         incomingPage = list.get(time);
         found = search(pageFramesList, incomingPage, time);
         // here, page was not found in the page frame table, thus a page fault
         // occurs and LRU page replacement happens
         if (!found)
         {
            int lruIndex = 0;
            Node* displayPtr = new Node;
            displayPtr = pageFramesList.getHeadPtr();
            int leastUsed = displayPtr->lastUsedAt;
            int index = 1;

            while (displayPtr->next != nullptr)
            {
               if (leastUsed > displayPtr->next->lastUsedAt)
               {
                  leastUsed = displayPtr->next->lastUsedAt;
                  index = displayPtr->next->index;
               }
               displayPtr = displayPtr->next;
            }
            lruIndex = index;
            pageFramesList.removeAtPosition(lruIndex);
            pageFramesList.insertAtPosition(list.get(time), lruIndex);
            numPageFaults++;
         }
      }
   }
}

// FIFO Page Replacement Algorithm
void PageReplacement::FIFO(List& list)
{
   bool found, insertedAtFront = false;
   int oldestIndex = 1;
   int incomingPage = 0;
   List pageFramesList;
   numPageFaults = 0;

   // simulation runs until end of page string reference
   for (time = 0; time < list.size(); time++)
   {
      pageFaultCalcTime(numPageFaults);
      if (pageFramesList.size() < numFrames)
      {
         if (!insertedAtFront)
         {
            pageFramesList.insertAtFront(list.get(time));
            insertedAtFront = true;
            numPageFaults++;
         }
         else
         {
            incomingPage = list.get(time);
            found = search(pageFramesList, incomingPage);
            if (!found)
            {
               pageFramesList.insertAtBack(list.get(time));
               numPageFaults++;
            }
         }
      }
      // FIFO page replacements
      else
      {
         incomingPage = list.get(time);
         found = search(pageFramesList, incomingPage);
         // here, page was not found in the page frame table, thus a page fault
         // occurs and FIFO page replacement happens
         if (!found)
         {
            // replace page which is located in the oldest index
            pageFramesList.removeAtPosition(oldestIndex);
            pageFramesList.insertAtPosition(list.get(time), oldestIndex);
            numPageFaults++;
            if (oldestIndex == numFrames)
            {
               oldestIndex = 1;
            }
            else
            {
               oldestIndex++;
            }
         }
      }
   }
}


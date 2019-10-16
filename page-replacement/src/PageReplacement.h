#ifndef LAB3_PAGEREPLACEMENT_H
#define LAB3_PAGEREPLACEMENT_H

#include <iostream>
#include "List.h"

class PageReplacement
{
   private:
   List pageList, pageFaultList;
   int numPageFaults;
   int numFrames;
   int time;
   int numPages;

   public:
   PageReplacement();
   void FIFO(List&);
   void LRU(List&);
   void MFU(List&);
   void OPTIMAL(List&);
   bool search(List&, int);
   bool search(List&, int, int);
   void setNumFrames(int numFrames) { this->numFrames = numFrames; }
   void setNumPages(int numPages) { this->numPages = numPages; }
   std::string printResults(int);
   void addPageFaults(int);
   void pageFaultCalcTime(int);
};

#endif //LAB3_PAGEREPLACEMENT_H

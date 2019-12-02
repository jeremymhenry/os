#include <iostream>
#include <fstream>
#include "PageReplacement.h"

int main(int argc, const char * argv[])
{
   int page = 0;
   std::string line, inputFileName, outputFileName;

   // read in command line arguments - frame size, input and output files
   int numFrames = atoi(argv[1]);
   inputFileName = "pages.txt";
   outputFileName = "outfile.txt";

   std::ifstream inFile;
   inFile.open(inputFileName);
   PageReplacement pageReplacement;
   List list;
   bool insertedAtFront = false;
   int numPages = 0;

   if (inFile.fail())
   {
      std::cout << "Error. Could not open file." << std::endl;
      exit(1);
   }
   else
   {
      while (inFile >> page)
      {
         if (!insertedAtFront)
         {
            list.insertAtFront(page);
            insertedAtFront = true;
            numPages++;
         }
         else
         {
            list.insertAtBack(page);
            numPages++;
         }
      }
   }
   // close file
   inFile.close();
   std::ofstream outFile;
   outFile.open(outputFileName, std::ofstream::out | std::ofstream::app);

   outFile << "==============================================================\n"
           << "            Page Replacement Algorithm Simulation             \n"
           << "==============================================================\n"
           << "                                                              \n"
           << "  Algorithm Total page faults  -   Frame Size: " << numFrames << " \n"
           << "--------------------------------------------------------------\n";

   pageReplacement.setNumFrames(numFrames);
   pageReplacement.setNumPages(numPages);

   // start Page Replacement Simulations
   pageReplacement.FIFO(list);
   outFile << pageReplacement.printResults(1);
   pageReplacement.LRU(list);
   outFile << pageReplacement.printResults(2);
   //pageReplacement.MFU(list);
   //outFile << pageReplacement.printResults(3);
   pageReplacement.OPTIMAL(list);
   outFile << pageReplacement.printResults(4);

   std::cout << "Simulation is complete. Check " << outputFileName << " for output results. "
   << std::endl;
}

*******************************************************


                 Read Me


*******************************************************
*  		Description of the program
*******************************************************
The purpose of this project is the implement a page replacement
algorithm simulator, which simulates the following 
page replacement algorithms: First In, First Out, Least
Recently Used, Most Frequently Used, and Optimal. As well 
as implementing these algorithms, we will also be 
calculating and displaying the page fault rates for each
algorithm. These rates will be calculated at intervals
of 2000 pages. Each algorithm will also be tested using
four different frame sizes: 128, 256, 512, and 1024.	

*******************************************************
*  		Source files
*******************************************************
Name: Node.h
	This file contains the declaration of a Node for
	the Linked List. Node contains information about
	our incoming page requests, such as count, arrival
	time, its numerical value, and the its index 
	within the Page Frames List. Some of the data are
	specific to one of the aforementioned algorithms. 

Name: List.h
	Contains the class declaration of my List, which 
	holds the page string reference and holds the
	page frame table, which stores incoming page 
	requests. 

Name: List.cpp
	Contains class definition and method implementations
	of List class. Methods include insertions, removals,
	searches and gets. List class is implemented as a 
	Linked List.

Name: PageReplacement.h
	Contains declaration for the page replacement 
	simulator. Holds page frame lists during the simulation,
	time duration, number of frames and the number of
	page faults for the simulation.

Name: PageReplacement.cpp
	Contains the implementation of PageReplacement.h. 
	Methods include implementations of the four page
	replacement algorithms FIFO, LRU, MFU and Optimal, 
	being able to search if incoming page requests 
	already exist in the page frame table, calculating
	page fault rates and 2000 page intervals, and 
	calculating and simulation results.

Name: main.cpp
	Main driver of the Page Replacement Simulation.
	Program starts by reading in three arguments from
	the command line: frame size, input file name, and
	output file name. The program then opens the input
	file, starts the simulation, and prints the results
	of each simulation to the output file. 

Name: pg-reference.txt
	Input file used to test each algoirthm simulation.
	Contains 10,000 page references.

*******************************************************
*  		Circumstances of programs
*******************************************************
Compiles on csegrid.ucdenver.pvt. Program was tested
using pg-reference.txt input file.

*******************************************************
*  How to build and run the program
*******************************************************

1. Uncompress the homework using gzip command

   Now you should see a directory named homework with the files:
	main.cpp
	Node.h
	List.h
	List.cpp
	PageReplacement.h
	PageReplacement.cpp
	pg-reference.txt
	Readme

2. Build the program.

    Change to the directory that contains the file by:
    % cd [hen8703] 

    Compile the program by:
    % make

3. Run the program by:
   % ./[target-name] [frame size] [input file] [output file]

4. Delete the obj files, executables, and core dump by
   %./make clean

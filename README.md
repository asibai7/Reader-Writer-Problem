# Reader-Writer-Problem
This program solves the Reader Writer problem by preventing starvation from occuring. To run, make sure you have the following 4 necessary files in order to successfully compile: readerwriter.h, readerwriter.c, main.c, and scenarios.txt. To compile, you may use to the following command:
	make

To compile and run, use:
	make run

To clean the executable files, use:
	make clean

You may edit the scenarios file to change the order of the reads and write. To compile and run in another way, use the following to compile: 
gcc -o readerwriter main.c readerwriter.c -l phthread 
to run, use: 
  ./readerwriter

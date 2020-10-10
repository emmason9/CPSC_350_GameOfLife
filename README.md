# CPSC_350_GameOfLife
This is Assignment 2 of the CPSC_350 class, called Game of Life.

1)
Emilee Mason
ID#2321064
emmason@chapman.edu
CPSC 350_01
Assignment 2: Game of Life

2)files
FileProcessor.h //help process fstream related objects 
FileProcessor.cpp
Cell.h	 	//create a cell object
Cell.cpp
CellGrid.h	//create an array/"grid" using cell objects 
CellGrid.cpp
GameMode.h	//setup a grid according to the set gamemode 
GameMode.cpp
Simulation.h	//allows users to interact and run the Game of Life
Simulation.cpp
main.cpp	//main method, runs the simulation all together


3) Bugs/errors that may occur.
Just as a heads up, some of the random grids may take a long time to set up because it takes a little 
while for the cells to be placed in random positions within the grid, since it might be going to indexes 
that are already filled with a cell repeatedly. Once the grid gets set up, the rest of the program 
should work okay! 
Also, when a grid stablizes, there will be a repeat generation after the orinigal one it stablizes one,
just to show that the grid stablized verses being completely empty. The empty grids shouldn't repeat a
generation. 


4)References:
https://stackoverflow.com/questions/9219712/c-array-expression-must-have-a-constant-value
This site helpped me understand a huge issued I ran into at the beginning. I was trying to have
a 2D array as a member variable of my CellGrid class and it wasn't working because the array's 
values had to be constants since they need to allocate the right amount of memory at compile time. 
I used this code to help it run smoothly through that process. (this one ate up a lot of time)

http://www.cplusplus.com/reference/cstdlib/srand/
https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/
https://stackoverflow.com/questions/12657962/how-do-i-generate-a-random-number-between-two-variables-that-i-have-stored
I used these to figure out the rand() and srand() functionality. 

https://www.tutorialspoint.com/how-to-convert-std-string-to-lower-case-in-cplusplus
This is how I learned how convert a string to all lowercase.

http://www.cplusplus.com/reference/cctype/isdigit/
I knew isalpha() and isdigit() exist from pyhton, but I didn't know how to use it in C++, if it was
different at all.

https://www.geeksforgeeks.org/converting-strings-numbers-cc/
http://www.cplusplus.com/reference/string/stod/
How I learned about the stoi() and stod() methods to help me figure out how to get the right type
of inputs from the user. 

https://stackoverflow.com/questions/9670396/exception-handling-and-opening-a-file
I was having issues handling the exceptions being thrown when a file name was input.

https://en.cppreference.com/w/cpp/thread/sleep_for
http://www.cplusplus.com/reference/thread/this_thread/sleep_for/
https://stackoverflow.com/questions/24776262/pause-console-in-c-program
I found the sleep_for method as a good way to pause the program/thread across all platforms. I noticed
the system("pause") had a lot of controversy and also didn't work when I was using it, so I used this
one instead.


5) how to run: (assuming you downloaded the file from the GitHub, so you start with a .zip file)
	1) Unzip the ___.zip file in a file that can be accessed by a docker container
	2) open the docker (docker start [container name], docker attach [container name])
	3) go into the unziped file within the docker container
	4) make all 		(creates an executable file)
	5) ./GameOfLife.exe	(runs the program)
	6) follow all the programs commands 
	7) make realclean 	(clean all of the excess files created from the program)

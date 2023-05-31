#include <iostream>
#include <fstream>
#include "stack.h"
using namespace std;

// Questions: /////////////////////////////////////////////////////////////
//	1. How do I get my program to handle forks in the road?
//	2. How do I process a 1 by 1 maze?
//	3. How to I get my program to recognize when there is no way out?
//	4. What is the degree of robustness for this program?
//	5. How many comments are too many comments? Comment other .cpp and .h?
///////////////////////////////////////////////////////////////////////////

Stack myStack;
int const MAXROWS = 80;
int const MAXCOLUMNS = 80;

bool checkNorth(int& currentRow, int& currentColumn, char maze[MAXROWS][MAXCOLUMNS])
{
	bool moveAvailable = false;

	// check north	- [currentRow-1][currentColumn]

	if (currentRow - 1 > 0) // out of bounds?
	{
		if (maze[currentRow - 1][currentColumn] == 'E'
			|| maze[currentRow - 1][currentColumn] == '0') // available move?
		{
			moveAvailable = true;
		}
	}

	return moveAvailable;
}



bool checkSouth(int& currentRow, int& currentColumn, char maze[MAXROWS][MAXCOLUMNS], int mazeRows)
{
	bool moveAvailable = false;

	// check south	- [currentRow+1][currentColumn]

	if (currentRow + 1 < mazeRows) // out of bounds?
	{
		if (maze[currentRow + 1][currentColumn] == 'E'
			|| maze[currentRow + 1][currentColumn] == '0') // available move?
		{
			moveAvailable = true;
		}
	}

	return moveAvailable;
}



bool checkEast(int& currentRow, int& currentColumn, char maze[MAXROWS][MAXCOLUMNS])
{
	bool moveAvailable = false;

	// check east	- [currentRow][currentColumn+1]

	if (currentColumn + 1 > 0) // out of bounds?
	{
		if (maze[currentRow][currentColumn + 1] == 'E'
			|| maze[currentRow][currentColumn + 1] == '0') // available move?
		{
			moveAvailable = true;
		}
	}

	return moveAvailable;
}



bool checkWest(int& currentRow, int& currentColumn, char maze[MAXROWS][MAXCOLUMNS], int mazeColumns)
{
	bool moveAvailable = false;

	// check west	- [currentRow][currentColumn-1]

	if (currentColumn - 1 < mazeColumns) // out of bounds?
	{
		if (maze[currentRow][currentColumn - 1] == 'E'
			|| maze[currentRow][currentColumn - 1] == '0') // available move?
		{
			moveAvailable = true;
		}
	}

	return moveAvailable;
}



bool processMazeData(int mazeRows, int mazeColumns, char maze[MAXROWS][MAXCOLUMNS], int currentRow, int currentColumn)
{
	// flag variable (char because I need three states: 'N':NULL 'T':TRUE 'F':FALSE)
	char pathFound = 'N';

	Coordinate nextAvailableMove;

	do 
	{
		// checks north position by 
		if (checkNorth(currentRow, currentColumn, maze))
		{
			Coordinate moveFound;
			moveFound.Row = (currentRow - 1);
			moveFound.Column = currentColumn;
			myStack.Push(moveFound);
		}

		if (checkSouth(currentRow, currentColumn, maze, mazeRows))
		{
			Coordinate moveFound;
			moveFound.Row = (currentRow + 1);
			moveFound.Column = currentColumn;
			myStack.Push(moveFound);
		}

		if (checkEast(currentRow, currentColumn, maze))
		{
			Coordinate moveFound;
			moveFound.Row = currentRow;
			moveFound.Column = (currentColumn + 1);
			myStack.Push(moveFound);
		}

		if (checkWest(currentRow, currentColumn, maze, mazeColumns))
		{
			Coordinate moveFound;
			moveFound.Row = currentRow;
			moveFound.Column = (currentColumn - 1);
			myStack.Push(moveFound);
		}

		if (!myStack.Empty())
		{
			myStack.Pop(nextAvailableMove);
			maze[currentRow][currentColumn] = '.';
			currentRow = nextAvailableMove.Row;
			currentColumn = nextAvailableMove.Column;
		}
		else if (myStack.Empty())
		{
			pathFound = 'F';
		}
		

		if (maze[currentRow][currentColumn] == 'E')
		{
			pathFound = 'T';
		}
	}
	while (pathFound != 'T' && pathFound != 'F');

	if (pathFound == 'T')
	{
		return true;
	}
	else if (pathFound == 'F')
	{
		return false;
	}
}



int main()
{
	// define a 2D array to hold maze chars
	char maze[MAXROWS][MAXCOLUMNS];
	
	// define and initialize local variables
	int mazeNumber = 1;
	int mazeRows = 0;
	int mazeColumns = 0;
	int startingRow = 0;
	int startingColumn = 0;
	bool stopSignalFound = false;

	// open i/o files
	ifstream inputFile;
	ofstream outputFile;
	inputFile.open("maze.txt");
	outputFile.open("mazeSolutions.txt");

	// check suffiency of i/o files
	if (inputFile.good() && outputFile.good())
	{
		// output initial header in output text file
		outputFile << "Solutions to A-MAZE-ING Stacks Assignment" << endl;
		outputFile << "Cason Kirschner" << endl;

		do 
		{
			// read dimensions of maze
			inputFile >> mazeRows >> mazeColumns;
			
			// check for signal to stop reading
			if (mazeRows == -1 && mazeColumns == -1)
			{
				stopSignalFound = true;
			}
			else
			{
				// read maze 
				for (int currentRow = 0; currentRow < mazeRows; currentRow++)
				{
					for (int currentColumn = 0; currentColumn < mazeColumns; currentColumn++)
					{
						inputFile >> maze[currentRow][currentColumn];
					}
				}
				
				// read starting coordinates
				inputFile >> startingRow >> startingColumn;
				
				// find a path if possible
				bool pathFound = processMazeData(mazeRows, mazeColumns, maze, startingRow, startingColumn);

				// output blank line
				outputFile << endl;

				// output maze number
				outputFile << "MAZE NUMBER " << mazeNumber << endl;
				mazeNumber++;

				// output blank line
				outputFile << endl;

				// output maze solution
				for (int currentRow = 0; currentRow < mazeRows; currentRow++)
				{
					for (int currentColumn = 0; currentColumn < mazeColumns; currentColumn++)
					{
						outputFile << maze[currentRow][currentColumn];
					}
					outputFile << endl;
				}

				// output blank line
				outputFile << endl;

				// output appropriate message
				if (pathFound)
				{
					outputFile << "There IS a way out" << endl;
				}
				else
				{
					outputFile << "There IS NOT a way out" << endl;
				}
				
			}
		} while (stopSignalFound == false || !inputFile.eof());
	}
	else 
	{
		cout << "Error opening input text file and/or output text file." << endl;
	}

	// close i/o files
	inputFile.close();
	outputFile.close();

	// release memory
	myStack.~Stack();

	system("pause");
}
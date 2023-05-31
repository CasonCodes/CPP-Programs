#pragma once

/*************************************************************************
Header File Name: Stack.h
Des:  This file will contain the stucture and methods for the class
	  stack which is a stack implemented as a dynamically allocated
	  single linked-list.
Author: Coach Ragsdale

*************************************************************************/

//Used to store a coordinate in the maze [Row][Column]
struct Coordinate
{
	int Row, Column;
};


//Define a node in a single linked-list. Each node will store a coordinate and a 
//pointer to the next node in the list
struct Node
{
	Coordinate Element;
	Node* Next;
};


class Stack
{
public:

	//Constuctor
	Stack();

	//Destructor
	~Stack();

	//Will see if stack is empty
	bool Empty();

	//Will place elements on the top of the stack
	bool Push(Coordinate);

	//Will remove element off the top of the stack
	bool Pop(Coordinate&);

	//No full function is provided since it is dependent on
	//memory allocation and push will check for that.

private:
	Node* Top;
};



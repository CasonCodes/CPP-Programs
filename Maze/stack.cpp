#include <iostream>
#include "stack.h"



Stack::Stack() 
{
	// when creating a stack, initialize Top to NULL to signify that the stack is empty upon creation
	Top = NULL;
}



Stack::~Stack() 
{
	// as long as the stack is not empty...
	while (Top != NULL) 
	{
		// create a new pointer
		Node* nodeToDelete = new Node;

		// mark top as the node to delete
		nodeToDelete = Top;

		// if there is not an item after top...
		if (Top->Next != NULL)
		{
			// make top point to the next itme in the stack
			Top = Top->Next;

			// and delete marked node
			delete nodeToDelete;
		}
		// otherwise, if there is not an item after top... 
		else if (Top->Next == NULL)
		{
			// mark the stack as empty
			Top = NULL;

			// delete the last marked node
			delete nodeToDelete;
		}
	}
}



bool Stack::Empty() 
{
	// flag variable
	bool isEmpty = false;

	// if the stack is empty
	if (Top == NULL)
	{
		// mark flag variable as true
		isEmpty = true;
	}

	// return flag variable
	return isEmpty;
}



bool Stack::Push(Coordinate pushedCoordinate) 
{
	// flag variable
	bool pushSuccessful = false;

	// new node to push onto stack
	Node* newNode = new Node;

	// store available move coord in new node
	newNode->Element = pushedCoordinate;

	// if the stack is empty...
	if (Top == NULL)
	{
		// make top point to the new node
		Top = newNode;

		// since it is the only one on the stack, set it to NULL because nothing comes after
		newNode->Next = NULL;

		// mark that the push is successful
		pushSuccessful = true;
	}
	// otherwise, if the stack is not empty...
	else if (Top != NULL)
	{
		// take whatever top is pointing to and make the new node point to it instead
		newNode->Next = Top;

		// make top point to the newly pushed node
		Top = newNode;

		// mark that the push is successful
		pushSuccessful = true;
	}

	// return flag variable
	return pushSuccessful;
}



bool Stack::Pop(Coordinate& poppedCoordinate) 
{
	// flag variable
	bool popSuccessful = false;

	// if the stack is not empty...
	if (Top != NULL)
	{
		// store what the top node's value in popped node
		poppedCoordinate = Top->Element;

		// make a new pointer to point to the node for deletion
		Node* nodeToDelete = new Node;

		// target the top value
		nodeToDelete = Top;

		// move top to the next node (if it's the stack's last node it will store NULL in Top)
		Top = Top->Next;

		// delete node marked for deletion
		delete nodeToDelete;

		// mark that the pop is successful
		popSuccessful = true;
	}

	// return flag variable
	return popSuccessful;
}
// class implementation

#include <iostream>
#include <string>
#include "BST.h"



// constructor
BST::BST()
{
	Root = NULL;
}



// destructor
BST::~BST()
{
	DeleteTree(Root);
	Root = NULL;
}



// insert a node into the BST
bool BST::Insert(string newLine)
{
	bool insertSuccessful = false;

	Node* newNode = new Node;
	newNode->Line = newLine;
	newNode->Rt = NULL;
	newNode->Lt = NULL;

	if (Root == NULL)
	{
		Root = newNode;
		insertSuccessful = true;
	}
	else if (Root != NULL)
	{
		////////////////////////////////////////////////////// LOCATE WHERE THE NEW NODE BELONGS 
		Node* currentNode = Root; 
		Node* currentNodesTrailer = Root; 

		while (currentNode != NULL)
		{
			if (newNode->Line < currentNode->Line)
			{
				currentNodesTrailer = currentNode;
				currentNode = currentNode->Lt;
			}
			else if (newNode->Line > currentNode->Line)
			{
				currentNodesTrailer = currentNode;
				currentNode = currentNode->Rt;
			}
		}

		////////////////////////////////////////////////////// INSERT THE NEW NODE INTO THE BST
		if (newNode->Line < currentNodesTrailer->Line)
		{
			currentNodesTrailer->Lt = newNode;
			insertSuccessful = true;
		}
		else if (newNode->Line > currentNodesTrailer->Line)
		{
			currentNodesTrailer->Rt = newNode;
			insertSuccessful = true;
		}
	}

	return insertSuccessful;
}



// delete a node from the BST
bool BST::Delete(string targetInfo)
{
	bool deleteSuccessful = false;
	bool targetInfoFound = false;

	Node* selectedNode = Root;
	Node* selectedNodesParent = selectedNode;

	if (Root != NULL)
	{

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////// LOCATE TARGET NODE IN BST

		while ((selectedNode->Line != targetInfo) && (selectedNode->Lt != NULL || selectedNode->Rt != NULL)) // until the target info has been found or until all possible nodes have been searched...
		{
			if (targetInfo < selectedNode->Line) // if the target info is less than the selected node's info...
			{
				selectedNodesParent = selectedNode; // update trailer pointer
				selectedNode = selectedNode->Lt; // traverse left
			}
			else if (targetInfo > selectedNode->Line) // if the target info is greater than the selected node's info...
			{
				selectedNodesParent = selectedNode; // update trailer pointer
				selectedNode = selectedNode->Rt; // traverse right
			}
		}

		if (targetInfo == selectedNode->Line)
		{
			targetInfoFound = true;
		}

		if (targetInfoFound == true) // if the target info was found... the next step is to identify the type of deletion 
		{

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////// DELETE ROOT CASE

			if (selectedNode == Root && selectedNode->Lt == NULL && selectedNode->Rt == NULL) // if the selected node is the Root and also the last node...
			{
				Root = NULL; // set Root to NULL signaling that the tree is empty
				delete selectedNode; // remove the last node in the BST that was previously pointed to by Root
				deleteSuccessful = true;
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////// DELETE LEAF CASE

			else if (selectedNode->Lt == NULL && selectedNode->Rt == NULL) // if the selected node is a leaf...
			{
				if (selectedNodesParent->Lt == selectedNode) // if the selected node is the left child of its parent...
				{
					selectedNodesParent->Lt = NULL; // cut the left child off
				}
				else if (selectedNodesParent->Rt == selectedNode) // if the selected node is the right child of its parent...
				{
					selectedNodesParent->Rt = NULL; // cut the right child off
				}

				delete selectedNode; // remove leaf
				deleteSuccessful = true;
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////// DELETE ONE CHILD CASE

			else if (selectedNode->Lt != NULL && selectedNode->Rt == NULL) // if the selected node only has a left child...
			{
				if (selectedNodesParent->Lt == selectedNode) // if the selected node is the left child of its parent...
				{
					selectedNodesParent->Lt = selectedNode->Lt; // make the parent point to the soon-to-be-deleted node's left child
				}
				else if (selectedNodesParent->Rt == selectedNode) // if the selected node is the right child of its parent...
				{
					selectedNodesParent->Rt = selectedNode->Lt; // make the parent point to the soon-to-be-deleted node's left child
				}

				delete selectedNode; // remove node
				deleteSuccessful = true;
			}
			else if (selectedNode->Lt == NULL && selectedNode->Rt != NULL) // if the selected node only has a right child...
			{
				if (selectedNodesParent->Lt == selectedNode) // if the selected node is the left child of its parent...
				{
					selectedNodesParent->Lt = selectedNode->Rt; // make the parent point to the soon-to-be-deleted node's right child
				}
				else if (selectedNodesParent->Rt == selectedNode) // if the selected node is the right child of its parent...
				{
					selectedNodesParent->Rt = selectedNode->Rt; // make the parent point to the soon-to-be-deleted node's right child
				}

				delete selectedNode; // remove node
				deleteSuccessful = true;
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////// DELETE TWO CHILDREN CASE

			else if (selectedNode->Lt != NULL && selectedNode->Rt != NULL) // if the selected node has a left child and a right child...
			{
				Node* closestSuccessor = selectedNode; // create node pointer to traverse to the closest successor 
				Node* closestSuccessorsParent = closestSuccessor;

				if (closestSuccessor->Rt != NULL) // if there is an existing right child...
				{
					closestSuccessorsParent = closestSuccessor; // update trailer pointer
					closestSuccessor = closestSuccessor->Rt; // traverse right once
				}

				while (closestSuccessor->Lt != NULL) // until you find a left child pointer that is NULL
				{
					closestSuccessorsParent = closestSuccessor; // update trailer pointer
					closestSuccessor = closestSuccessor->Lt; // continue stepping left
				}

				selectedNode->Line = closestSuccessor->Line; // copy closest successor's value into the selected node


				if (closestSuccessorsParent->Lt == closestSuccessor)
				{
					closestSuccessorsParent->Rt = closestSuccessor->Rt;
				}
				else if (closestSuccessorsParent->Rt == closestSuccessor)
				{
					closestSuccessorsParent->Rt = closestSuccessor->Rt;
				}

				delete closestSuccessor;
				deleteSuccessful = true;
			}
		}
	}
	return deleteSuccessful;
}



// edit a node in the tree
bool BST::Edit(string infoToEdit, string replacementInfo)
{
	bool editSuccessful = false;

	if (Root != NULL && Delete(infoToEdit) == true && Insert(replacementInfo) == true)
	{
		editSuccessful = true;
	}

	return editSuccessful;
}



// print out the entire BST in sorted order
void BST::Print()
{
	inorderPrint(Root);
}



// release all node storage back to the OS, called from destructor
void BST::DeleteTree(Node* pointer)
{
	// Base case: empty tree
	if (pointer == NULL)
	{
		return;
	}

	DeleteTree(pointer->Lt);
	DeleteTree(pointer->Rt);

	delete pointer;
}



// recursive function to print out BST in sorted order, called from Print
void BST::inorderPrint(Node* pointer)
{
	if (pointer != NULL)
	{
		inorderPrint(pointer->Lt);
		cout << pointer->Line << endl;
		inorderPrint(pointer->Rt);
	}
}
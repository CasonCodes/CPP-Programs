// class definition

/**************************************************************************************
	File:	BST.h
	Des:	This file contains the class definition for a Binary Search Tree (BST).
			It containsthe functionality to Insert into, Delete from, Edit a node,
			and print all nodes in the tree.

	Author: Coach Rags
**************************************************************************************/

#include <string>
using namespace std;

// a node for a BST, Lt will point to items less than parent and Rt
// points to items greater than the parent
struct Node
{
	string Line;
	Node* Lt;
	Node* Rt;
};

// Class definition for a Binary Searcy Tree, standard functionality
class BST
{
public:
	// constructor
	BST();

	// destructor
	~BST();

	// insert a node into the BST
	bool Insert(string);

	// delete a node from the BST
	bool Delete(string);

	// edit a node in the tree
	bool Edit(string, string);

	// print out the entire BST in sorted order
	void Print();

private:
	// release all node storage back to the OS, called from destructor
	void DeleteTree(Node*);

	// recursive function to print out BST in sorted order, called from Print
	void inorderPrint(Node*);

	Node* Root;
};
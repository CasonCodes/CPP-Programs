// main program

/******************************************************************************
Name: TestDriver.cpp
Des: This program is designed to test the base functionality of the Binary
Searcy Tree ADT implemented dynamically. The program will obtain data
from a file of strings (one string per line).  The user will be queried for the
name of the text file; if it does not exist the program will exit.  Otherwise,
the program will build a Binary Search Tree to contain the string data.  If the build
is successful, a menu will be provided for the user allowing he/she to delete,
edit, or print the list.  When the program is over, the memory allocated for
all the nodes in the Binary Search Tree will be released back to the system.
This test program will also test for memory leaks by using the header vld.h.
If memory leaks exist, a report will be generated at the end of execution
noting what memory locations were not deallocated.
Author: Coach Rags
******************************************************************************/
#include<iostream>
#include<fstream>
#include<string>
//check for memory leaks, will be commented out during development
//#include<vld.h> 
#include "BST.h"

using namespace std;

/******************************************************************************
Name: Menu
Des: Menu will display a menu with three options (delete,edit,print) and will
return the option to the call after first ensuring it is uppercase.
******************************************************************************/
void Menu(char& opt)
{
	string input;

	cout << endl;
	cout << "Enter D to delete item from the list" << endl;
	cout << "Enter E to edit an item in the list" << endl;
	cout << "Enter P to print out the items in the list" << endl;
	cout << "OPTION? ";
	getline(cin, input);
	opt = toupper(input[0]);
	cout << endl;
}

/******************************************************************************
Name: buildList
Des: buildList will accept a list object first and then query the user for the
name of an input file to obtain data.  The function will read this text file
one line at a time and will insert each line into the list object.  If the file
does not exist or could not be opened for some reason, the function returns
false to the call.  Also, if the List Insert function fails, a memory
allocation error is displayed and buildStatus becomes false.
******************************************************************************/
bool buildList(BST& tdList)
{
	ifstream fin;
	string fData, fName;
	bool buildStatus = true;

	// Logic to get input file name and attempt to open file
	//cout << "Name of input file: ";
	//getline(cin, fName);
	fin.open("Text.txt");

	/* If file open succeeds, the data file is read one line at a time and
	inserted into the list object.  The file is closed at the end of
	reading. If file did not open, error message is displayed and
	buildStatus becomes false.
	*/
	if (fin.good())
	{
		getline(fin, fData);
		while (buildStatus == true && !fin.eof())
		{
			// Make sure the Insert worked, if not, memory allocation failed
			if (tdList.Insert(fData))
			{
				getline(fin, fData);
			}
			else
			{
				cout << "memory allocation error" << endl;
				buildStatus = false;
			}
		}
		fin.close();
	}
	else
	{
		cout << "cannot open file" << endl;
		buildStatus = false;
	}

	/* True is returned if the file was successfully read and all calls to the
	List Insert function were successful.  False is returned if the file
	could not be opened or a memory allocation error occured in Insert.
	*/
	return buildStatus;
}

/******************************************************************************
Name: TestDelete
Des: TestDelete will obtain data from the user that should match data in the
List.  The List Delete function is called and will return if the data was or
was not deleted.
******************************************************************************/
void TestDelete(BST& tdList)
{
	string itemToDelete;

	cout << "Enter the item to delete: ";
	getline(cin, itemToDelete);

	// List::Delete will return true if item deleted, false othewise
	if (tdList.Delete(itemToDelete))
	{
		cout << "Item deleted" << endl;
	}
	else
	{
		cout << "Item NOT deleted" << endl;
	}
}

/******************************************************************************
Name: TestEdit
Des: TestEdit will get the item to be edited and the edited text and then send
these two data elements to the List Edit function.
******************************************************************************/
void TestEdit(BST& tdList)
{
	string itemToEdit, editedItem;

	cout << "Enter item to correct: ";
	getline(cin, itemToEdit);
	cout << "Enter edited item: ";
	getline(cin, editedItem);

	if (tdList.Edit(itemToEdit, editedItem))
	{
		cout << "Item edited" << endl;
	}
	else
	{
		cout << "Item not edited" << endl;
	}
}

/******************************************************************************
Name: Print
Des: Print will accept a List object and an output file (for now cout) then
it will call the List Print function.
******************************************************************************/
void TestPrint(BST& tdList)
{
	tdList.Print();
}

/******************************************************************************
Name: Main
Des: Main will first call the function which builds the ordered linked list
from a text file.  If this is successful, a loop begins to run which displays
a menu providing three different options to the user.  The appropriate function
is called, executed and sent back to get another option from the user.  All
output generated is displayed to the screen.
******************************************************************************/
void main()
{
	BST ToDoList;

	if (buildList(ToDoList))
	{
		cout << "BST with no changes" << endl << endl;
		ToDoList.Print();
		cout << endl;
		system("pause");
		cout << endl;

		cout << "Test: Delete \"open savings acct\"" << endl << endl;
		ToDoList.Delete("open savings acct");
		ToDoList.Print();
		cout << endl;
		system("pause");
		cout << endl;

		cout << "Test: Delete \"scud\"" << endl << endl;
		ToDoList.Delete("scud");
		ToDoList.Print();
		cout << endl;
		system("pause");
		cout << endl;

		cout << "Test: Delete \"make dental appt\"" << endl << endl;
		ToDoList.Delete("make dental appt");
		ToDoList.Print();
		cout << endl;
		system("pause");
		cout << endl;

		cout << "Test: Delete \"get estimate on car repair\"" << endl << endl;
		ToDoList.Delete("get estimate on car repair");
		ToDoList.Print();
		cout << endl;
		system("pause");
		cout << endl;

		cout << "Test: Delete \"join planet fitness\"" << endl << endl;
		ToDoList.Delete("join planet fitness");
		ToDoList.Print();
		cout << endl;
		system("pause");
		cout << endl;

		cout << "Test: Edit \"daily bible reading\" to \"finish bible reading\"" << endl << endl;
		ToDoList.Edit("daily bible reading", "finish bible reading");
		ToDoList.Print();
		cout << endl;
		system("pause");
		cout << endl;

		cout << "Test: Edit \"pay bills\" to \"wash car\"" << endl << endl;
		ToDoList.Edit("pay bills", "wash car");
		ToDoList.Print();
		cout << endl;
		system("pause");
		cout << endl;

		cout << "Test: Edit \"i am a scud\" to \"I am a stud\"" << endl << endl;
		ToDoList.Edit("i am a scud", "I am a stud");
		ToDoList.Print();
		cout << endl;
		system("pause");
		cout << endl;
	}

	system("pause");
}
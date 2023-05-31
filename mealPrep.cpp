#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct Item {
	string name = "";
	bool inPantry = false;
};

struct Recipe {
	string title = "";
	vector<Item> requiredItems;
};

class Cookbook {
	vector<Recipe> allRecipes;
	void printLine();
	unsigned int getInput();
	void printList(vector<string> list);
	void printRecipe();
	void printAllRecipes();
	void addNewRecipe();
	void deleteRecipe();
	void editRecipe();
	void saveData();
public:
	void loadData();
	bool displayMenu();
};

// COMPLETE
void Cookbook::printLine() {
	cout << "----------------------------------" << endl;
}

// COMPLETE
unsigned int Cookbook::getInput() {
	cout << "\t> ";
	unsigned int input;
	cin >> input;
	return input;
}

// COMPLETE
void Cookbook::printList(vector<string> list) {
	for (unsigned int i = 0; i < list.size(); i++) {
		cout << i + 1 << ". " << list[i] << endl;
	}
}

// COMPLETE
void Cookbook::printRecipe() {
	unsigned int input = getInput() - 1;
	system("cls");
	cout << "Recipe Title: " << allRecipes[input].title << endl;
	printLine();
	for (unsigned int i = 0; i < allRecipes[input].requiredItems.size(); i++) {
		cout << i + 1 << ". " << allRecipes[input].requiredItems[i].name << endl;
	}
	cout << endl;
	system("pause");
}

// COMPLETE
void Cookbook::printAllRecipes() {
	if (allRecipes.size() == 0) {
		cout << endl << "No recipes to display!" << endl;
		system("pause");
	}
	else {
		system("cls");
		cout << "Please select a recipe to view:" << endl;
		printLine();
		for (unsigned int i = 0; i < allRecipes.size(); i++) {
			cout << i + 1 << ". " << allRecipes[i].title << " --> " << allRecipes[i].requiredItems.size() << " items" << endl;
		}
		printRecipe();
	}
}

// COMPLETE
void Cookbook::addNewRecipe() {
	system("cls");
	string input;
	cin.ignore();
	Recipe newRecipe;
	cout << "Title of Recipe: ";
	getline(cin, input);
	newRecipe.title = input;
	bool readyToQuit = false;
	printLine();
	cout << "Required items:" << endl;
	do {
		cout << "\t> ";
		getline(cin, input);
		if (input == "done") {
			readyToQuit = true;
		}
		else {
			Item newItem;
			newItem.name = input;
			newRecipe.requiredItems.push_back(newItem);
		}
	} while (!readyToQuit);
	allRecipes.push_back(newRecipe);
	cout << endl << "New Recipe Saved!" << endl;
	system("pause");
}

// COMPLETE
void Cookbook::deleteRecipe() {
	if (allRecipes.empty()) {
		cout << endl << "No recipes to delete!" << endl;
	}
	else {
		system("cls");
		cout << "Select a recipe to delete:" << endl;
		printLine();
		for (unsigned int i = 0; i < allRecipes.size(); i++) {
			cout << i + 1 << ". " << allRecipes[i].title << " --> " << allRecipes[i].requiredItems.size() << " items" << endl;
		}
		unsigned int input = getInput() - 1;
		system("cls");
		cout << "Recipe Title: " << allRecipes[input].title << endl;
		printLine();
		for (unsigned int i = 0; i < allRecipes[input].requiredItems.size(); i++) {
			cout << i + 1 << ". " << allRecipes[input].requiredItems[i].name << endl;
		}
		cout << endl << "(Y/N) Confirm deletion: ";
		char yesNo;
		cin >> yesNo;
		if (toupper(yesNo) == 'Y') {
			allRecipes.erase(allRecipes.begin() + input);
			cout << endl << "Recipe deleted!" << endl;
		}
		else {
			cout << endl << "Deletion cancelled!" << endl;
		}
	}
	system("pause");
}

// INCOMPLETE
void Cookbook::editRecipe() {
	if (allRecipes.empty()) {
		cout << endl << "No recipes to edit!" << endl;
	}
	else {
		system("cls");
		cout << "Select a recipe to edit:" << endl;
		printLine();
		for (unsigned int i = 0; i < allRecipes.size(); i++) {
			cout << i + 1 << ". " << allRecipes[i].title << " --> " << allRecipes[i].requiredItems.size() << " items" << endl;
		}
		unsigned int input = getInput() - 1;
		system("cls");
		cout << "Recipe Title: " << allRecipes[input].title << endl;
		printLine();
		for (unsigned int i = 0; i < allRecipes[input].requiredItems.size(); i++) {
			cout << i + 1 << ". " << allRecipes[input].requiredItems[i].name << endl;
		}
		unsigned int recipeNumber = input;
		input = getInput() - 1;
		cout << endl << "Edit " << allRecipes[recipeNumber].requiredItems[input].name << " to be: ";
		string newName;
		cin.ignore();
		getline(cin, newName);
		allRecipes[recipeNumber].requiredItems[input].name = newName;
		system("cls");
		cout << "Recipe Title: " << allRecipes[input].title << endl;

		printLine();
		for (unsigned int i = 0; i < allRecipes[input].requiredItems.size(); i++) {
			cout << i + 1 << ". " << allRecipes[input].requiredItems[i].name << endl;
		}
		cout << endl << "Recipe edited!" << endl;
		system("pause");
	}
}

// COMPLETE
void Cookbook::loadData() {
	ifstream inputFile;
	inputFile.open("saveFile.txt");
	if (inputFile.good()) {
		bool titleCaptured = false;
		bool recipeCaptured = false;
		bool itemCaptured = false;
		unsigned int howManyRecipes;
		inputFile >> howManyRecipes;
		for (unsigned int i = 0; i < howManyRecipes; i++) {
			string input;
			Recipe newRecipe;
			while (!recipeCaptured) {
				Item newItem;
				inputFile >> input;
				if (input == ":") { 
					titleCaptured = true;
				}
				else if (input == "|") { 
					recipeCaptured = true;
				}
				else if (input == ",") { 
					itemCaptured = true;
					newRecipe.requiredItems.push_back(newItem);
				}
				else if (titleCaptured) {
					
					newItem.name = input;
					
				}
				else {
					if (newRecipe.title == "") {
						newRecipe.title += input;
					}
					else {
						newRecipe.title += " " + input;
					}
				}
				itemCaptured = false;
			}
			allRecipes.push_back(newRecipe);
			titleCaptured = false;
			recipeCaptured = false;
		}
		inputFile.close();
	}
	else {
		cout << "Error loading Cookbook!" << endl;
	}
}

// COMPLETE
void Cookbook::saveData() {
	ofstream outputFile;
	outputFile.open("saveFile.txt");
	if (outputFile.good()) {
		outputFile << allRecipes.size() << endl;
		for (unsigned int i = 0; i < allRecipes.size(); i++) {
			outputFile << allRecipes[i].title << " : ";
			for (unsigned int x = 0; x < allRecipes[i].requiredItems.size(); x++) {

				if (x == 0) {
					outputFile << allRecipes[i].requiredItems[x].name;
				}
				else {
					outputFile << " , " << allRecipes[i].requiredItems[x].name;
				}

			}
			outputFile << "|" << endl;
		}
		outputFile.close();
		cout << endl << "Cookbook saved!";
	}
	else {
		cout << endl << "Error saving Cookbook!" << endl;
	}
}

// COMPLETE
bool Cookbook::displayMenu() {
	system("cls");
	vector<string> menuOptions = 
	{ "All Recipes","Add Recipe","Delete Recipe","Edit Recipe","Save and Quit" };
	cout << "Please select an option:" << endl;
	printLine();
	printList(menuOptions);
	cout << "\t> ";
	unsigned int input;
	cin >> input;
	switch (input) {
	case 1: printAllRecipes(); break;
	case 2: addNewRecipe(); break;
	case 3: deleteRecipe(); break;
	case 4: editRecipe(); break;
	case 5: saveData(); return true;
	default: displayMenu();
	}
	return false;
}

int main() {
	bool readyToQuit = false;
	Cookbook book;
	book.loadData();
	do {
		readyToQuit = book.displayMenu();
	} while (!readyToQuit);
}
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <fstream>
using namespace std;



// [ Grocery List App ] --> mARKETmASTER
// lets user create a list of groceries
// when the user is ready to go to the store,
// this program will scan through each item,
// ask the user if that item needs to be added
// the grocery list for the next trip to the store.



enum Status {
	Have, Need
};

struct Item {
	string itemName = "";
	Status status = Have;
};

struct Recipe {
	string recipeName = "";
	vector<Item> requiredItems;
	bool haveWhatsNeeded(vector<Item> groceryList) {
		int missingItems = 0;
		for (int i = 0; i < requiredItems.size(); i++) {
			for (int x = 0; x < groceryList.size(); x++) {
				if (requiredItems[i].itemName == groceryList[x].itemName && groceryList[i].status == Need) {
					missingItems++;
					break;
				}
			}
		}
	}
};

class MarketMaster {

	vector<Item> groceryList = {

		// MEAT 
		// ----------------------------
		{"Turkey"}, {"Bacon"}, {"Sausage"},
		{"Tuna"}, {"Ground Pork"}, {"Ground Beef"}, 
		{"Steak"}, {"Ground Turkey"},

		// FRUITS & VEGETABLES
		// ----------------------------
		{"Green Onions"}, {"Bananas"}, {"Potatoes"},
		{"Tomatoes"}, {"Serrano Peppers"}, {"Apples"},
		{"Onions"}, {"Bell Peppers"}, {"Pineapple"}, {"Avocado"}, {"Lime"},

		// GENERAL ITEMS
		// ----------------------------
		{"Wheat Bread"}, {"Pita Bread"}, {"Coffee"}, { "Water Bottles" }, { "Tea" }, { "Rice" },
		{"Pasta Sauce"}, {"Ramen Noodles"}, {"Cereal"},  {"Hot Sauce"}, 
		{"Peanut Butter"}, {"Spaghetti"},  {"Waffle Mix"}, {"Maple Syrup"},
		{"Canned Soup"}, {"Tortillas"}, {"Bagels"}, {"Chips"}, {"Soylent"}, 
		{"Muffins"}, {"Cashew Mix"}, {"Oatmeal"}, 

		// COLD ITEMS
		// ----------------------------
		{"Milk"}, {"Eggs"}, {"Butter"}, {"Toquitos"},
		{"Jelly"}, {"Lettuce"}, {"Coffee Creamer"},
		{"Soy Sauce"}, {"Mayonaise"}, {"Mustard"}, {"Hummus"},
		{"Juice"}, {"Pickles"}, {"Cheese"}, {"Ice Cream"},

		// CONDIMENTS & SEASONINGS
		// ----------------------------
		{"Sesame Seed Oil"}, {"Salt"}, {"Pepper"}, {"Olive Oil"}, 
		{"Garlic"}, {"Thyme"}, {"Italian Seasoning"}, {"Mustard"}, 
		{"Ketchup"}, {"Mayonaise"}, 

		// HYGIENE ITEMS
		// ----------------------------
		{"Shower Sponge"}, {"Vitamins"},  {"Shampoo"}, {"Conditioner"}, 
		{"Toothbrush"}, {"Toothpaste"}, {"Mouth Wash"}, {"Deodorant"}, 
		{"Face Wash"},

		// UTILITY ITEMS
		// ----------------------------
		{"Trash Bags"}, {"Dish/Hand Soap"}, {"Disinfectant Wipes/Spray"}, 
		{"Paper Towels"}, {"Cat Litter"}, {"Cat Food"}, {"Litter Deodorizer"}, 
		{"Laundry Soap"}, {"Ziploc Bags"}, {"Gloves"}, {"Candle"}

	};

	vector<Recipe> recipeList = {

		// BREAKFAST
		{ "Eggs & Toast", {{"Bread"}, {"Eggs"}, {"Butter"}, {"Salt"}, {"Pepper"}} },
		{ "Eggs & Rice", {{"Rice"}, {"Eggs"}, {"Butter"}, {"Salt"}, {"Pepper"}} },
		{ "Turkey Bagel", {{"Turkey"}, {"Eggs"}, {"Butter"}, {"Salt"}, {"Pepper"}, {"Bagels"}} },
		{ "Waffles", {{"Waffle Mix"}, {"Syrup"}, {"Olive Oil"}, {"Butter"}} },

		// LUNCH
		{ "PB&J Sandwich", {{"Peanut Butter"}, {"Jelly"}, {"Bread"}} },
		{ "Turkey Sandwich", {{"Bread"}, {"Mustard"}, {"Turkey"}, {"Tomatoes"}, {"Lettuce"}, {"Cheese"}} },
		{ "Tuna Sandwich", {{"Bread"}, {"Mayonaise"}, {"Tuna"}, {"Apples"}, {"Pickles"}} },

		// DINNER
		{ "Steak and Potatoes", {{"Steak"}, {"Olive Oil"}, {"Green Onions"}, {"Thyme"}, {"Butter"}, {"Salt"}, {"Pepper"}, {"Potatoes"}, {"Cheese"}, {"Garlic"}} },
		{ "Ramen Noodle Soup", {{"Eggs"}, {"Ground Pork"}, {"Soy Sauce"}, {"Green Onions"}, {"Garlic"}, {"Sesame Seed Oil"}, {"Ramen Noodles"}, {"Olive Oil"}} },

	};

	vector<string> mainMenu = {
		"Grocery Scan", "Pantry", "Needed Items List", "Recipe List"
	};

	void printTitleBar(string title) {
		cout << "========== [" << title << "] ==========" << endl;
	}
	int getUserInputInt(string promptSymbol = ">") {
		// prompts the user for an integer
		int input;
		cout << "\t" << promptSymbol << " ";
		cin >> input;
		system("cls");
		return input;
	}
	char getUserInputChar(string promptSymbol = ">") {
		// prompts the user for an char
		char input;
		cout << "\t" << promptSymbol << " ";
		cin >> input;
		system("cls");
		return input;
	}
	string getUserInputString(string promptSymbol = ">") {
		// prompts the user for an char
		string input;
		cout << "\t" << promptSymbol << " ";
		cin >> input;
		system("cls");
		return input;
	}
	void printList(vector<Item> list) {
		// prints a numbered list of Items and their status
		int mode = 2;
		if (mode == 1) {
			for (int i = 0; i < list.size(); i++) {
				switch (list[i].status) {
				case Need: cout << "[ ] "; break;
				case Have: cout << "[X] "; break;
				}
				cout << "(" << i + 1 << ") " << list[i].itemName << endl;
			}
		}
		else if (mode == 2) {
			// HVD = horizontal value difference (between columns)
			int HVD = list.size() / 3;

			// BUG: if (list % 3 != 0) --> does not print full list
			// TO DO: accomplish columns but full list 

			for (int i = 0; i < HVD; i++) {

				switch (list[i].status) {
				case Need: cout << "[ ] "; break;
				case Have: cout << "[X] "; break;
				}

				cout << "(" << i + 1 << ") ";
				cout << setw(30) << left << list[i].itemName;

				cout << "\t";

				switch (list[i + HVD].status) {
				case Need: cout << "[ ] "; break;
				case Have: cout << "[X] "; break;
				}

				cout << "(" << i + 1 + HVD << ") ";
				cout << setw(30) << left << list[i + HVD].itemName;

				cout << "\t";

				switch (list[i + HVD + HVD].status) {
				case Need: cout << "[ ] "; break;
				case Have: cout << "[X] "; break;
				}

				cout << "(" << i + 1 + HVD + HVD << ") ";
				cout << setw(30) << left << list[i + HVD + HVD].itemName;

				cout << endl;
			}
		}
	}
	void printList(vector<string> list) {
		// prints a numbered list of Words
		for (int i = 0; i < list.size(); i++) {
			cout << "\t(" << i + 1 << ") " << list[i] << endl;
		}
	}
	void printList(vector<Recipe> list) {
		// prints a numbered list of Words
		for (int i = 0; i < list.size(); i++) {
			cout << "\t(" << i + 1 << ") " << list[i].recipeName << endl;
		}
	}
	void displayMenu(vector<Item> items, string title) {
		printTitleBar(title);
		cout << endl;
		printList(items);
		cout << endl;
	}
	void displayMenu(vector<string> options, string title) {
		printTitleBar(title);
		cout << endl;
		printList(options);
		cout << endl;
	}
	void displayMenu(vector<Recipe> options, string title) {
		printTitleBar(title);
		cout << endl;
		printList(options);
		cout << endl;
	}
	Status flipStatus(Status status) {
		switch (status) {
		case Have: return Need;
		case Need: return Have;
		}
	}
	void displayGroceryList() {
		displayMenu(groceryList, "Grocery List");
		int input = getUserInputInt(">");
		if (input == 0) {
			system("cls");
			return;
		}
		else if (input > 0 && input <= groceryList.size()) {
			Status currentStatus = groceryList[input - 1].status;
			groceryList[input - 1].status = flipStatus(currentStatus);
		}
		system("cls");
		displayGroceryList();
	}
	void displayMissingItems() {
		vector<Item> MissingItems = getMissingItems();
		displayMenu(MissingItems, "Items Needed");
		int input = getUserInputInt(">");
		if (input == 0) {
			system("cls");
			return;
		}
		else if (input > 0 && input <= MissingItems.size()) {
			Status currentStatus = groceryList[input - 1].status;
			groceryList[input - 1].status = flipStatus(currentStatus);
		}
		system("cls");
		displayMissingItems();
	}
	vector<Item> getMissingItems() {
		// returns list of items with Status: Need
		vector<Item> items;
		for (int i = 0; i < groceryList.size(); i++) {
			if (groceryList[i].status == Need) {
				items.push_back(groceryList[i]);
			}
		}
		return items;
	}
	int indexOf(string itemName) {
		// returns index of input given, returns -1 otherwise
		for (int i = 0; i < groceryList.size(); i++) {
			if (groceryList[i].itemName == itemName) {
				return i;
			}
		}
		return -1;
	}
	static bool compareFunction(Item a, Item b) {
		return a.itemName < b.itemName;
	}
	int count(vector<Item> items) {
		return items.size();
	}
	void scanGroceryList() {
		for (int i = 0; i < groceryList.size(); i++) {
			bool validEntry = false;
			do {
				system("cls");
				printTitleBar("Grocery List Scan");
				cout << endl;
				cout << "\t(" << i + 1 << "/" << groceryList.size() << "): " << groceryList[i].itemName << endl;
				cout << endl;
				cout << "(B)ack" << endl;
				switch (toupper(getUserInputChar("Need this? (Y/N):"))) {
				case 'Y': groceryList[i].status = Need; validEntry = true; break;
				case 'N': groceryList[i].status = Have; validEntry = true; break;
				case '0': system("cls"); return;
				}
			} while (!validEntry);
		}
	}
	void displayRecipeList() {
		displayMenu(recipeList, "Recipe List");
		int input = getUserInputInt(">");
		if (input == 0) {
			system("cls");
			return;
		}
		else if (input > 0 && input <= recipeList.size()) {
			// TO DO: what happens when user selects a recipe
		}
		system("cls");
		displayRecipeList();
	}
	void displaySplashScreen() {
		cout << "             00000000    00000000  00   00  00000000  00000000                  " << endl;
		cout << "            0000000000  000000000  00  00   00000000  00000000            " << endl;
		cout << "  00  00    00      00  00     00  00 00    00           00            " << endl;
		cout << " 00000000   00      00  00    00   0000     00000000     00                  "  << endl;
		cout << "00  00  00  0000000000  000000     0000     00000000     00                 " << endl;
		cout << "00  00  00  00      00  00   00    00 00    00           00             " << endl;
		cout << "00      00  00      00  00    00   00  00   00000000     00              " << endl;
		cout << "00      00  00      00  00     00  00   00  00000000     00                   " << endl;
		cout << "-------------------------------------------------------------------------------|> " << endl;
		cout << "                     00000000    00000000  00000000  00000000   00000000                " << endl;
		cout << "                    0000000000  000000000  00000000  00000000  000000000          " << endl;
		cout << "          00  00    00      00  00            00     00        00     00    " << endl;
		cout << "         00000000   00      00  00            00     00000000  00    00                 " << endl;
		cout << "        00  00  00  0000000000  000000        00     00000000  000000                  " << endl;
		cout << "        00  00  00  00      00       00       00     00        00   00       " << endl;
		cout << "        00      00  00      00        00      00     00000000  00    00             " << endl;
		cout << "        00      00  00      00  0000000       00     00000000  00     00                 " << endl;
		cout << endl;
		cout << "Created by Cason Kirschner" << endl;
		system("pause");
		system("cls");
	}
	bool load() {
		fstream inputFile;
		inputFile.open("groceryAppSave.txt");
		if (inputFile.is_open()) {
			groceryList.clear();
			string input;
			int status;

			// read grocery list
			do {
				inputFile >> input;
				if (input == "RECIPES") {
					break;
				}
				else {
					inputFile >> status;
					groceryList.push_back({ input, (Status)status });
				}				
			} while (!inputFile.eof());

			// read recipes
			do {
				inputFile >> input;

			} while (!inputFile.eof());

			return true;
		}
		else {
			return false;
		}
	}
	bool save() {
		fstream outputFile;
		outputFile.open("groceryAppSave.txt");
		if (outputFile.is_open()) {

			// save groceries
			for (int i = 0; i < groceryList.size(); i++) {
				outputFile << groceryList[i].itemName << "\t" << groceryList[i].status << endl;
			}

			outputFile << endl << "RECIPES" << endl;

			// save recipes with their items
			for (int i = 0; i < recipeList.size(); i++) {
				for (int x = 0; x < recipeList[i].requiredItems.size(); x++) {
					outputFile << recipeList[i].recipeName << endl;
					outputFile << "\t" << recipeList[i].requiredItems[x].itemName << endl;
				}
				// marks end of recipe
				outputFile << "*" << endl << endl;
			}
			return true;
		}
		else {
			return false;
		}
	}
	void printNeededList() {
		fstream outputFile;
		outputFile.open("groceryAppSave.txt", ios::out);

		// save needed groceries
		for (int i = 0; i < groceryList.size(); i++) {
			if (groceryList[i].status == Need) {
				outputFile << groceryList[i].itemName << endl;
			}
		}
			

	}

public:

	void startApplication() {
		//load();
		int input = 0;
		bool readyToQuit = false;
		displaySplashScreen();
		do {
			sort(groceryList.begin(), groceryList.end(), compareFunction);
			displayMenu(mainMenu, "Main Menu");
			double percentage = 100 * ((double)count(getMissingItems()) / (double)groceryList.size());
			cout << "You have " << 100 - (int)percentage << "% of the items on your grocery list." << endl;
			cout << endl;
			switch (getUserInputInt(">")) {
			case 0: readyToQuit = true; break;
			case 1: scanGroceryList(); break;
			case 2: displayGroceryList(); break;
			case 3: displayMissingItems(); break;
			case 4: displayRecipeList(); break;
			}
		} while (!readyToQuit);
		//save();
		printNeededList();
	}

};



int main() {
	MarketMaster mm;
	mm.startApplication();
}

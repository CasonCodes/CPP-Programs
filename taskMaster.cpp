#include <iostream>
#include <string>
#include <vector>
using namespace std;

// elaborate on the relationship between Roger Penrose's 'Presumption of an analog between the theory of quantum uncertainty and measurement' and 'Godelle's Theroem'

struct Date {
	int month, day;
	int hour, minute;
};

struct Task {
	string title = "NEW TASK";
	string description = "N/A";
};

enum Order {
	none,
	custom,
	difficulty,
	efficiency,
	date
};

struct List {
	vector<Task> tasks;
	Order sortingOrder = none;
};

struct Menu {
	string title = "";
	vector<string> items;
	Menu(string t, vector<string> i) {
		title = t;
		items = i;
	}
};

class TaskMaster {
private:
	int activeList = 0;
	Menu mainMenu;
	vector<List> allLists;
	vector<string> itemsOf(List list) {
		vector<string> items;
		for (int i = 0; i < list.tasks.size(); i++) {
			items.push_back(list.tasks[i].title);
		}
	}
	int showMenu(Menu menu) {
		if (menu.title != "") {
			cout << "[ " << menu.title << " ]" << endl;
			cout << endl;
		}
		if (menu.items.empty() == false) {
			for (int i = 0; i < menu.items.size(); i++) {
				cout << i + 1 << ") " << menu.items[i] << endl;
			}
			cout << endl;
			cout << "> ";
			int userInput;
			cin >> userInput;
			cout << endl;
			return userInput;
		}
	}
public:
	void start() {
		mainMenu = { "Main Menu", itemsOf(allLists[activeList])};
		showMenu(mainMenu);
	}	
};

int main() {
	TaskMaster tm;
	tm.start();
}













#include <iostream>
#include <vector>
#include <string>
using namespace std;

// get all the passengers to the opposite side

enum class Entity {
	none = 'n',
	person = 'p',
	fox = 'f',
	chicken = 'c',
	grain = 'g'
};
enum class Side {
	left, right
};
struct Passenger {
	Entity name;
	Side side;
	Entity enemy;
};
vector<Passenger> allPassengers = {
		{ Entity::person,	Side::left,  Entity::none},
		{ Entity::fox,		Side::left,  Entity::none},
		{ Entity::chicken,  Side::left,  Entity::fox},
		{ Entity::grain,	Side::left,  Entity::chicken}
};
void printAllPassengers() {
	for (int i = 0; i < allPassengers.size(); i++) {
		if (allPassengers[i].side == Side::left) {
			switch (allPassengers[i].name) {
				case Entity::person: cout << "Person" << endl; break;
				case Entity::fox: cout << "Fox" << endl; break;
				case Entity::chicken: cout << "Chicken" << endl; break;
				case Entity::grain: cout << "Grain" << endl; break;
			}
		}
		else if (allPassengers[i].side == Side::right) {
			switch (allPassengers[i].name) {
			case Entity::person: cout << "\t\tPerson" << endl; break;
			case Entity::fox: cout << "\t\tFox" << endl; break;
			case Entity::chicken: cout << "\t\tChicken" << endl; break;
			case Entity::grain: cout << "\t\tGrain" << endl; break;
			}
		}
	}
	cout << endl;
}
bool puzzleNotSolved() {
	for (int i = 0; i < allPassengers.size(); i++) {
		if (allPassengers[i].side == Side::left) {
			return true;
		}
	}
	return false;
}
bool allPassengersAreSafe() {
	for (int i = 0; i < allPassengers.size(); i++) {
		for (int x = 0; x < allPassengers.size(); x++) {
			if (allPassengers[i].name != allPassengers[x].name) {
				if (allPassengers[i].enemy == allPassengers[x].name) { 
					if (allPassengers[i].side == allPassengers[x].side) {
						for (int y = 0; y < allPassengers.size(); y++) {
							if (allPassengers[y].name == Entity::person) {
								if (allPassengers[y].side == allPassengers[x].side) {
									return true;
								}
							}
						}
						return false;
					}
				}
			}
		}
	}
	return true;
}



void makeMove() {
	cout << "Move ";
	string input;
	cin >> input;
	for (int i = 0; i < allPassengers.size(); i++) {
		if ((char)allPassengers[i].name == input[0]) {
			if (allPassengers[i].side == Side::left) {
				allPassengers[i].side = Side::right;
				for (int x = 0; x < allPassengers.size(); x++) {
					if (allPassengers[x].name == Entity::person) {
						allPassengers[x].side = Side::right;
					}
				}
			}
			else if (allPassengers[i].side == Side::right) {
				allPassengers[i].side = Side::left;
				for (int x = 0; x < allPassengers.size(); x++) {
					if (allPassengers[x].name == Entity::person) {
						allPassengers[x].side = Side::left;
					}
				}
			}
			else {
				cout << "[Invalid move!]" << endl;
			}
		}
	}
	if (puzzleNotSolved()) {
		cout << "Game win!" << endl;
	}
}

int main() {
	do {
		system("cls");
		cout << "LEFT SIDE\tRIGHT SIDE" << endl;
		cout << "=========\t==========" << endl;
		printAllPassengers();

		if (allPassengersAreSafe()) {
			cout << "[Everything is safe!]" << endl;
		}
		else {
			cout << "[Something got eaten!]" << endl;
		}
		
		if (puzzleNotSolved()) {
			makeMove();
		}

	} while (puzzleNotSolved());
}














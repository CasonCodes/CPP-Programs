#include <iostream>
#include <string>
using namespace std;

enum coinFace {
	heads,
	tails
};

int stringToInt(string text) {
	int conversion = 0;
	for (int i = 0; i < text.size(); i++) {
		conversion += (int)text[i];
	}
	return conversion;
}

coinFace coinFlip() {
	switch (rand() % 2) {
	case 0: return heads;
	case 1: return tails;
	}
}

struct Player {
	coinFace callCoin() {
		string playersGuess;
		cout << "heads or tails: ";
		cin >> playersGuess;
		if (playersGuess == "heads") 
			return heads;
		else 
			return tails;
	}
	void attack(Player& defender) {
		cout << name << " has decided to attack " << defender.name << " \t\t-[*-*]-  -[^-^]-" << endl;
		cout << name << ", ";
		if (coinFlip() == callCoin()) {
			cout << name << " called the coin flip right!" << endl;
			cout << name << " attacks " << defender.name << " \t\t\t\t[*-*]=!  -['o']-" << endl;
			cout << defender.name << ", ";
			if (coinFlip() == defender.callCoin()) {
				cout << defender.name << " called the coin flip right!" << endl;
				cout << defender.name << " blocked " << name << "'s attack \t\t\t[o_o]=?  [+]=[^.^]" << endl;
			}
			else {
				cout << defender.name << " called the coin flip wrong" << endl;
				cout << defender.name << " failed to block the attack from " << name << " \t[*O*]=! -[x_x]-" << endl;
				cout << defender.name << "'s health: " << defender.health << " -> ";
				defender.health -= (strength - defender.defense);
				cout << defender.health << endl;
			}
		}
		else {
			cout << name << " called the coin flip wrong!" << endl;
			cout << name << " attacks " << defender.name << ", but misses! \t\t[;-;]=!  -[^o^]" << endl;
		}
		cout << endl;
		cout << "==========================================" << endl;
		cout << endl;
	}
	string name = "";
	int defense = 0;
	int strength = 0;
	int level = 0;
	int health = 10;
	bool isAlive() { return health > 0; };
};

void disabledmain() {
	Player you = {"Cason", 2, 5};
	Player opponent = {"Gabriel Foust", 3, 6};
	int turnNumber = 0;
	do {
		cout << "\t\t\t\t\t\t\tAttacker | Defender" << endl;
		turnNumber++;
		cout << "TURN #" << turnNumber << endl;
		you.attack(opponent);
		
		turnNumber++;
		cout << "TURN #" << turnNumber << endl;
		opponent.attack(you);

		system("pause");
		system("cls");
	} while (you.isAlive() && opponent.isAlive());

	if (you.isAlive()) {
		cout << you.name << " wins!" << endl;
	}
	else if (opponent.isAlive()) {
		cout << opponent.name << " wins!" << endl;
	}
}
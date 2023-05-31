#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <windows.h>
using namespace std;

enum class Weapon {
	fists = 0,
	sword = 15,
	axe = 20
};

enum class Equipment {
	nothing = 0,
	shield = 10
};

struct Player {
	string name = "_____";
	Weapon weapon = Weapon::fists;
	Equipment equipment = Equipment::nothing;
	int healthPoints = 100;
	int attackPoints() { return (int)weapon; }
	int defensePoints() { return (int)equipment; };
	bool isAlive() { return healthPoints > 0; }

	void attack(Player& target) {

		srand((unsigned)time(0));
		int waitTime = rand();
		Sleep(waitTime / 10 );


		srand((unsigned)time(0));
		int randomNumber = rand();

		if (randomNumber % 2 == 0) {
			if (attackPoints() > target.defensePoints()) {
				target.healthPoints -= (attackPoints() - target.defensePoints());
				cout << name << "\t dealt " << (attackPoints() - target.defensePoints())
					<< " damage to \t" << target.name << "!" << endl;
			}
			else {
				cout << name << "'s attack was ineffective - " << target.name
					<< " took no damage!" << endl;
			}
		}
		else {
			cout << target.name << "\t dodged " << name << "'s attack!" << endl;
		}
	}
};

int main() {


	// create players
	Player playerOne = { "Cason", Weapon::sword, Equipment::shield };
	Player playerTwo = { "Kyle", Weapon::sword, Equipment::shield };


	// start fight
	while (playerOne.isAlive() && playerTwo.isAlive()) {
		
		if (playerOne.isAlive()) {
			playerOne.attack(playerTwo);
		}

		if (playerTwo.isAlive()) {
			playerTwo.attack(playerOne);
		}

	}


	// announce winner
	if (playerOne.isAlive()) {
		cout << playerOne.name << " arises victorious!" << endl;
	}
	else {
		cout << playerTwo.name << " arises victorious!" << endl;
	}
}
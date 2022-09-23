#include <iostream>
#include <string>
using namespace std;

// Rock, Paper, Scissors //

struct Player {
	int move;
	int wins;
	int losses;
	int number;
	bool winner;
};

struct RPSMatch {
	Player One;
	Player Two;
	bool gameComplete;
};

void getMoveFromPlayer(Player& thePlayer) {
	cout << "Player " << thePlayer.number << ":" << endl
		<< "    - Enter 1 for Rock" << endl
		<< "    - Enter 2 for Paper" << endl
		<< "    - Enter 3 for Scissors" << endl
		<< "\t> ";
	cin >> thePlayer.move;
}

void decideWinner(Player& One, Player& Two) {
	switch (One.move - Two.move) {
	case -2: One.wins++; Two.losses++; break;
	case -1: One.losses++; Two.wins++; break;
	case 0: break;
	case 1: One.wins++; Two.losses++; break;
	case 2: One.losses++; Two.wins++; break;
	}
}

void checkGame(RPSMatch& theRPSMatch) {
	if (theRPSMatch.One.wins == 3) {
		theRPSMatch.One.winner = true;
		theRPSMatch.gameComplete = true;
	}
	else if (theRPSMatch.Two.wins == 3) {
		theRPSMatch.Two.winner = true;
		theRPSMatch.gameComplete = true;
	}
}

void printRPSMatchReport(RPSMatch& theRPSMatch) {
	cout << "Player " << theRPSMatch.One.number << " \t\t" << "Player " << theRPSMatch.Two.number << endl;
	cout << "----------------------------------" << endl;
	cout << "Wins: " << theRPSMatch.One.wins << " \t\t" << "Wins: " << theRPSMatch.Two.wins << endl;
	cout << "Losses: " << theRPSMatch.One.losses << " \t\t" << "Losses: " << theRPSMatch.Two.losses << endl;
	cout << "Last Move: " << theRPSMatch.One.move << " \t\t" << "Last Move: " << theRPSMatch.Two.move << endl;
}

int main() {
	Player One = { 0, 0, 0, 1, false };
	Player Two = { 0, 0, 0, 2, false };
	RPSMatch theRPSMatch = { One, Two, false };

	while (theRPSMatch.gameComplete == false) {
		system("cls");
		getMoveFromPlayer(theRPSMatch.One);
		system("cls");
		getMoveFromPlayer(theRPSMatch.Two);
		system("cls");
		decideWinner(theRPSMatch.One, theRPSMatch.Two);
		printRPSMatchReport(theRPSMatch);
		system("pause");
		system("cls");
		checkGame(theRPSMatch);
	}
	system("cls");
	printRPSMatchReport(theRPSMatch);
	cout << "Winner: " << theRPSMatch.One.winner << " \t\t" << "Winner: " << theRPSMatch.Two.winner << endl;
}
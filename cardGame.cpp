#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

	struct Card {
		char value = '0';
		char suit = '0';
		bool faceUp = true;
		bool outOfGame = false;
	};



	struct Hand {
		Card handCards[7] = 
		{	{'0', '0', false, false}, 
			{'0', '0', false, false}, 
			{'0', '0', false, false}, 
			{'0', '0', false, false},
			{'0', '0', false, false},
			{'0', '0', false, false},
			{'0', '0', false, false}
		};
	};



	struct Deck {
		Card deckCards[4][13] = 
		{ 
			{ {'A', 'H'}, {'2', 'H'}, {'3', 'H'}, {'4', 'H'}, {'5', 'H'}, {'6', 'H'}, {'7', 'H'}, {'8', 'H'}, {'9', 'H'}, {'T', 'H'}, {'J', 'H'}, {'Q', 'H'}, {'K', 'H'} },
			{ {'A', 'D'}, {'2', 'D'}, {'3', 'D'}, {'4', 'D'}, {'5', 'D'}, {'6', 'D'}, {'7', 'D'}, {'8', 'D'}, {'9', 'D'}, {'T', 'D'}, {'J', 'D'}, {'Q', 'D'}, {'K', 'D'} },
			{ {'A', 'S'}, {'2', 'S'}, {'3', 'S'}, {'4', 'S'}, {'5', 'S'}, {'6', 'S'}, {'7', 'S'}, {'8', 'S'}, {'9', 'S'}, {'T', 'S'}, {'J', 'S'}, {'Q', 'S'}, {'K', 'S'} },
			{ {'A', 'C'}, {'2', 'C'}, {'3', 'C'}, {'4', 'C'}, {'5', 'C'}, {'6', 'C'}, {'7', 'C'}, {'8', 'C'}, {'9', 'C'}, {'T', 'C'}, {'J', 'C'}, {'Q', 'C'}, {'K', 'C'} } 
		};
	};
	


	bool shuffleDeck(Deck& theDeck) {
		bool success = false;
		for (int timesShuffled = rand() % 4; timesShuffled < rand() % 100; timesShuffled++) {
			for (int x = 0; x < 4; x++) {
				for (int y = 0; y < 13; y++) {

					// draw the next card in the deck
					char holdValue = theDeck.deckCards[x][y].value;
					char holdSuit = theDeck.deckCards[x][y].suit;
					
					// draw a random card to swap with in the deck
					int randomX = rand() % 4; // between 0-3
					int randomY = rand() % 13; // between 0-12

					// place the random card where the currently held card was
					theDeck.deckCards[x][y].value = theDeck.deckCards[randomX][randomY].value;
					theDeck.deckCards[x][y].suit = theDeck.deckCards[randomX][randomY].suit;

					// put the currently held card where the random card was
					theDeck.deckCards[randomX][randomY].value = holdValue;
					theDeck.deckCards[randomX][randomY].suit = holdSuit;
				}
			}
		}
		success = true;
		return success;
	}



	bool displayCards(Deck theDeck) {
		bool success = false;

		cout << endl;

		for (int row = 0; row < 4; row++) {
			cout << "\t";
			for (int column = 0; column < 13; column++) {
				cout << "[" << theDeck.deckCards[row][column].value << " " << theDeck.deckCards[row][column].suit << "]  ";
			}
			cout << endl;
		}

		success = true;
		return success;
	}



	bool displayCards(Hand myHand) {
		bool success = false;

		cout << endl;

		for (int count = 0; count < 7; count++) {

			cout << "\t[";

			if (myHand.handCards[count].faceUp == true) {
				cout << myHand.handCards[count].value << " " << myHand.handCards[count].suit;
			}
			else {
				cout << "  ";
			}

			cout << "]  ";
		}

		cout << endl;
		success = true;
		return success;
	}

	bool displayTable(Deck theDeck, Hand myHand) {
		bool success = false;



		return success;
	}

	int main() {

		int choice;
		Hand dealersHand;
		Hand myHand;
		Deck theDeck; 
		string userName;

		cout << endl << "\tName: ";
		cin >> userName;
		system("cls");
		cout << endl << "\tWelcome." << endl << endl << "\t";
		system("pause");

		do {

			system("cls");
			cout << endl;
			cout << "\t1. Shuffle the Deck." << endl;
			cout << "\t2. Display the Deck." << endl;
			cout << "\t3.  Display my Hand." << endl;
			cout << "\t4.                  " << endl;
			cout << "\t5.                  " << endl;

			cout << endl << "\tEnter the number of chosen function: ";
			cin >> choice;

			switch (choice) {
			
			case 1:

				if (shuffleDeck(theDeck))
					cout << endl << "\tCards Shuffled..." << endl;
				else
					cout << "/!\\ shuffleDeck(theDeck) == false /!\\" << endl;
				break;

			case 2:

				if (displayCards(theDeck))
					cout << endl << "\tCards Displayed..." << endl;
				else
					cout << "/!\\ displayCards(theDeck) == false /!\\" << endl;
				break;

			case 3:

				if (displayCards(myHand))
					cout << endl << "\tCards Displayed..." << endl;
				else
					cout << "/!\\ displayCards(myHand) == false /!\\" << endl;
				break;

			case 4: 

				if (displayTable(theDeck, myHand))
					cout << endl << "\tGame Start..." << endl;
				else
					cout << "/!\\ displayTable(theDeck, myHand) /!\\" << endl;
				break;

			case 5: 
				
				
				break;

			case -1:

				break;

			default: 

				system("cls"); 
				cout << endl << "\tInvalid option." << endl;
				break;

			}

			cout << endl << "\t";
			system("pause");

		}  while (choice != -1);

		// deal card to dealer and player
		// deal second to dealer face down and player face up
	}

	// 
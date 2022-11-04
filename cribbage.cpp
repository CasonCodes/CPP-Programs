#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


// Written By: cason Kirschner
// Project: Cribbage Scores


// FAILS TEST CASES: 15, 19, 22




enum Suit {
	hearts   = 'H',
	diamonds = 'D',
	clubs	 = 'C',
	spades   = 'S'
};

enum Value {
	joker,  
	ace, 
	two, 
	three, 
	four, 
	five, 
	six, 
	seven, 
	eight, 
	nine, 
	ten, 
	jack, 
	queen, 
	king	
};

struct Card {
	Suit suit;
	Value value;
	bool scored = false;
};

bool compareByValue(Card& a, Card& b) {
	return a.value < b.value;
}
vector<vector<vector<int>>> sets {
	{ // sets of 0
		
	},
	{ // sets of 1
		{0}, {1}, {2}, {3}, {4}
	},
	{ // sets of 2
		{0, 1}, {0, 2},
		{0, 3}, {0, 4},
		{1, 2}, {1, 3},
		{1, 4}, {2, 3},
		{2, 4}, {3, 4}
	},
	{ // sets of 3
		{0, 1, 2}, {0, 1, 3},
		{0, 2, 3}, {1, 2, 3},
		{0, 1, 4}, {0, 2, 4},
		{1, 2, 4}, {0, 3, 4},
		{1, 3, 4}, {2, 3, 4}
	},
	{ // sets of 4
		{0, 1, 2, 3},
		{0, 1, 2, 4},
		{0, 1, 3, 4},
		{0, 2, 3, 4},
		{1, 2, 3, 4}
	},
	{ // sets of 5
		{0, 1, 2, 3, 4}
	}
};

class Cribbage {
	vector<Card> hand;
	void initializeHand() {
		hand.clear();
		for (int i = 0; i < 5; i++) {
			Card newCard;
			hand.push_back(newCard);
		}
	}
	void resetScoredCards()  {
		for (int i = 0; i < hand.size(); i++) {
			hand[i].scored = false;
		}
	}
	int findPairs() {
		vector<vector<int>> setsOfTwo = {
			{0, 1}, {0, 2},
			{0, 3}, {0, 4},
			{1, 2}, {1, 3},
			{1, 4}, {2, 3},
			{2, 4}, {3, 4}
		};
		int points = 0;
		for (int i = 0; i < setsOfTwo.size(); i++) {
			if (hand[setsOfTwo[i][0]].value == hand[setsOfTwo[i][1]].value) {
				points += 2;
			}
		}
		return points;
	}
	int findMatchingSuits() {
		int points = 5;
		for (int i = 1; i < hand.size(); i++) {
			// if any any card's suit is different than the first card's
			if (hand[0].suit != hand[i].suit) {
				// if only the starter card's suit is different, else points = 0
				if (i == 4) { 
					// if the starter card is the only suit that is different
					points = 4 ;
				}
				else {
					// if one of the first four cards is different
					points = 0;
				}
				break;
			}
		}
		return points;
	}
	int findMatchingJack() {
		int points = 0;
		for (int i = 0; i < hand.size() - 1; i++) {
			if (hand[i].value == jack && hand[i].suit == hand[4].suit) {
				points = 1;
			}
		}
		return points;
	}
	int faceValueOf(Value value) {
		switch (value) {
		case joker: return 0;
		case ace:   return 1;
		case two:   return 2;
		case three: return 3;
		case four:  return 4;
		case five:  return 5;
		case six:   return 6;
		case seven: return 7;
		case eight: return 8;
		case nine:  return 9;
		case ten :  return 10;
		case jack:  return 10;
		case queen: return 10;
		case king:  return 10;
		}
	}
	int searchWithinSetsOfTwo() {
		// look for 2 card matches that == 15
		int points = 0;
		for (int i = 0; i < sets[2].size(); i++) {
			if (faceValueOf(hand[sets[2][i][0]].value) +
				faceValueOf(hand[sets[2][i][1]].value) == 15) {
				points += 2;
			}
		}
		return points;
	}
	int searchWithinSetsOfThree() {
		// look for 3 card matches that == 15
		int points = 0;
		for (int i = 0; i < sets[3].size(); i++) {
			if (faceValueOf(hand[sets[3][i][0]].value) +
				faceValueOf(hand[sets[3][i][1]].value) +
				faceValueOf(hand[sets[3][i][2]].value) == 15) {
				points += 2;
			}
		}
		return points;
	}
	int searchWithinSetsOfFour() {
		// look for 4 card matches that == 15
		int points = 0;
		for (int i = 0; i < sets[4].size(); i++) {
			if (faceValueOf(hand[sets[4][i][0]].value) +
				faceValueOf(hand[sets[4][i][1]].value) +
				faceValueOf(hand[sets[4][i][2]].value) +
				faceValueOf(hand[sets[4][i][3]].value) == 15) {
				points += 2;
			}
		}
		return points;
	}
	int searchWithinSetsOfFive() {
		// look for 5 card matches that == 15
		int points = 0;
		for (int i = 0; i < sets[5].size(); i++) {
			if (faceValueOf(hand[sets[5][i][0]].value) +
				faceValueOf(hand[sets[5][i][1]].value) +
				faceValueOf(hand[sets[5][i][2]].value) +
				faceValueOf(hand[sets[5][i][3]].value) +
				faceValueOf(hand[sets[5][i][4]].value) == 15) {
				points += 2;
			}
		}
		return points;
	}
	int findPairsOf15() {
		int points = 0;
		points += searchWithinSetsOfTwo();
		points += searchWithinSetsOfThree();
		points += searchWithinSetsOfFour();
		points += searchWithinSetsOfFive();
		return points;
	}
	int findStraights() {
		int points = 0;
		sort(hand.begin(), hand.end(), compareByValue);
		
		// begin looking for five card straights first, if straight found, stop search
		// if no 5 card straights found, start looking for 4 card straights (could be multiple)
		// if no 4 card starights found, start looking for 3 card starights (could be multiple)
		// if no 3 card straights found, there are no points rewarded to user

		// for each length of straight, looking for the largest straight possible first
		for (int targetLength = 5; targetLength >= 3; targetLength--) {		
			bool straightFound = false;

			// for each set
			for (int setIndex = 0; setIndex < sets[targetLength].size(); setIndex++) {

				// assumes currentSet is a straight
				bool setIsConsecutive = true;

				// for each index within set
				for (int x = 0; x < sets[targetLength][setIndex].size() - 1; x++) {
					Card first = hand[sets[targetLength][setIndex][x]];
					Card second = hand[sets[targetLength][setIndex][x + 1]];

					// check for consecutiveness (if difference == 1, then consecutive)
					if (second.value - first.value != 1) {

						// set is not consecutive, skip to next set
						setIsConsecutive = false;
						break;

					}
				}
				if (setIsConsecutive) {
					points += targetLength;
					straightFound = true;
				}
			}
			if (straightFound) {
				break;
			}
		}
		return points;
	}
public:
	bool getCards() {
		initializeHand();
		for (int i = 0; i < hand.size(); i++) {
			string input;
			cin >> input;
			if (input == "0") {
				return false;
			}
			Card newCard;
			switch (input[0]) {
			case 'A': newCard.value = ace; break;
			case 'T': newCard.value = ten; break;
			case 'J': newCard.value = jack; break;
			case 'Q': newCard.value = queen; break;
			case 'K': newCard.value = king; break;
			default: newCard.value = Value(input[0] - '0'); break;
			}
			newCard.suit = (Suit)input[1];
			hand[i] = newCard;
		}
		return true;
	}
	void calculateScore() {
		int totalScore = 0;
		totalScore += findPairs();			// [+2pts] per
		totalScore += findMatchingSuits();  // [+4-5pts]
		totalScore += findMatchingJack();   // [+1pts]
		totalScore += findPairsOf15();		// [+2pts] per
		totalScore += findStraights();		// [+3-5pts]
		cout << totalScore << endl;
	}
};

int main() {
	Cribbage c;
	while (c.getCards()) {
		c.calculateScore();
	}
}
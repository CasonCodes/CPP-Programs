#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Cube {
	vector<char> sides = {};
	bool isAvailable = true;
	bool contains(char target) {
		for (int i = 0; i < sides.size(); i++) {
			if (sides[i] == target) {
				return true;
			}
		}
		return false;
	}
	void print() {
		for (int i = 0; i < sides.size(); i++) {
			cout << sides[i];
		}
	}
};

int howManyWords;
char extraCharacter;
vector<Cube> allCubes;
vector<string> allWords;
vector<char> uniqueLetters;

void resetCubeAvailability(vector<Cube> & cubes) {
	for (int i = 0; i < cubes.size(); i++) {
		cubes[i].isAvailable = true;
	}
}

bool compareCubes(Cube& cubeOne, Cube& cubeTwo) {
	return cubeOne.sides[0] < cubeTwo.sides[0];
}

void collectAllWords() {
	// collect all words and store them in allWords
	for (int i = 0; i < howManyWords; i++) {
		string newWord;
		cin >> newWord;
		for (int c = 0; c < newWord.size(); c++) {
			newWord[c] = toupper(newWord[c]);
		}
		allWords.push_back(newWord);
	}
}

void createCubes() {
	// get how many cubes to make, and create that many empty cubes
	int howManyCubes = allWords[0].size();
	for (int i = 0; i < howManyCubes; i++) {
		Cube newCube;
		allCubes.push_back(newCube);
	}
}

bool isUnique(char target) {
	for (int i = 0; i < uniqueLetters.size(); i++) {
		if (uniqueLetters[i] == target) {
			return false;
		}
	}
	return true;
}

void collectUniqueLetters() {
	for (int w = 0; w < allWords.size(); w++) {
		for (int l = 0; l < allWords[w].size(); l++) {
			char letter = allWords[w][l];
			if (isUnique(letter)) {
				uniqueLetters.push_back(letter);
			}
		}
	}
}

bool noWordsHaveTwoLettersOnSingleCube(vector<Cube> cubes) {


	// for every word
	for (int w = 0; w < allWords.size(); w++) {
		string currentWord = allWords[w];

		// for every cube
		for (int c = 0; c < cubes.size(); c++) {
			

			// for every letter in current word
			for (int l = 0; l < allWords[w].size(); l++) {
				char currentLetter = allWords[w][l];

				// check to see if the cube has the current letter
				if (cubes[c].contains(allWords[w][l])) {

					// if we havent found a letter on this cube yet, mark it unavailable
					if (cubes[c].isAvailable == true) {
						cubes[c].isAvailable = false;
					}

					// if we have found a letter on this cube already, we just found a 2nd
					else if (cubes[c].isAvailable == false) {
						return false;
					}
				}
			}
		}
		resetCubeAvailability(cubes);
	}
	return true;
}

bool solve(vector<Cube> & cubes, vector<char> letters, int pos) {
	if (pos == letters.size()) {
		return true;
	}
	else {
		for (int c = 0; c < cubes.size(); c++) {
			if (cubes[c].sides.size() != 6) {
				cubes[c].sides.push_back(letters[pos]);
				if (noWordsHaveTwoLettersOnSingleCube(cubes)) {
					if (solve(cubes, letters, pos + 1)) {
						return true;
					}
 				}
				cubes[c].sides.pop_back();
			}
		}
	}
	return false;		
}

void insertExtraCharacter() {
	if (extraCharacter != '-') {
		for (int i = 0; i < allCubes.size(); i++) {
			if (allCubes[i].sides.size() == 5) {
				allCubes[i].sides.push_back(extraCharacter);
			}
		}
	}
}

void printSortedCubes() {
	for (int i = 0; i < allCubes.size(); i++) {
		sort(allCubes[i].sides.begin(), allCubes[i].sides.end());
	}
	sort(allCubes.begin(), allCubes.end(), compareCubes);
	for (int i = 0; i < allCubes.size(); i++) {
		allCubes[i].print();
		
		if (i != (allCubes.size() - 1)) {
			cout << " ";
		}
	}
	cout << endl;
}

void resetForNextIteration() {
	int howManyWords = -1;
	char extraCharacter = ' ';
	allCubes.clear();
	allWords.clear();
	uniqueLetters.clear();
}

int main() {
	while (cin >> howManyWords && howManyWords != 0) {
		cin >> extraCharacter;
		collectAllWords();
		createCubes();
		collectUniqueLetters();
		if (solve(allCubes, uniqueLetters, 0)) {
			insertExtraCharacter();
			printSortedCubes();
		}
		resetForNextIteration();
	}
}

// if letter already exists on cube
// skip over blocks that contain a letter used in word

/*

0 1 2 3
-------

C L I P     CLIP
	G O     CLOG
  E N       CONE
H D   S     DISH
A   F Z     FAZE
U     R     FURL
	M       MARE
  K         MOCK
  Q         QUIP
T   W       STEW
  Y         TONY
	  V     VICE
			WARD
-------
5 6 6 6

*/
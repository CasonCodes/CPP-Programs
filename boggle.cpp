/*
--------------------------------
[PROBLEM]: IT BOGGLES THE MIND
[WRITTEN BY]: CASON KIRSCHNER
[COURSE]: APPLIED ALGORITHMS
[DATE]: 10.17.2022
--------------------------------
	[PROGRAM DESCRIPTION]:
--------------------------------
THIS PROGRAM READS IN A GRID
OF VARIABLE "GRIDSIZE" AND A
WORD TO SEARCH FOR.
--------------------------------
	[EXAMPLE INPUT]:
--------------------------------
HDRU
RAIG
RNVN
DIUS
HARDING
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::setw;
using std::left;

enum Direction {
	N, NE, E, SE, S, SW, W, NW
};

struct Square {
	char letter = ' ';
	bool isUsed = false;
};

struct Coordinate {
	int row = 0;
	int col = 0;
};

const int gridSize = 4;
const bool debugMode = false;
const bool stepByStepDebug = false;
const char breadCrumbSymbol = '*';

class Boggle {

private:

	Coordinate look(Direction const& direction, Coordinate const& focus) {
		switch (direction) {
		case N:  return { focus.row - 1, focus.col + 0 };
		case NE: return { focus.row - 1, focus.col + 1 };
		case E:  return { focus.row + 0, focus.col + 1 };
		case SE: return { focus.row + 1, focus.col + 1 };
		case S:  return { focus.row + 1, focus.col + 0 };
		case SW: return { focus.row + 1, focus.col - 1 };
		case W:  return { focus.row + 0, focus.col - 1 };
		case NW: return { focus.row - 1, focus.col - 1 };
		}
	}

	void resetUsedSquares(vector<vector<Square>>& grid) {
		for (int row = 0; row < gridSize; row++) {
			for (int col = 0; col < gridSize; col++) {
				grid[row][col].isUsed = false;
			}
		}
	}

	void capitalizeWord(string& word) {
		for (int i = 0; i < word.size(); i++) {
			word[i] = toupper(word[i]);
		}
	}

	void capitalizeGrid(vector<vector<Square>>& grid) {
		for (int row = 0; row < gridSize; row++) {
			for (int col = 0; col < gridSize; col++) {
				grid[row][col].letter = toupper(grid[row][col].letter);
			}
		}
	}

	bool isOnGrid(Coordinate const& coordinate) {
		return (coordinate.row >= 0 && coordinate.row < 4
			&& coordinate.col >= 0 && coordinate.col < 4);
	}

	void displayGrid(vector<vector<Square>> const& grid) {
		if (debugMode == true) {
			if (stepByStepDebug == true) {
				cout << "--------------------" << endl;
			}
			else {
				system("cls");
			}
		}

		for (int row = 0; row < gridSize; row++) {
			for (int col = 0; col < gridSize; col++) {
				if (grid[row][col].isUsed) {
					cout << breadCrumbSymbol;
				}
				else {
					cout << grid[row][col].letter;
				}
			}
			cout << endl;
		}
		system("pause");
	}

	void getGrid(vector<vector<Square>>& grid) {
		for (int row = 0; row < gridSize; row++) {
			vector<Square> newRow;
			for (int col = 0; col < gridSize; col++) {
				Square newSquare;
				cin >> newSquare.letter;
				newRow.push_back(newSquare);
			}
			grid.push_back(newRow);
		}
		capitalizeGrid(grid);
	}

	bool getWord(string& word) {
		bool keepGoing = true;
		cin >> word;
		capitalizeWord(word);
		if (word == "*") {
			keepGoing = false;
		}
		return keepGoing;
	}

	void displayResult(string const& word, bool const& wordFound) {
		if (wordFound) {
			cout << setw(17) << left << word << "VALID" << endl;
		}
		else {
			cout << setw(17) << left << word << "NOT VALID" << endl;
		}
		if (debugMode == true) {
			system("pause");
		}
	}

	bool allSameLetter(vector<vector<Square>> const& grid) {
		for (int row = 0; row < gridSize; row++) {
			for (int col = 0; col < gridSize; col++) {
				if (grid[row][col].letter != grid[0][0].letter) {
					return false;
				}
			}
		}
		return true;
	}

	bool allSameLetter(string const& word) {
		for (int i = 0; i < word.size(); i++) {
			if (word[i] != word[0]) {
				return false;
			}
		}
		return true;
	}

	bool findWord(string word, Coordinate focus, vector<vector<Square>> grid) {

		// if all letters of word have been found (base case)
		if (word.size() == 0) {
			return true;
		}
		else {

			// for all possible directions 
			// (N, NE, E, SE, S, SW, W, NW)
			for (int i = 0; i < 8; i++) {

				// capture coordinate of square in each direction
				Coordinate lookedAt = look(Direction(i), focus);

				// if coord is on the grid, its letter matches, and has not been used
				if (isOnGrid(lookedAt) == true) {
					if (grid[lookedAt.row][lookedAt.col].letter == word[0]) {
						if (grid[lookedAt.row][lookedAt.col].isUsed == false) {

							// mark square as used
							grid[lookedAt.row][lookedAt.col].isUsed = true;

							if (debugMode == true) {
								displayGrid(grid);
							}

							// continue search, follow path, call function recursively
							bool found = findWord(word.substr(1), lookedAt, grid);

							// only break out of search completely if entire
							// word found, otherwise continue searching.
							if (found == true) {
								return found;
							}
						}
					}
				}
			}
			// found dead end, back track
			return false;
		}
	}

public:

	void startSearch() {
		string word;
		Coordinate focus;
		vector<vector<Square>> grid;

		getGrid(grid);

		// while the word is not "*"
		while (getWord(word)) {

			bool wordFound = false;

			if (word.size() == gridSize * gridSize && allSameLetter(grid) && allSameLetter(word)) {
				wordFound = true;
			}
			else {
				// each possible starting place of the word
				for (focus.row = 0; focus.row < gridSize; focus.row++) {
					for (focus.col = 0; focus.col < gridSize; focus.col++) {

						// if square contains first letter of word
						if (grid[focus.row][focus.col].letter == word[0]) {

							// mark square as used
							grid[focus.row][focus.col].isUsed = true;

							if (debugMode == true) {
								displayGrid(grid);
							}

							// call recursive function, passing the word excluding 
							// the first letter because it was already found
							wordFound = findWord(word.substr(1), focus, grid);
						}
						if (wordFound == true) {
							break;
						}
					}
					if (wordFound == true) {
						break;
					}
				}
			}
			// display whether the word was found or not
			// amd prepare grid for next word to search for
			displayResult(word, wordFound);
			resetUsedSquares(grid);
		}
	}

};

int main() {
	Boggle b;
	b.startSearch();
}
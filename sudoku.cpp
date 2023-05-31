#include <iostream>
#include <string>
using namespace std;

enum class Digit {
	blank = '.',
	one = '1', 
	two = '2', 
	three = '3',
	four = '4', 
	five = '5', 
	six = '6',
	seven = '7', 
	eight = '8', 
	nine = '9'
};

struct Coordinate {
	int row = 0;
	int col = 0;
};

struct Position {
	Coordinate whichSquare;
	Coordinate whichTile;
};

// a Tile holds a digit
struct Tile {
	Position position;
	Digit digit = Digit::blank;
	bool cannotBeChanged = false;

	bool isBlank() { 
		return digit == Digit::blank; 
	}
	void printTile() {
		cout << char(digit);
	}
};

// a square is a 3x3 matrix of Tiles
struct Square {
	Tile tiles[3][3];

	bool squareFilled() {
		bool isFilled = true;
		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 3; col++) {
				if (tiles[row][col].isBlank()) {
					isFilled = false;
				}
			}
		}
		return isFilled;
	}
};

// a Board is a 3x3 matrix of Squares
struct Board {
	Square squares[3][3];
	int testCaseNumber = 0;
	Tile* focusedTile;

	void setFocus(Position newPosition) {
		focusedTile = &squares[newPosition.whichSquare.row][newPosition.whichSquare.col]
			.tiles[newPosition.whichTile.row][newPosition.whichTile.col];
	}
	int howManyDuplicatesFoundOn(string rowOrCol, Digit digitToLookFor, Position position) {
		
		setFocus(position);
		int count = 0;
		
		if (rowOrCol == "row") {
			
			for (int sC = 0; sC < 3; sC++) {
				for (int tC = 0; tC < 3; tC++) {
					if (focusedTile->digit != digitToLookFor) {
						setFocus({ {focusedTile->position.whichSquare.row, sC},
							{focusedTile->position.whichTile.row, tC} });
					}
					else {
						count++;
					}
				}
			}

		}
		else if (rowOrCol == "col") {

			for (int sR = 0; sR < 3; sR++) {
				for (int tR = 0; tR < 3; tR++) {
					if (focusedTile->digit != digitToLookFor) {
						setFocus({ {sR, focusedTile->position.whichSquare.col},
							{tR, focusedTile->position.whichTile.col} });
					}
					else {
						count++;
					}
				}
			}

		}
		return count;
	}
	void printBoard() {
		// traversing through a 3x3 matrix of 3x3 matrices...
		for (int sR = 0; sR < 3; sR++) { // looping through squareRow
			for (int tC = 0; tC < 3; tC++) { // looping through tileRow
				for (int sC = 0; sC < 3; sC++) { // looping through squareCol
					for (int tR = 0; tR < 3; tR++) { // looping through tileRow

						squares[sR][sC].tiles[tR][tC].printTile();
						// protects against leading and trailing spaces
						if (sC != 3 && tC != 3) { 
							cout << " ";
						}	
					}
				}
				cout << endl;
			}
		}
	}
	bool boardFilled() {
		// returns true if no blank tiles are found on board
		bool isFilled = true;
		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 3; col++) {
				if (squares[row][col].squareFilled()) {
					isFilled = false;
				}
			}
		}
		return isFilled;
	}

	bool getTestCaseNumber() {
		cin >> testCaseNumber;
		return testCaseNumber == 0;
	}
	void getBoard() {
		// traversing through a 3x3 matrix of 3x3 matrices...
		for (int sR = 0; sR < 3; sR++) { // looping through squareRow
			for (int tC = 0; tC < 3; tC++) { // looping through tileRow
				for (int sC = 0; sC < 3; sC++) { // looping through squareCol
					for (int tR = 0; tR < 3; tR++) { // looping through tileRow

						char input;
						cin >> input;
						if (input != '0') {
							squares[sR][sC].tiles[tR][tC].cannotBeChanged = true;
						}
						squares[sR][sC].tiles[tR][tC].digit = Digit(input);
						squares[sR][sC].tiles[tR][tC].position = {};
					}
				}
			}
		}
	}
	bool solveBoard() {
		bool canBeSolved = true;



		return canBeSolved;
	}
	void printResult(bool canBeSolved) {
		cout << "Test Case #" << testCaseNumber << ":" << endl;
		if (canBeSolved) {
			printBoard();
		}
		else {
			cout << "No solution";
		}
	}
};

int main() {
	bool readyToQuit = false;
	do {
		Board board;
		readyToQuit = board.getTestCaseNumber();
		if (!readyToQuit) {
			board.getBoard();
			bool canBeSolved = board.solveBoard();
			board.printResult(canBeSolved);
		}
	} while (!readyToQuit);
}
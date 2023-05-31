#include <iostream>	
#include <string>
#include <vector>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

enum Digit {
	empty = '0',
	one = '1',
	two = '2',
	three = '3',
	four = '4',
	five = '5',
	six = '6',
	seven = '7',
	eight = '8',
	nine = '9',
};

enum Box {
	upperLeft, upperMiddle, upperRight,
	middleLeft, middleMiddle, middleRight,
	lowerLeft, lowerMiddle, lowerRight
};

struct Coord {
	int x = 0;
	int y = 0;
};

struct Cell {
	Digit digit = empty;
};

const bool debugMode = false;
const int gridSize = 9;

class Sudoku {

private:

	int testNumber = 0;
	bool solutionFound = false;
	Cell grid[gridSize][gridSize];
	vector<vector<Coord>> boxes = {
		{ {0,0},{0,1},{0,2},
		  {1,0},{1,1},{1,2},
		  {2,0},{2,1},{2,2} }, // UL

		{ {0,3},{0,4},{0,5},
		  {1,3},{1,4},{1,5},
		  {2,3},{2,4},{2,5} }, // UM

		{ {0,6},{0,7},{0,8},
		  {1,6},{1,7},{1,8},
		  {2,6},{2,7},{2,8} }, // UR

		{ {3,0},{3,1},{3,2},
		  {4,0},{4,1},{4,2},
		  {5,0},{5,1},{5,2} }, // ML

		{ {3,3},{3,4},{3,5},
		  {4,3},{4,4},{4,5},
		  {5,3},{5,4},{5,5} }, // MM

		{ {3,6},{3,7},{3,8},
		  {4,6},{4,7},{4,8},
		  {5,6},{5,7},{5,8} }, // MR

		{ {6,0},{6,1},{6,2},
		  {7,0},{7,1},{7,2},
		  {8,0},{8,1},{8,2} }, // BL

		{ {6,3},{6,4},{6,5},
		  {7,3},{7,4},{7,5},
		  {8,3},{8,4},{8,5} }, // BM

		{ {6,6},{6,7},{6,8},
		  {7,6},{7,7},{7,8},
		  {8,6},{8,7},{8,8} }  // BR

	};

	bool boxContains(Digit target, Box box) {
		for (int i = 0; i < gridSize; i++) {
			int b = (int)box;
			int x = boxes[b][i].x;
			int y = boxes[b][i].y;
			if (grid[x][y].digit == target) {
				return true;
			}
		}
		return false;
	}
	void inputGrid() {
		for (int row = 0; row < gridSize; row++) {
			for (int col = 0; col < gridSize; col++) {
				char input = ' ';
				cin >> input;
				grid[row][col].digit = (Digit)input;
			}
		}
	}
	void printGrid() {
		if (debugMode) {
			cout << "    0 1 2   3 4 5   6 7 8" << endl;
			cout << "    ---------------------" << endl;
		}
		for (int row = 0; row < gridSize; row++) {
			if (debugMode) {
				if (row != 3 && row != 6) {
					cout << row << " | ";
				}
				if (row == 3 || row == 6) {
					cout << "    ---------------------" << endl;
					cout << row << " | ";
				}
			}
			for (int col = 0; col < gridSize; col++) {
				if (debugMode) {
					if (col == 3 || col == 6) {
						cout << "| " << (char)grid[row][col].digit;
					}
					else {
						cout << (char)grid[row][col].digit;
					}
				}
				else {
					cout << (char)grid[row][col].digit;
				}
				if (col != gridSize - 1) {
					cout << " ";
				}
			}
			cout << endl;
		}
	}
	void printResult() {
		cout << "Test Case #" << testNumber << ":" << endl;
		if (solutionFound) {
			printGrid();
		}
		else {
			cout << "No solution" << endl;
		}
		cout << endl;
	}
	bool noVerticalDuplicates(Coord position) {
		return false;
	}
	bool noHorizontalDuplicates(Coord position) {
		return false;
	}
	bool noBoxDuplicates(Coord position, Box whichBox) {
		return false;
	}
	bool goodVertical(Coord position) {
		bool allTargets[9] = { false, false, false, false, false, false, false, false, false };
		for (int y = 0; y < 9; y++) {
			if (grid[position.x][y].digit == (Digit)(y + 1)) {
				allTargets[y] = true;
			}
		}
		for (int i = 0; i < 9; i++) {
			if (allTargets[i] == false) {
				return false;
			}
		}
		return true;
	}
	bool goodHorizontal(Coord position) {
		bool allTargets[9] = { false, false, false, false, false, false, false, false, false };
		for (int x = 0; x < 9; x++) {
			if (grid[x][position.y].digit == (Digit)(x + 1)) {
				allTargets[x] = true;
			}
		}
		for (int i = 0; i < 9; i++) {
			if (allTargets[i] == false) {
				return false;
			}
		}
		return true;
	}
	bool completeBox(Box whichBox) {
		for (int target = 1; target <= 9; target++) {
			if (!boxContains((Digit)target, whichBox)) {
				return false;
			}
		}
		return true;
	}

public:

	void setupPuzzle() {
		cin >> testNumber;
		inputGrid();
	}
	void solvePuzzle() {
		while (true) {
			char choice;
			int x, y;
			system("cls");
			printGrid();
			cout << endl << "Place a(n): ";
			cin >> choice;
			cout << "At: ";
			cin >> x >> y;
			grid[x][y].digit = (Digit)choice;
			printGrid();
		}
	}
};

int main() {
	Sudoku s;
	s.setupPuzzle();
	s.solvePuzzle();
}
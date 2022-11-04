#include <iostream>
#include <vector>
using namespace std;

const bool debugMode = false;

struct Coord {
	int x, y;
};

struct Square {
	char symbol = '.';
	bool isFound = false;
};

enum class Direction {
	N, E, S, W, NE, SE, SW, NW
};

struct Object {
	int perimeter = 0;
	vector<Coord> squares;
	void reset() {
		perimeter = 0;
		squares.clear();
	}
};

struct ObjectFinder {

	int gridRows = 0;
	int	gridCols = 0;
	Object object;
	int testCaseCount = 1;
	Coord clickPoint = { 0, 0 };
	vector<vector<Square>> grid;

	void getGridSize() {
		cin >> gridRows >> gridCols;
	}

	void getGrid() {
		for (int r = 0; r < gridRows; r++) {
			vector<Square> newRow;
			for (int c = 0; c < gridCols; c++) {
				Square newSquare;
				cin >> newSquare.symbol;
				newSquare.isFound = false;
				newRow.push_back(newSquare);
			}
			grid.push_back(newRow);
		}
	}

	void displayGrid() {
		for (int r = 0; r < gridRows; r++) {
			for (int c = 0; c < gridCols; c++) {
				cout << grid[r][c].symbol;
			}
			cout << endl;
		}
	}

	bool isValidInput() {
		return gridRows != 0 && gridCols != 0 &&
			clickPoint.x != 0 && clickPoint.y != 0;
	}

	void getClickPoint() {
		cin >> clickPoint.x >> clickPoint.y;
	}

	Coord look(Direction direction, Coord current) {
		switch (direction) {
		case Direction::N:  return { current.x - 1, current.y + 0 };
		case Direction::E:  return { current.x + 0, current.y + 1 };
		case Direction::S:  return { current.x + 1, current.y + 0 };
		case Direction::W:  return { current.x + 0, current.y - 1 };
		case Direction::NE: return { current.x - 1, current.y + 1 };
		case Direction::SE: return { current.x + 1, current.y + 1 };
		case Direction::SW: return { current.x + 1, current.y - 1 };
		case Direction::NW: return { current.x - 1, current.y - 1 };
		default: cout << "Something went wrong in look();" << endl;
		}
	}

	bool isOnGrid(Coord coord) {
		return coord.x < gridRows && coord.x >= 0
			&& coord.y < gridCols && coord.y >= 0;
	}

	void findObject(Coord current) {

		// for all directions
		for (int i = 0; i < 8; i++) {

			// shortens loop time
			if (object.squares.size() == gridRows * gridCols) {
				return;
			}

			// capture coord in that direction
			Coord lookedAt = look(Direction(i), current);

			// if square looked at is on grid, an X, & hasnt been found yet
			if (isOnGrid(lookedAt) 
				&& grid[lookedAt.x][lookedAt.y].symbol == 'X' 
				&& grid[lookedAt.x][lookedAt.y].isFound == false) {

				// mark as found, store coordinate, and continue search
				grid[lookedAt.x][lookedAt.y].isFound = true;

				if (debugMode) {
					grid[lookedAt.x][lookedAt.y].symbol = 'x';
					system("cls");
					displayGrid();
					cout << endl;
					system("pause");
				}				

				object.squares.push_back(lookedAt);
				findObject(lookedAt);
			}
		}
	}

	void calculatePerimeter() {

		// for each square that is part of the object
		for (int i = 0; i < object.squares.size(); i++) {

			// for N, E, S, W
			for (int d = 0; d < 4; d++) {

				// if square is an edge piece of the object
				Coord lookedAt = look(Direction(d), object.squares[i]);
				if (!isOnGrid(lookedAt) || grid[lookedAt.x][lookedAt.y].symbol == '.') {
					object.perimeter++;
				}

			}
		}
	}

	void displayResult() {
		cout << "Perimeter of object " << testCaseCount 
			<< " at (" << clickPoint.x << "," << clickPoint.y << ") = " 
			<< object.perimeter << endl;
	}

	void resetForNextTestCase() {
		gridRows = 0;
		gridCols = 0;
		object.reset();
		clickPoint = { 0, 0 };
		grid.clear();
		testCaseCount++;
	}
};

int main() {
	ObjectFinder of;
	of.getGridSize();
	of.getClickPoint();
	while (of.isValidInput()) {
		of.getGrid();
		of.findObject(of.clickPoint);
		of.calculatePerimeter();
		of.displayResult();
		of.resetForNextTestCase();
		of.getGridSize();
		of.getClickPoint();
	} 
}

/*







Example input
-----------------
6 4 2 3
.XXX
.XXX
.XXX
...X
..X.
X...
6 4 6 1
.XXX
.XXX
.XXX
...X
..X.
X...
6 4 5 3
.XXX
.XXX
.XXX
...X
..X.
X...
5 6 3 3
.XXXX.
X....X
..XX.X
.X...X
..XXX.
6 4 2 3
XXXX
XXXX
XXXX
XXXX
XXXX
XXXX
5 5 1 2
.....
..X..
.....
..X..
.....
0 0 0 0

Example output
-------------------
Perimeter of object 1 at (2,3) = 18
Perimeter of object 2 at (6,1) = 4
Perimeter of object 3 at (5,3) = 18
Perimeter of object 4 at (3,3) = 40
Perimeter of object 1 at (2,3) = 20



*/
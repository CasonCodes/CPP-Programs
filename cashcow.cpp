#include <iostream>
#include <vector>
#include <queue>
using namespace std;

enum class Color {
	red = 'R',
	blue = 'B',
	yellow = 'Y',

	none = ' ',
	selected = '.'
};

struct Coordinate {
	int row = 0;
	int column = 0;
	Coordinate(int r, int c) {
		row = r;
		column = c;
	}
};

struct Cluster {
	Color color = Color::none;
	queue<Coordinate> coordinates;
};

class CashCow {

	queue<Coordinate> moves;
	int howManyMovesToExpect;
	vector<vector<Color>> board;

public:

	// COMPLETE 
	bool outOfBounds(Coordinate coordinate) {
		return coordinate.row < 0
			|| coordinate.row > 9
			|| coordinate.column < 0
			|| coordinate.column > 11;
	}

	// COMPLETE 
	bool getHowManyMoves() {
		cin >> howManyMovesToExpect;
		return howManyMovesToExpect != 0;
	}

	// COMPLETE
	void initializeBoard() {
		for (int row = 0; row < 10; row++) {
			vector<Color> newRow;
			for (int col = 0; col < 12; col++) {
				Color newColor = Color::none;
				newRow.push_back(newColor);
			}
			board.push_back(newRow);
		}
	}

	// COMPLETE
	void readBoardSetUp() {
		for (int col = 11; col >= 0; col--) {
			for (int row = 0; row < 10; row++) {
				char circleColor;
				cin >> circleColor;
				switch (circleColor) {
				case 'Y': board[row][col] = Color::yellow; break;
				case 'B': board[row][col] = Color::blue; break;
				case 'R': board[row][col] = Color::red; break;
				}
			}
		}
	}

	// COMPLETE
	void collectMoves() {
		for (int i = 0; i < howManyMovesToExpect; i++) {
			char rowCharacter; int columnNumber;
			cin >> rowCharacter >> columnNumber;
			Coordinate newMove((int)(rowCharacter - 'a'), columnNumber - 1);
			moves.push(newMove);
		}
	}

	// COMPLETE
	Color at(Coordinate coordinate) {
		if (!outOfBounds(coordinate)) {
			return board[coordinate.row][coordinate.column];
		}
		else {
			return Color::none;
		}
	}

	// COMPLETE
	void findCluster(Coordinate move, Cluster& newCluster) {

		board[move.row][move.column] = Color::selected;
		newCluster.coordinates.push(move);

		

		Coordinate north(move.row, move.column + 1);
		Coordinate east(move.row + 1, move.column);
		Coordinate south(move.row - 1, move.column);
		Coordinate west(move.row, move.column - 1);

		if (at(north) == newCluster.color) { // N
			findCluster(north, newCluster);
		}
		if (at(east) == newCluster.color) { // E
			findCluster(east, newCluster);
		}
		if (at(south) == newCluster.color) { // S
			findCluster(south, newCluster);
		}
		if (at(west) == newCluster.color) { // W
			findCluster(west, newCluster);
		}
	}

	// COMPLETE
	void removeCluster(Cluster& cluster) {
		if (cluster.coordinates.size() > 2) {
			while (!cluster.coordinates.empty()) {
				board[cluster.coordinates.front().row][cluster.coordinates.front().column] = Color::none;

				cluster.coordinates.pop();
			}
		}
	}

	// COMPLETE
	bool isEmptyRow(int row) {
		for (int col = 0; col < 12; col++) {
			if (board[row][col] != Color::none) {
				return false;
			}
		}
		return true;
	}

	// INCOMPLETE
	void condenseBoard() {
		for (int count = 0; count < 5; count++) {
			for (int row = 0; row < 10; row++) {
				for (int col = 0; col < 12; col++) {
					if (at({ row, col }) == Color::none) {
						board[row].push_back(board[row][col]);
						board[row].erase(board[row].begin() + col);
						
					}
				}
			}
		}
		// traverse through rows of board, if empty vector is found, throw to end of columns
		for (int count = 0; count < 5; count++) {
			for (int row = 0; row < 10; row++) {
				if (isEmptyRow(row)) {
					board.push_back(board[row]);
					board.erase(board.begin() + row);
					
				}
			}
		}
	}

	// COMPLETE
	void executeMoves() {
		while (!moves.empty()) {
			Cluster newCluster;
			if (at(moves.front()) != Color::none) {
				newCluster.color = at(moves.front());
				findCluster(moves.front(), newCluster);
			}
			moves.pop();
			removeCluster(newCluster);
			condenseBoard();
			
		}
	}

	// COMPLETE
	int countHowManyCircles() {
		int howManyCircles = 0;
		for (int row = 0; row < 10; row++) {
			for (int col = 0; col < 12; col++) {
				if (board[row][col] != Color::none) {
					howManyCircles++;
				}
			}
		}
		return howManyCircles;
	}

	// COMPLETE
	void printBoard() {
		system("cls");
		for (int col = 11; col >= 0; col--) {
			for (int row = 0; row < 10; row++) {
				cout << (char)board[row][col];
			}
			cout << endl;
		}
	}

};

int main() {
	bool keepGoing = true;
	while (keepGoing) {
		CashCow myGame;
		keepGoing = myGame.getHowManyMoves();
		if (keepGoing) {
			myGame.initializeBoard();
			myGame.readBoardSetUp();
			myGame.collectMoves();
			myGame.executeMoves();
			cout << myGame.countHowManyCircles() << endl;
		}
	}
}

/*
 
	   12 Columns [2nd #]
	11 | * * * * * * * * * *
	10 | * * * * * * * * * *
	9  | * * * * * * * * * *
	8  | * * * * * * * * * *
	7  | * * * * * * * * * *
	6  | * * * * * * * * * *
	5  | * * * * * * * * * *
	4  | * * * * * * * * * *
	3  | * * * * * * * * * *
	2  | * * * * * * * * * *
	1  | * * * * * * * * * *
	0  | * * * * * * * * * *
		 ------------------- 10 Rows [1st #]
		 0 1 2 3 4 5 6 7 8 9
		 a b c d e f g h i j 

*/
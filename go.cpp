#include <iostream>
#include <vector>
using namespace std;

const bool debugMode = false;

enum LatticePointStatus {
	whiteStone,
	blackStone,
	unclaimed,

	pending,

	whitePoint,
	blackPoint,
	contested,
};

enum GameStatus {
	draw,
	white,
	black,
	undecided
};

struct Coordinate {
	int row = 0;
	int col = 0;
};

enum class Direction {
	up, down, left, right
};

class Go {
	int boardSize = 0;
	int whiteScore = 0;
	int blackScore = 0;
	bool timeToQuit = false;
	int howManyBlackStones = 0;
	int howManyWhiteStones = 0;
	vector<vector<LatticePointStatus>> board;

	void printBoard() {
		system("cls");
		for (int i = 0; i < boardSize; i++) {
			for (int x = 0; x < boardSize; x++) {
				switch (board[i][x]) {
				case unclaimed: cout << "."; break;
				case blackStone: cout << "B"; break;
				case whiteStone: cout << "W"; break;
				case blackPoint: cout << "b"; break;
				case whitePoint: cout << "w"; break;
				case contested: cout << "x"; break;
				case pending: cout << "p"; break;
				}
				cout << " ";
			}
			cout << endl;
		}
	}
	void inputGameDetails() {
		cin >> howManyBlackStones >> howManyWhiteStones;
	}
	void initializeBoard() {
		for (int i = 0; i < boardSize; i++) {
			vector<LatticePointStatus> newRow;
			for (int x = 0; x < boardSize; x++) {
				newRow.push_back(unclaimed);
			}
			board.push_back(newRow);
		}
	}
	void setWhiteStones() {
		for (int i = 0; i < howManyWhiteStones; i++) {
			int row, col;
			cin >> row >> col;
			board[row - 1][col - 1] = whiteStone;
		}
	}
	void setBlackStones() {
		for (int i = 0; i < howManyBlackStones; i++) {
			int row, col;
			cin >> row >> col;
			board[row - 1][col - 1] = blackStone;
		}
	}
	bool onBoard(Coordinate coord) {
		return coord.row >= 0 && coord.row < boardSize
			&& coord.col >= 0 && coord.col < boardSize;
	}
	LatticePointStatus getStatus(Coordinate coordinate) {
		return board[coordinate.row][coordinate.col];
	}
	Coordinate look(Direction direction, Coordinate current) {
		switch (direction) {
		case Direction::up:		return { current.row - 1, current.col + 0 };
		case Direction::right:	return { current.row + 0, current.col + 1 };
		case Direction::down:	return { current.row + 1, current.col + 0 };
		case Direction::left:	return { current.row + 0, current.col - 1 };
		}
	}
	void captureCluster(Coordinate current, vector<Coordinate> & clusterCoords) {
		// for each direction
		for (int i = 0; i < 4; i++) {

			// look in each direction
			Coordinate lookedAt = look(Direction(i), current);

			// if looked at coordinate is in bounds
			if (onBoard(lookedAt)) {

				// if unclaimed, add to cluster coord list
				if (getStatus(lookedAt) == unclaimed) {
					clusterCoords.push_back(lookedAt);
					board[lookedAt.row][lookedAt.col] = pending;
					if (debugMode) {
						printBoard();
					}
					captureCluster(lookedAt, clusterCoords);
				}				
			}
		}
	}
	void determineClusterOwner(vector<Coordinate> & clusterCoords) {

		LatticePointStatus firstBorderColorFound = unclaimed;
		LatticePointStatus clusterStatus = unclaimed;

		// for every lattice point in cluster
		for (int d = 0; d < clusterCoords.size(); d++) {
			Coordinate current = { clusterCoords[d].row, clusterCoords[d].col };

			// for every direction
			for (int i = 0; i < 4; i++) {

				// look in direction
				Coordinate lookedAt = look(Direction(i), current);

				// if looked at coordinate is in bounds
				if (onBoard(lookedAt)) {

					// if black border found
					if (board[lookedAt.row][lookedAt.col] == blackStone) {

						// if this is the first color weve seen
						if (firstBorderColorFound == unclaimed) {
							firstBorderColorFound = blackStone;
							clusterStatus = blackStone;
						}

						// if we found a black border, but the first we found is white
						else if (firstBorderColorFound == whiteStone) {

							// set cluster as contested
							clusterStatus = contested;
						}
					}

					// if white border found
					else if (board[lookedAt.row][lookedAt.col] == whiteStone) {

						// if this is the first color weve seen
						if (firstBorderColorFound == unclaimed) {
							firstBorderColorFound = whiteStone;
							clusterStatus = whiteStone;
						}

						// if we found a white border, but the first we found is black
						else if (firstBorderColorFound == blackStone) {

							// set cluster as contested
							clusterStatus = contested;
						}
					}
				}
			}
		}		

		for (int i = 0; i < clusterCoords.size(); i++) {
			if (clusterStatus == contested) {
				board[clusterCoords[i].row][clusterCoords[i].col] = contested;
			}
			else if (clusterStatus == blackStone) {
				board[clusterCoords[i].row][clusterCoords[i].col] = blackPoint;
			}
			else if (clusterStatus == whiteStone) {
				board[clusterCoords[i].row][clusterCoords[i].col] = whitePoint;
			}
			if (debugMode) {
				printBoard();
			}
		}
	}
	void disputeTerritory() {

		// loop through entire board
		for (int r = 0; r < boardSize; r++) {
			for (int c = 0; c < boardSize; c++) {
				Coordinate current = { r, c };

				// if unclaimed territory found
				if (getStatus(current) == unclaimed) {

					// add current coord to cluster coords
					vector<Coordinate> clusterCoords;
					clusterCoords.push_back(current);
					board[current.row][current.col] = pending;
					if (debugMode) {
						printBoard();
					}

					// start search from current coord
					captureCluster(current, clusterCoords);

					// once entire cluster captured, mark cluster by owner
					determineClusterOwner(clusterCoords);
				}
			}
		}
	}
	void countWhitePoints() {
		for (int i = 0; i < boardSize; i++) {
			for (int x = 0; x < boardSize; x++) {
				if (board[i][x] == whitePoint) {
					whiteScore++;
				}
			}
		}
	}
	void countBlackPoints() {
		for (int i = 0; i < boardSize; i++) {
			for (int x = 0; x < boardSize; x++) {
				if (board[i][x] == blackPoint) {
					blackScore++;
				}
			}
		}
	}
	void outputGameResults() {
		if (blackScore > whiteScore) {
			cout << "black wins by " << blackScore - whiteScore << endl;
		}
		else if (whiteScore > blackScore) {
			cout << "white wins by " << whiteScore - blackScore << endl;
		}
		else if (blackScore == whiteScore) {
			cout << "draw" << endl;
		}
	}
public:
	void play(int size) {
		boardSize = size;
		inputGameDetails();
		initializeBoard();
		setBlackStones();
		setWhiteStones();
		disputeTerritory();
		countWhitePoints();
		countBlackPoints();
		outputGameResults();
	}
};

int main() {
	int boardSize;
	while (cin >> boardSize && boardSize != 0) {
		Go myGame;
		myGame.play(boardSize);
	}
}


/*


9 25 26
1 5 1 6 2 5 2 7 3 2 3 6 3 7 4 2 4 3 4 4 4 5 4 8 4 9 5 1 5 2 5 3 5 6 5 7 5 8 6 1 6 3 6 4 6 6 7 4 7 5
1 3 1 4 1 8 2 1 2 2 2 4 2 9 3 1 3 3 3 4 3 5 4 1 5 4 5 9 6 2 6 7 6 8 6 9 7 1 7 2 7 3 7 6 7 7 8 4 8 5 8 6
1 1 0
1 1


*/
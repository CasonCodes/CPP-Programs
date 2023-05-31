#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Coordinate {
	int row = 0;
	int col = 0;
};

enum Direction {
	north,
	west,
	northWest,
	nowhere
};

struct Cell {
	Direction pointingTo = nowhere;
	unsigned int count = 0;
};

struct DNA {
	string strandOne = "";
	string strandTwo = "";
	vector<vector<Cell>> cellGrid;
	string longestCommonSequence = "";

	bool isTimeToQuit() {
		return (strandOne == "*" || strandOne == "*");
	}
	bool onGrid(Coordinate coordinate) {
		return coordinate.row < 0
			|| coordinate.row >= strandOne.size()
			|| coordinate.col < 0
			|| coordinate.col >= strandTwo.size();
	}
	void getStrand(int strandNumber) {
		if (strandNumber == 1) {
			cin >> strandOne;
		}
		else if (strandNumber == 2) {
			cin >> strandTwo;
		}
	}
	void buildCellGrid() {
		// fill entire Grid with 0's
		for (int row = 0; row <= strandOne.size(); row++) {
			vector<Cell> newRow;
			for (int x = 0; x <= strandTwo.size(); x++) {
				Cell newCell;
				newRow.push_back(newCell);
			}
			cellGrid.push_back(newRow);
		}

		// starting at cellGrid[1][1]...
		for (int row = 1; row <= strandOne.size(); row++) {
			for (int col = 1; col <= strandTwo.size(); col++) {
				if (strandOne[row - 1] == strandTwo[col - 1]) {
					// if characters match, grab NW count and increment, then point to NW cell.
					cellGrid[row][col].count = cellGrid[row - 1][col - 1].count + 1;
					cellGrid[row][col].pointingTo = northWest;
				}
				else {
					// if they don't match, copy largest value from N or W and point to it.
					if (cellGrid[row - 1][col].count > cellGrid[row][col - 1].count) {
						cellGrid[row][col].count = cellGrid[row - 1][col].count;
						cellGrid[row][col].pointingTo = north;
					}
					else {
						cellGrid[row][col].count = cellGrid[row][col - 1].count;
						cellGrid[row][col].pointingTo = west;
					}
				}
			}
		}
	}
	void calculateLCS() {
		Coordinate currentCell;

		// set currentCell's location to bottom right 
		currentCell.row = strandOne.size();
		currentCell.col = strandTwo.size();

		while (cellGrid[currentCell.row][currentCell.col].count != 0) {

			// add corresponding character to LCS
			if (cellGrid[currentCell.row][currentCell.col].pointingTo == northWest)
				longestCommonSequence = strandOne[currentCell.row - 1] + longestCommonSequence;

			// move to where current cell is pointing to
			switch (cellGrid[currentCell.row][currentCell.col].pointingTo) {
			case north: currentCell.row--;  break;
			case west: currentCell.col--; break;
			case northWest: currentCell.row--; currentCell.col--; break;
			}

		}
	}
	void outputLCS() {
		cout << longestCommonSequence << ":" << longestCommonSequence.size() << endl;
	}
};

int main() {
	bool readyToQuit = false;
	while (!readyToQuit) {
		DNA dna;
		dna.getStrand(1);
		dna.getStrand(2);
		readyToQuit = dna.isTimeToQuit();
		if (!readyToQuit) {
			dna.buildCellGrid();
			dna.calculateLCS();
			dna.outputLCS();
		}
	}
}
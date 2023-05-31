#include <iostream>
#include <vector>
using namespace std;

enum class MazeBlock {
	path = '.',
	rock = '#',
	box = 'B',
	person = 'P',
	target = 'T',
	start = 'S'
};

enum class Dir {
	N,
	E,
	S,
	W
};

struct Coord {
	int x, y;
};

struct BoxPusher {

private: /////////////////////////////////////////////////////////////////

	Coord box;
	Coord target;
	Coord person;
	int maxRows, maxCols;
	vector<char> pathTaken;
	vector<vector<MazeBlock>> maze;

	// [X]
	MazeBlock look(Dir d, Coord c) {
		switch (d) {
		case Dir::N: return maze[c.x - 1][c.y]; break;
		case Dir::E: return maze[c.x][c.y + 1]; break;
		case Dir::S: return maze[c.x + 1][c.y]; break;
		case Dir::W: return maze[c.x][c.y - 1]; break;
		}
	}
	// [X]
	bool boxCanBePushed() {
		for (int i = 0; i < 4; i++) {
			MazeBlock lookedAt = look(Dir(i), box);
			if (lookedAt == MazeBlock::person) {
				return true;
			}
		}
		return false;
	}
	// [X]
	void printMaze() {
		for (int r = 0; r < maxRows; r++) {
			for (int c = 0; c < maxCols; c++) {
				cout << char(maze[r][c]);
			}
			cout << endl;
		}
	}

public: /////////////////////////////////////////////////////////////////

	int mazeCount = 1;

	// [X]
	bool getMaze() {
		cin >> maxRows >> maxCols;
		if (maxRows == 0 && maxCols == 0) {
			return false;
		}
		else {
			for (int r = 0; r < maxRows; r++) {
				vector<MazeBlock> newRow;
				for (int c = 0; c < maxCols; c++) {
					char input;
					cin >> input;
					MazeBlock newMB;
					switch (input) {
					case '.': newMB = MazeBlock(input); break;
					case '#': newMB = MazeBlock(input); break;
					case 'B': newMB = MazeBlock(input); box = {r, c}; break;
					case 'T': newMB = MazeBlock(input); target = { r,c }; break;
					case 'S': newMB = MazeBlock::person; person = {r,c}; break;
					}
					newRow.push_back(newMB);
				}
				maze.push_back(newRow);
			}
			return true;
		}
	}
	// []
	bool canBeSolved() {
		return false;
	}
	// [X]
	void printPathTaken() {
		for (int i = 0; i < pathTaken.size(); i++) {
			cout << char(pathTaken[i]);
		}
		cout << endl;
	}

};

/*


            -------> [] -----> T



BOX finds shortest path to TARGET
determine direction BOX needs to be pushed in
PERSON must go to side of box that is opposite of the direction it must be pushed in

*/

int main() {
	BoxPusher bp;
	while (bp.getMaze()) {
		if (bp.mazeCount > 1) {
			cout << endl;
		}
		if (bp.canBeSolved()) {
			cout << "Maze #" << bp.mazeCount << endl;
			bp.printPathTaken();
		}
		else {
			cout << "Maze #" << bp.mazeCount << endl;
			cout << "Impossible." << endl;
		}		
	}	
}
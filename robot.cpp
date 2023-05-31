#include <iostream>
#include <vector>
using namespace std;




struct Location {
	int row = 0;
	int col = 0;
};




struct Tile {
	int timesVisited = 0;
	char instruction = ' ';
};




struct Robot {
	Location currentTile;
	Location startOfLoop;
	bool stuckInLoop = false;
	int loopInstructions = 0;
	int instructionsFollowed = 0;
};




struct Maze {
	int howManyRows = 0;
	int howManyColumns = 0;
	vector<vector<Tile>> tileGrid;
};




// COMPLETE
void getMazeDetails(Maze& maze, Robot& robot) {
	cin >> maze.howManyRows >> maze.howManyColumns >> robot.currentTile.row >> robot.currentTile.col;
	robot.currentTile.row--;
	robot.currentTile.col--;
}




// COMPLETE
bool quitSignalFound(Maze& maze, Robot& robot) {
	return maze.howManyRows == 0
		|| maze.howManyColumns == 0
		|| robot.currentTile.row == -1
		|| robot.currentTile.col == -1;
}




// COMPLETE
void getMazeGrid(Maze& maze) {
	for (int i = 0; i < maze.howManyRows; i++) {
		vector<Tile> newRow;
		for (int x = 0; x < maze.howManyColumns; x++) {
			Tile newTile;
			cin >> newTile.instruction;
			newRow.push_back(newTile);
		}
		maze.tileGrid.push_back(newRow);
	}
}




// COMPLETE
bool robotOutOfBounds(Maze& maze, Robot& robot) {
	return robot.currentTile.row == -1
		|| robot.currentTile.row == maze.howManyRows
		|| robot.currentTile.col == -1
		|| robot.currentTile.col == maze.howManyColumns;
}




// COMPLETE
void handleLoop(Maze& maze, Robot& robot) {
	robot.startOfLoop.row = robot.currentTile.row;
	robot.startOfLoop.col = robot.currentTile.col;
	do {
		switch (maze.tileGrid[robot.currentTile.row][robot.currentTile.col].instruction) {
		case 'N': robot.currentTile.row--; break;
		case 'S': robot.currentTile.row++; break;
		case 'E': robot.currentTile.col++; break;
		case 'W': robot.currentTile.col--; break;
		}
		robot.loopInstructions++;
	} while (robot.currentTile.row != robot.startOfLoop.row || robot.currentTile.col != robot.startOfLoop.col);
	robot.instructionsFollowed -= robot.loopInstructions;
}




// COMPLETE
void makeRobotMove(Maze& maze, Robot& robot) {
	switch (maze.tileGrid[robot.currentTile.row][robot.currentTile.col].instruction) {
	case 'N': robot.currentTile.row--; break;
	case 'S': robot.currentTile.row++; break;
	case 'E': robot.currentTile.col++; break;
	case 'W': robot.currentTile.col--; break;
	}
	robot.instructionsFollowed++;
	if (!robotOutOfBounds(maze, robot)) {
		maze.tileGrid[robot.currentTile.row][robot.currentTile.col].timesVisited++;
		if (maze.tileGrid[robot.currentTile.row][robot.currentTile.col].timesVisited == 2) {
			robot.stuckInLoop = true;
			handleLoop(maze, robot);
		}
	}
}




// COMPLETE
void printResults(Robot& robot) {
	cout << robot.instructionsFollowed << " instruction";
	if (robot.instructionsFollowed != 1) {
		cout << "s";
	}
	cout << " before ";
	if (robot.loopInstructions > 0) {
		cout << "a loop of " << robot.loopInstructions << " instructions";
	}
	else {
		cout << "exit";
	}
	cout << endl;
 }




// COMPLETE
int main() {
	bool timeToQuit = false;
	do {
		Maze maze;
		Robot robot;
		bool robotFoundExit = false;
		getMazeDetails(maze, robot);
		if (!quitSignalFound(maze, robot)) {
			getMazeGrid(maze);
			do {
				makeRobotMove(maze, robot);
				robotFoundExit = robotOutOfBounds(maze, robot);
			} while (!robotFoundExit && !robot.stuckInLoop);
			printResults(robot);
		}
		else {
			timeToQuit = true;
		}
	} while (!timeToQuit);
}
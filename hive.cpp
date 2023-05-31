#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int howManyDirections = 6;

enum Insect {
	Bee = 'Q', 
	Ant = 'A',
	Spider = 'S',
	Beetle = 'B', 
	Grasshopper = 'G'
};

enum Color {
	White = 'W',
	Black = 'B'
};

enum Direction {
	N, NE, SE, S, SW, NW, U, D
};

struct Position {
	int r = 0;
	int c = 0;
	int h = 0;
	bool isEqualTo(Position p) {
		return r == p.r
			&& c == p.c
			&& h == p.h;
	}
};

Position Look(Direction d, Position p) {
	switch (d) {
	case NW: return { p.r + 1, p.c - 1, p.h };
	case N:  return { p.r + 1, p.c    , p.h };
	case NE: return { p.r + 1, p.c + 1, p.h };
	case SE: return { p.r - 1, p.c + 1, p.h };
	case S:  return { p.r - 1, p.c,     p.h };
	case SW: return { p.r - 1, p.c - 1, p.h };
	case U: return  { p.r,     p.c,     p.h + 1 };
	case D: return  { p.r,     p.c,     p.h - 1 };
	default: cout << "Error in Look()" << endl; return p;
	}
}

struct GameBoard {
	struct Piece {
		Insect insect;
		Position position;
		Color color;
		bool isPinned(GameBoard& gameBoard) {
			Position p = Look(U, position);
			return gameBoard.isOccupied(p);
		}
		bool isSurrounded(GameBoard& gameBoard) {
			for (int i = 0; i < howManyDirections; i++) {
				Position p = Look((Direction)i, position);
				if (!gameBoard.isOccupied(p)) {
					return false;
				}
			}
			return true;
		}
		bool isBlocked(Direction d, GameBoard& gameBoard) {

			bool isBlocked = false;
			Position nw = Look(NW, position);
			Position ne = Look(NE, position);
			Position n = Look(N, position);
			Position s = Look(S, position);
			Position se = Look(SE, position);
			Position sw = Look(SW, position);

			switch (d) {
			case NW: isBlocked = gameBoard.isOccupied(n) && gameBoard.isOccupied(sw);
			case N:  isBlocked = gameBoard.isOccupied(ne) && gameBoard.isOccupied(nw);
			case NE: isBlocked = gameBoard.isOccupied(n) && gameBoard.isOccupied(se);
			case SE: isBlocked = gameBoard.isOccupied(ne) && gameBoard.isOccupied(s);
			case S:  isBlocked = gameBoard.isOccupied(se) && gameBoard.isOccupied(sw);
			case SW: isBlocked = gameBoard.isOccupied(nw) && gameBoard.isOccupied(s);
			}
		}
	};
	vector<Piece> pieces;
	bool isOccupied(Position p) {
		for (int i = 0; i < pieces.size(); i++) {
			if (pieces[i].position.isEqualTo(p)) {
				return true;
			}
		}
		return false;
	}
	bool hiveBroken() {
		return false;
	}
	void print() {
		// TO DO
		cout << "/````\\" << "\\,,,,/" << endl;
		cout << "* WB *" << endl;
		cout << "\\,,,,/" << "/````\\" << endl;
		cout << "      * WB *" << endl;
	}
};

struct Piece {
	Insect insect;
	Position position;
	Color color;
	bool isPinned(GameBoard& gameBoard) {
		Position p = Look(U, position);
		return gameBoard.isOccupied(p);
	}
	bool isSurrounded(GameBoard& gameBoard) {
		for (int i = 0; i < howManyDirections; i++) {
			Position p = Look((Direction)i, position);
			if (!gameBoard.isOccupied(p)) {
				return false;
			}
		}
		return true;
	}
	bool isBlocked(Direction d, GameBoard& gameBoard) {

		bool isBlocked = false;
		Position nw = Look(NW, position);
		Position ne = Look(NE, position);
		Position n = Look(N, position);
		Position s = Look(S, position);
		Position se = Look(SE, position);
		Position sw = Look(SW, position);

		switch (d) {
		case NW: isBlocked = gameBoard.isOccupied(n) && gameBoard.isOccupied(sw);
		case N:  isBlocked = gameBoard.isOccupied(ne) && gameBoard.isOccupied(nw);
		case NE: isBlocked = gameBoard.isOccupied(n) && gameBoard.isOccupied(se);
		case SE: isBlocked = gameBoard.isOccupied(ne) && gameBoard.isOccupied(s);
		case S:  isBlocked = gameBoard.isOccupied(se) && gameBoard.isOccupied(sw);
		case SW: isBlocked = gameBoard.isOccupied(nw) && gameBoard.isOccupied(s);
		}
	}
	void print() {
		// TO DO
		cout << "/````\\" << endl;
		cout << "* " << (char)color << (char)insect << " *" << endl;
		cout << "\\,,,,/" << endl;
	}
};

struct Player {
	Color color;
	string name = "";
	vector<Piece> hand = {
		{Bee},
		{Ant},{Ant},{Ant},
		{Spider},{Spider},
		{Beetle},{Beetle},
		{Grasshopper},{Grasshopper},{Grasshopper}
	};
	void print() {
		// TO DO
		for (int i = 0; i < hand.size(); i++) {
			hand[i].print();
		}
		cout << endl;
	}
};

struct Hive {
	int turnCount = 1;
	GameBoard gameBoard;
	Player playerOne = {White, "Cason"};
	Player playerTwo = {Black, "AI"};

	string whoseTurn() {
		switch (turnCount % 2) {
		case 0: return "Black";
		default: return "White";
		}
	}
	void initializeGame() {
		for (int i = 0; i < playerOne.hand.size(); i++) {
			playerOne.hand[i].color = playerOne.color;
		}
		for (int i = 0; i < playerTwo.hand.size(); i++) {
			playerTwo.hand[i].color = playerTwo.color;
		}
		gameBoard.pieces.reserve(22);
	}
	
public:	
	void playGame() {
		initializeGame();
		playerOne.print();
		playerTwo.print();

		// TO DO
		


	}
};

int main() {
	Hive hive;
	hive.playGame();
}
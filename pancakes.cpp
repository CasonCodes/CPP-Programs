#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const bool debugMode = false;

enum Size {
	A = 'A',
	B = 'B',
	C = 'C',
	D = 'D',
	E = 'E',
	F = 'F',

	a = 'a',
	b = 'b',
	c = 'c',
	d = 'd',
	e = 'e',
	f = 'f'
};

struct Pancake {
	Size size;
	char toChar() {
		return (char)size;
	}
	bool burntSideUp() {
		return (this->toChar() == tolower(this->toChar()));
	}
	void flip() {
		if (this->toChar() == toupper(this->toChar())) {
			size = (Size)tolower(this->toChar());
		}
		else {
			size = (Size)toupper(this->toChar());
		}
	}
};

struct Stack {
	vector<Pancake> pancakes;
	void initialize(string input) {
		for (int i = 0; i < input.size(); i++) {
			Pancake newPancake;
			newPancake.size = (Size)input[i];
			pancakes.push_back(newPancake);
		}
	}
	void print() {
		for (int i = 0; i < pancakes.size(); i++) {
			cout << pancakes[i].toChar();
		}
		cout << endl;
	}
	int height() {
		return pancakes.size();
	}
	void flipFrom(int level) {
		for (int l = level; l < height(); l++) {
			pancakes[l].flip();
		}
		reverse(pancakes.begin() + level, pancakes.end());
	}
};

struct PancakeFlipper {
	Stack stack;
	int minimumFlips = 0;
	vector<Stack> statesVisited;
	bool inValidOrder(Stack state) {
		for (int i = 0; i < state.height(); i++) {
			for (int x = i; x < state.height(); x++) {
				if (state.pancakes[i].size > state.pancakes[x].size) {
					return false;
				}
			}
		}
		return true;
	}
	bool isGoalState(Stack state) {
		for (int i = 0; i < state.height(); i++) {
			if (state.pancakes[i].burntSideUp()) {
				return false;
			}
		}
		if (inValidOrder(state)) {
			return true;
		}
		else {
			return false;
		}
	}
	bool areEqual(Stack s1, Stack s2) {

		// if stacks are different heights --> not equal
		if (s1.height() != s2.height()) {
			return false;
		}
		else {
			// if height is equal, compare each pancake
			for (int i = 0; i < s1.height(); i++) {

				// if any pancakes don't match --> not equal
				if (s1.pancakes[i].toChar() != s2.pancakes[i].toChar()) {
					return false;
				}
			}
		}

		// if stacks have been fully compared --> equal
		return true;
	}
	bool alreadyVisited(Stack target) {
		for (int i = 0; i < statesVisited.size(); i++) {
			if (areEqual(statesVisited[i], target)) {
				return true;
			}
		}
		return false;
	}
	bool layerContainsGoal(queue<Stack> batch) {
		while (batch.empty() == false) {
			Stack nextMove = batch.front();
			batch.pop();
			if (debugMode) {
				nextMove.print();
			}
			if (isGoalState(nextMove)) {
				return true;
			}
		}
		return false;
	}
	queue<Stack> generateNextLayer(queue<Stack> possibleMoves) {
	
		queue<Stack> nextLayer;

		while (possibleMoves.empty() == false) {

			Stack move = possibleMoves.front();
			possibleMoves.pop();

			for (int level = 0; level < stack.height(); level++) {
				move.flipFrom(level);
				if (!alreadyVisited(move)) {
					statesVisited.push_back(move);
					nextLayer.push(move);
				}
			}

		}
		return nextLayer;
	}
	int solve(queue<Stack> possibleMoves, double howManyFlips) {

		if (layerContainsGoal(possibleMoves)) {
			return howManyFlips;
		}

		queue<Stack> nextLayer = generateNextLayer(possibleMoves);	
		howManyFlips += 1.5;
	
		if (layerContainsGoal(nextLayer)) {
			return howManyFlips;
		}
		else {
			return solve(nextLayer, howManyFlips + 1);
		}			

	}
};

int main() {

	string input;

	while (cin >> input && input != "0") {

		// setup pancake flipper object
		PancakeFlipper pf;
		pf.stack.initialize(input);

		// start search from initial pancake stack
		pf.statesVisited.push_back(pf.stack);
		queue<Stack> possibleMoves;
		possibleMoves.push(pf.stack);
		pf.minimumFlips = pf.solve(possibleMoves, 0);
		cout << pf.minimumFlips << endl;
		
	}


}


// Goal: all capital (burnt side down) && in order
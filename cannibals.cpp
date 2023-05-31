#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct State {
	int msOnLeft;
	int csOnLeft;
	int msOnRight;
	int csOnRight;
	bool boatOnLeft;
	void print() {
		cout << "LEFT" << "\t" << "RIGHT" << endl;
		cout << "====" << "\t" << "=====" << endl;

		for (int i = 0; i < msOnLeft; i++) 
			cout << "M";		
		cout << "\t";

		for (int i = 0; i < msOnRight; i++) 
			cout << "M";		
		cout << endl;

		for (int i = 0; i < csOnLeft; i++)
			cout << "C";		
		cout << "\t";

		for (int i = 0; i < csOnRight; i++) 
			cout << "C";		
		cout << endl;

		if (boatOnLeft) 
			cout << "B" << endl;
		else 
			cout << "    " << "\t" << "B" << endl;
	
	}
};

bool clearScreenMode;
vector<State> visitedStates;
State startState = { 3, 3, 0, 0, true };
State goalState = { 0, 0, 3, 3, false };

bool safeState(State state) {
	return ((state.msOnLeft >= state.csOnLeft) || (state.csOnLeft > 0 && state.msOnLeft == 0)) 
		&& ((state.msOnRight >= state.csOnRight) || (state.csOnRight > 0 && state.msOnRight == 0));
}
void printMove(int howManyMs, int howManyCs, char prefix = ' ') {
	if (prefix != ' ') {
		cout << "[" << prefix << "]: ";
	}
	cout << "crossRiver(";
	for (int i = 0; i < howManyMs; i++) {
		cout << "M";
	}
	for (int i = 0; i < howManyCs; i++) {
		cout << "C";
	}
	cout << ");" << endl;
}
State crossRiver(State state, int howManyMs, int howManyCs) {
	bool enough = true;
	State copy = state;
	if (state.boatOnLeft) { 
		if (state.msOnLeft >= howManyMs && state.csOnLeft >= howManyCs) {
			state.msOnLeft -= howManyMs;
			state.msOnRight += howManyMs;
			state.csOnLeft -= howManyCs;
			state.csOnRight += howManyCs;
			state.boatOnLeft = !state.boatOnLeft;
		}
		else {
			// print failed move - not enough, prune
			//printMove(howManyMs, howManyCs, 'X');
			enough = false;
		}
	}
	else { 
		if (state.msOnRight >= howManyMs && state.csOnRight >= howManyCs) {
			state.msOnRight -= howManyMs;
			state.msOnLeft += howManyMs;
			state.csOnRight -= howManyCs;
			state.csOnLeft += howManyCs;
			state.boatOnLeft = !state.boatOnLeft;
		}
		else {
			// print failed move - not enough, prune
			//printMove(howManyMs, howManyCs, 'X');
			enough = false;
		}
	}
	if (safeState(state) && enough) {
		return state;
	}
	else {
		// print failed move - missionaries outnumbered, prune
		return copy;
	}
}
bool areEqual(const State& s1, const State& s2) {
	return (s1.boatOnLeft == s2.boatOnLeft
		&& s1.csOnLeft == s2.csOnLeft
		&& s1.csOnRight == s2.csOnRight
		&& s1.msOnLeft == s2.msOnLeft
		&& s1.msOnRight == s2.msOnRight);
}
bool alreadyVisited(State& state) {
	for (int i = 0; i < visitedStates.size(); i++) {
		if (areEqual(state, visitedStates[i])) {
			return true;
		}
	}
	return false;
}
queue<State> generateNextLayer(queue<State> possibleMoves) {

	// try each possible move from every possible move
	queue<State> nextLayer;
	while (!possibleMoves.empty()) {

		State state = possibleMoves.front();
		possibleMoves.pop();

		State newState;
		for (int i = 1; i <= 5; i++) {
			switch (i) {
			case 1: newState = crossRiver(state, 1, 0); break; // move m, b
			case 2: newState = crossRiver(state, 2, 0); break; // move m, m, b
			case 3: newState = crossRiver(state, 0, 1); break; // move c, b
			case 4: newState = crossRiver(state, 0, 2); break; // move c, c, b
			case 5: newState = crossRiver(state, 1, 1); break; // move m, c, b
			}			
			
			if (!alreadyVisited(newState)) {				
				visitedStates.push_back(newState);
				nextLayer.push(newState);
			}
			else {
				// print failed move - already visited, prune
				//cout << "[X]: crossRiver() == ancestor node;" << endl;
			}
		}
	}
	return nextLayer;
}
bool layerContainsGoal(queue<State> layer, int howManyMoves) {
	cout << "_____________________________________" << endl;
	cout << "==============[LAYER " << howManyMoves << "]==============" << endl << endl;
	while (!layer.empty()) {
		cout << "______________" << endl;
		layer.front().print();
		cout << "______________" << endl;
		cout << endl;
		if (areEqual(layer.front(), goalState)) {
			cout << endl;
			cout << "[Found goal node!]" << endl;
			return true;
		}
		layer.pop();
	}
	cout << endl;
	cout << "[Goal node isn't in this layer.]" << endl;
	return false;
}
int solve(queue<State> possibleMoves, int howManyMoves) {

	// generate next layer of nodes 
	queue<State> nextLayer = generateNextLayer(possibleMoves);

	system("pause");
	if (clearScreenMode) {
		cout << endl;
		system("cls");
	}
	else {
		cout << endl;
	}

	// check for goal node in generated layer
	if (layerContainsGoal(nextLayer, howManyMoves)) {
		return howManyMoves;
	}

	// otherise, continue search in next layer of tree
	else {
		return solve(nextLayer, howManyMoves + 1);
	}

}

int main() {
	char input;
	do {
		system("cls");
		cout << "Clear screen after each layer? (y/n): ";
	} while (cin >> input && (toupper(input) != 'Y' && toupper(input) != 'N'));
	system("cls");
	cout << "This program displays each layer of nodes in the search tree" << endl
		<< "of the Missionaries & Cannibals Problem. It only displays the" << endl
		<< "possible moves found in each layer. With each layer, it prunes" << endl
		<< "the moves it has visited to avoid infinite search loops. It also" << endl
		<< "prunes the nodes that it cannot make";
	system("cls");
	switch (toupper(input)) {
	case 'Y': clearScreenMode = true; break;
	case 'N': clearScreenMode = false; break;
	}
	cout << "_____________________________________" << endl;
	cout << "==============[START]================" << endl << endl;
	cout << "______________" << endl;
	startState.print();
	cout << "______________" << endl;
	cout << endl;
	queue<State> possibleMoves;
	possibleMoves.push(startState);
	visitedStates.push_back(startState);
	cout << "Moves Made: " << solve(possibleMoves, 1) << endl;
	
}
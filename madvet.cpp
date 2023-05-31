#include <iostream>
#include <vector>
#include <queue>
using namespace std;

enum class Way {
	forward,
	reverse
};

enum class Move {
	A, Ar, B, Br, C, Cr
};

struct Group {
	int ants, beavers, cougars;
	bool contains(int a, int b, int c) {
		return (ants >= a)
			&& (beavers >= b)
			&& (cougars >= c);
	}
	void print() {
		cout << "{" << ants << beavers << cougars << "} ";
	}
};

struct Machine {
	int antsIn, beaversIn, cougarsIn;
	int antsOut, beaversOut, cougarsOut;

	Group useMachine(Group groupIn, Way way) {
		Group groupOut = groupIn;
		if (way == Way::forward && 
			groupIn.contains(antsIn, beaversIn, cougarsIn)) {
			groupOut.ants -= antsIn;
			groupOut.beavers -= beaversIn;
			groupOut.cougars -= cougarsIn;
			groupOut.ants += antsOut;
			groupOut.beavers += beaversOut;
			groupOut.cougars += cougarsOut;
		}
		else if (way == Way::reverse && 
			groupIn.contains(antsOut, beaversOut, cougarsOut)) {
			groupOut.ants -= antsOut;
			groupOut.beavers -= beaversOut;
			groupOut.cougars -= cougarsOut;
			groupOut.ants += antsIn;
			groupOut.beavers += beaversIn;
			groupOut.cougars += cougarsIn;
		}
		return groupOut;
	}
};

Group start, goal;
vector<Group> visited;
Machine A = { 1, 0, 0 };
Machine B = { 0, 1, 0 };
Machine C = { 0, 0, 1 };

bool equal(const Group& start, const Group& goal) {
	return (start.ants == goal.ants)
		&& (start.beavers == goal.beavers)
		&& (start.cougars == goal.cougars);
}

bool alreadyVisited(Group& target) {
	for (int i = 0; i < visited.size(); i++) {
		if (equal(target, visited[i])) {
			return true;
		}
	}
	return false;
}

bool layerContainsGoal(queue<Group> nextLayer) {
	while (!nextLayer.empty()) {
		if (equal(nextLayer.front(), goal)) {
			return true;
		}
		nextLayer.pop();
	}
	return false;
}

void printQueue(queue<Group> queue) {
	while (!queue.empty()) {
		queue.front().print();
		queue.pop();
	}
}

queue<Group> generateNextLayer(queue<Group> possibleMoves) {

	queue<Group> nextLayer;

	while (!possibleMoves.empty()) {

		Group groupBefore = possibleMoves.front();
		possibleMoves.pop();

		Group groupAfter;
		for (int i = 0; i < 6; i++) {
			switch ((Move)i) {
			case Move::A:  groupAfter = A.useMachine(groupBefore, Way::forward); break;
			case Move::Ar: groupAfter = A.useMachine(groupBefore, Way::reverse); break;
			case Move::B:  groupAfter = B.useMachine(groupBefore, Way::forward); break;
			case Move::Br: groupAfter = B.useMachine(groupBefore, Way::reverse); break;
			case Move::C:  groupAfter = C.useMachine(groupBefore, Way::forward); break;
			case Move::Cr: groupAfter = C.useMachine(groupBefore, Way::reverse); break;
			}
			if (!alreadyVisited(groupAfter)) {
				visited.push_back(groupAfter);
				nextLayer.push(groupAfter);
			}
		}
	}
	return nextLayer;
}



int solve(queue<Group> possibleMoves, int stepsTaken) {

	if (stepsTaken > 29) {
		return stepsTaken;
	}

	queue<Group> nextLayer = generateNextLayer(possibleMoves);
	//printQueue(nextLayer); // debug
	//system("pause");
	//cout << endl;

	if (layerContainsGoal(nextLayer)) {
		return stepsTaken;
	}
	else {
		return solve(nextLayer, stepsTaken + 1);
	}
}

int main() {
	int howManyTests;
	cin >> howManyTests;
	for (int i = 0; i < howManyTests; i++) {
		int testNumber, howManyQuestions;
		cin >> testNumber >> howManyQuestions;	
		cin >> A.antsOut >> A.beaversOut >> A.cougarsOut;
		cin >> B.antsOut >> B.beaversOut >> B.cougarsOut;
		cin >> C.antsOut >> C.beaversOut >> C.cougarsOut;
		cout << testNumber << " " << howManyQuestions << endl;	
		for (int x = 0; x < howManyQuestions; x++) {				
			int questionNumber;
			cin >> questionNumber
				>> start.ants >> start.beavers >> start.cougars
				>> goal.ants >> goal.beavers >> goal.cougars;
			cout << questionNumber << " ";
			visited.push_back(start);
			queue<Group> possibleMoves;
			possibleMoves.push(start);
			int stepsTaken = solve(possibleMoves, 1);
			if (stepsTaken < 30) {
				cout << stepsTaken << endl;
			}
			else {
				cout << "NO SOLUTION" << endl;
			}
			visited.clear();
		}
	}
}

/*

1
5 6
0 1 1
1 0 1
1 1 0
1 1 2 3 0 1 0
2 1 2 3 0 1 1
3 1 2 4 1 0 0
4 2 0 0 0 2 0
5 2 3 4 0 1 0
6 0 1 0 2 3 4







5
1 2
0 1 0
1 1 1
1 1 0
1 0 1 1 3 0 0
2 1 0 0 2 0 0
2 2
0 3 4
0 0 5
0 0 3
1 2 0 0 0 0 5
2 2 0 0 0 0 4
3 4
0 1 0
1 1 1
1 1 0
1 0 1 1 3 0 0
2 1 0 0 2 0 0
3 2 3 4 5 1 2
4 1 1 2 3 1 1
4 4
0 3 4
0 0 5
0 0 3
1 2 0 0 0 0 5
2 2 0 0 0 0 4
3 1 2 3 0 0 1
4 1 2 3 0 0 2





1
5 3
0 1 1
1 0 1
1 1 0
1 1 2 3 0 1 0
3 1 2 4 1 0 0
5 2 3 4 0 1 0












*/
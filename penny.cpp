#include <iostream>
#include <vector>
using namespace std;

// Program: Penny Game
// Written by: Cason Kirschner

struct SequenceCount {
	int count = 0;
	string sequence = "";
};

int main() {
	int howManyTestCases;
	cin >> howManyTestCases;
	for (int i = 0; i < howManyTestCases; i++) {
		string testCase;
		cin >> testCase;
		vector<SequenceCount> targets = {
		{0, "TTT"}, {0, "HTT"},
		{0, "THT"}, {0, "HHT"},
		{0, "TTH"}, {0, "HTH"},
		{0, "THH"}, {0, "HHH"}          
		};
		for (int currentTarget = 0; currentTarget < targets.size(); currentTarget++) {
			for (int currentRange = 0; currentRange < testCase.size() - 2; currentRange++) {
				if (testCase[currentRange] == targets[currentTarget].sequence[0] &&
					testCase[currentRange + 1] == targets[currentTarget].sequence[1] &&
					testCase[currentRange + 2] == targets[currentTarget].sequence[2]) {
					targets[currentTarget].count++;
				}
			}
		}
		for (int currentTarget = 0; currentTarget < targets.size(); currentTarget++) {
			if (currentTarget != 0) {
				cout << " ";
			}
			cout << targets[currentTarget].count;
		}
		cout << endl;
	}
}
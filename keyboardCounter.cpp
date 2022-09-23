#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// This program takes input from the user, counts every character typed in,
// and prints a list of the frequencies 

struct Letter {
	Letter(char ch, int c) {
		character = ch;
		count = c;
	}
	char character;
	int count;
};

vector<Letter> countAllLetters(string line) {
	vector<Letter> allLetters;
	for (int i = 0; i < line.size(); i++) {
		bool matchFound = false;
		for (int p = 0; p < allLetters.size(); p++) {
			if (line[i] == allLetters[p].character) {
				allLetters[p].count++;
				matchFound = true;
			}
		}
		if (matchFound == false) {
			Letter newLetter(line[i], 1);
			allLetters.push_back(newLetter);
		}
	}
	return allLetters;
}

bool compareLetters(Letter a, Letter b) {
	return (a.count > b.count);
}

vector<Letter> sortAllLetters(vector<Letter> allLetters) {
	sort(allLetters.begin(), allLetters.end(), compareLetters);
	return allLetters;
}

void printAllLetters(vector<Letter> allLetters) {
	for (int i = 0; i < allLetters.size(); i++) {
		cout << allLetters[i].character << ": ";
		for (int y = 0; y < allLetters[i].count; y++) {
			cout << "|";
		}
		cout << " " << allLetters[i].count << endl;
	}
}

int main() {
	string line;
	do {
		getline(cin, line);
		printAllLetters(sortAllLetters(countAllLetters(line)));
	} while (line != "done");
}
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool areAnagrams(string wordOne, string wordTwo) {
	for (int i = 0; i < wordOne.size(); i++) {

	}
	for (int i = 0; i < wordTwo.size(); i++) {

	}
}

int main() {
	bool loopDone = false;
	string wordOne = "";
	string wordTwo = "";
	do {
		cin >> wordOne;
		cin >> wordTwo;
		if (wordOne != "<end>" && wordTwo != "<end>") {
			if (areAnagrams(wordOne, wordTwo)) {
				cout << "YES" << endl;
			}
			else {
				cout << "NO" << endl;
			}
		}
		else {
			loopDone = true;
		}
	} while (loopDone == false);
}
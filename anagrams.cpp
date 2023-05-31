#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool areAnagrams(string wordOne, string wordTwo) {
	int wordCountOne[26] = { 0 };
	int wordCountTwo[26] = { 0 };
	for (int i = 0; i < wordOne.size(); i++) {
		wordCountOne[toupper(wordOne[i]) - 'A']++;
	}
	for (int i = 0; i < wordTwo.size(); i++) {
		wordCountTwo[toupper(wordTwo[i]) - 'A']++;
	}
	for (int i = 0; i < 26; i++) {
		if (wordCountOne[i] != wordCountTwo[i]) {
			return false;
		}
	}
	return true;
}

int main() {
	bool loopDone = false;
    string wordOne = "";
    string wordTwo = "";
    do {
        cout << "Word One: ";
        cin >> wordOne;
        cout << "Word Two: ";
        cin >> wordTwo;
        if (wordOne != "<end>" && wordTwo != "<end>") {
            if (areAnagrams(wordOne, wordTwo)) {
                cout << "[ANAGRAMS]" << endl << endl;
            }
            else {
                cout << "[NOT ANAGRAMS]" << endl << endl;
            }
        }
        else {
            loopDone = true;
        }
    } while (loopDone == false);
}
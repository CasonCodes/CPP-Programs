#include <iostream>
#include <string>
using namespace std;

// sorts a given word in alphabetical order by use of a bubble sort

string sortWord(string word) {
	bool sorted = false;
	for (int x = 0; x < word.size(); x++) {
		for (int y = 0; y < word.size(); y++) {
			if (word[x] < word[y]) {
				char temp = word[x];
				word[x] = word[y];
				word[y] = temp;
			}
		}
	}
	return word;
}

int main() {
	string word;
	char response;
	do {
		cout << "Word to sort:\t";
		cin >> word;
		cout << "Sorted word:\t" << sortWord(word) << endl;
		cout << "Again? (Y/N): ";
		cin >> response;
		cout << endl;
	} while ((toupper(response) == 'Y'));
}
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

vector<string> wordBank;

void loadWordDatabase(vector<string>& wordBank) {
	ifstream wordDatabase;
	wordDatabase.open("allWords.txt");
	while (wordDatabase) {
		string word; 
		wordDatabase >> word;
		wordBank.push_back(word);
	}
	wordDatabase.close();
}

bool partialMatch(string searchWord, string databaseWord) {
	int count = 0;
	bool foundMatch = false;
	for (int i = 0; i < searchWord.size(); i++) {
		for (int j = 0; j < databaseWord.size(); j++) {
			if (searchWord[i] == databaseWord[j]) {
				if (searchWord)
					count++;
				
				if (count == searchWord.size()) {
					foundMatch = true;
				}
				else {
					i++;
				}
			}
		}
		if (foundMatch) {
			break;
		}
	}
	return foundMatch;
}

void searchForWord(string searchWord) {
	cout << "Search results:" << endl;
	for (int i = 0; i < wordBank.size(); i++) {
		if (wordBank[i] == searchWord || partialMatch(searchWord, wordBank[i])) {
			cout << "\t" << wordBank[i] << endl;
		}
	}
	cout << endl;
}



int main() {
	string searchWord = "";
	bool wordSearched = false;
	loadWordDatabase(wordBank);
	while (wordSearched == false) {
		cout << "Search word: ";
		cin >> searchWord;
		searchForWord(searchWord);
	}
}
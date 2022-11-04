// Problem: Interleaved 2 of 5
// Written By: Cason Kirschner

#include <iostream>
#include <string>
#include <queue>
using namespace std;

string startingSeqence = "NnNn";

string digitCode[10] = 
//  0		1		2		3		4
{"nnwwn","wnnnw","nwnnw","wwnnn","nnwnw"
,"wnwnn","nwwnn","nnnww","wnnwn","nwnwn"};
//  5		6		7		8		9

string endingSequence = "WnN";

string capitalize(string sequence) {
	for (int i = 0; i < sequence.size(); i++) {
		sequence[i] = toupper(sequence[i]);
	}
	return sequence;
}

string interleave(string sequenceOne, string sequenceTwo) {
	string newSequence = "";
	for (int i = 0; i < 5; i++) {
		newSequence += sequenceOne[i];
		newSequence += sequenceTwo[i];
	}
	return newSequence;
}

bool isOdd(string sequence) {
	return sequence.size() % 2 != 0;
}

string addLeadingZero(string sequence) {
	string copyOfSequence = sequence;
	sequence.clear();
	return sequence = "0" + copyOfSequence;
}

int main() {
	string input = "";
	while (cin >> input && input != "0") {
		if (isOdd(input)) {
			input = addLeadingZero(input);
		}
		queue<char> number;
		for (int i = 0; i < input.size(); i++) {
			number.push(input[i]);
		}
		string barcode = startingSeqence;
		while (!number.empty()) {
			string digitOne = capitalize(digitCode[number.front() - '0']);
			number.pop();
			string digitTwo = digitCode[number.front() - '0'];
			number.pop();
			barcode += interleave(digitOne, digitTwo);
		}
		barcode += endingSequence;
		cout << barcode << endl;
	}
}

// NOTES:
// the number to be encoded must have an even number of digits - add leading zeros until even
// all barcodes have to begin with (narrow bar, narrow space, narrow bar, and narrow space)
// all barcodes have to end with (wide bar, narrow space, and narrow bar)
// use uppercase letters for bars, 
// use lowercase letters for the spaces
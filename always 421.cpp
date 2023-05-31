#include <iostream>
using namespace std;

bool isEven(int number) {
	if (number % 2 == 0) {
		return true;
	}
	else {
		return false;
	}
}
void alwaysFourTwoOne() {
	// get starting number
	cout << "Starting Number: ";
	int number;
	cin >> number;

	// variables
	int four = 0;
	int two = 0;
	int one = 0;
	int iterations = 0;

	while (four < 3 || two < 3 || one < 3) {

		iterations++;
		cout << number;

		// if even divide by 2
		if (isEven(number)) {
			number /= 2;
			cout << " / 2 ======= " << number << endl;
		}

		// if odd multiply by 3 and add 1
		else {
			number *= 3;
			number += 1;
			cout << " x 3 + 1 === " << number << endl;
		}

		// quit when 421 sequence is found
		switch (number) {
		case 4: four++; break;
		case 2: two++; break;
		case 1: one++; break;
		}

		// quit if negative
		if (number < 0) {
			cout << "ERROR" << endl;
			break;
		}
	}

	// display number of iterations
	cout << "Iterations: " << iterations << endl;
}
void alwaysTwo() {
	cout << "Starting Number: ";
	int number;
	cin >> number;
	int startingNumber = number;
	cout << number;
	number *= 3;
	cout << " x 3 = " << number << endl;
	cout << number;
	number += 6;
	cout << " + 6 = " << number << endl;
	cout << number;
	number /= 3;
	cout << " / 3 = " << number << endl;
	cout << number;
	number -= startingNumber;
	cout << " - " << startingNumber << " = " << number << endl;
	cout << "The answer is always 2." << endl;
}
void alwaysThirtySeven() {
	cout << "Three Digit Repeating Number (ex. 555): ";
	int number;
	cin >> number;
	int digit = number / 111;
	cout << number << " / (" << digit << " + " << digit << " + " << digit << ") = ";
	digit = (digit + digit + digit);
	number /= digit;
	cout << number << endl;
	cout << "The answer is always 37." << endl;
}
int main() {
	int choice;
	do {
		const int MAX = 4;
		int choices[MAX] = {421, 2, 37, 0};
		for (int i = 0; i < MAX; i++) {
			cout << choices[i] << " ";
		}
		cout << endl << "Choice: ";
		cin >> choice;
		cout << endl;
		if (choice == 421) {
			alwaysFourTwoOne();
		}
		if (choice == 2) {
			alwaysTwo();
		}
		if (choice == 37) {
			alwaysThirtySeven();
		}
		cout << endl << "-----------------------------------------" << endl << endl;
	} while (choice != 0);
}
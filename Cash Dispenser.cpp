#include <iostream>
using namespace std;

void dispenseCash(double& askedAmount, double& givenAmount) {
	while (askedAmount / 100 >= 1) {
		cout << "$100.00 Dispensed..." << endl;
		askedAmount -= 100;
		givenAmount += 100;
	}

	while (askedAmount / 50 >= 1) {
		cout << "$50.00 Dispensed..." << endl;
		askedAmount -= 50;
		givenAmount += 50;
	}

	while (askedAmount / 20 >= 1) {
		cout << "$20.00 Dispensed..." << endl;
		askedAmount -= 20;
		givenAmount += 20;
	}

	while (askedAmount / 10 >= 1) {
		cout << "$10.00 Dispensed..." << endl;
		askedAmount -= 10;
		givenAmount += 10;
	}

	while (askedAmount / 5 >= 1) {
		cout << "$5.00 Dispensed..." << endl;
		askedAmount -= 5;
		givenAmount += 5;
	}

	while (askedAmount / 1 >= 1) {
		cout << "$1.00 Dispensed..." << endl;
		askedAmount -= 1;
		givenAmount += 1;
	}

	while (askedAmount / 0.25 >= 1) {
		cout << "$0.25 Dispensed..." << endl;
		askedAmount -= 0.25;
		givenAmount += 0.25;
	}

	while (askedAmount / 0.10 >= 1) {
		cout << "$0.10 Dispensed..." << endl;
		askedAmount -= 0.10;
		givenAmount += 0.10;
	}

	while (askedAmount / 0.05 >= 1) {
		cout << "$0.05 Dispensed..." << endl;
		askedAmount -= 0.05;
		givenAmount += 0.05;
	}

	while (askedAmount / 0.01 >= 1) {
		cout << "$0.01 Dispensed..." << endl;
		askedAmount -= 0.01;
		givenAmount += 0.01;
	}
}

int main() {

	char response;

	do {

		system("cls");

		double askedAmount = 0.00;
		double givenAmount = 0.00;

		cout << "How much money do you want?" << endl
			<< "\t$";
		cin >> askedAmount;
		cout << endl;

		dispenseCash(askedAmount, givenAmount);
		cout << endl << "Given Amount: $" << givenAmount << endl;

		cout << endl << "Would you like more money? (Y/N)" << endl
			<< "\t> ";
		cin >> response;
		response = toupper(response);

	} while (response == 'Y');
}
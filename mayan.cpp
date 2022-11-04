#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int power(int x, int y) {
	int product = x;
	if (y != 0) {
		for (int i = 1; i < y; i++) {
			product *= x;
		}
	}
	else {
		return 1;
	}
	return product;
}

struct Digit {
	int dots = 0;
	int bars = 0;
	void reset() { dots = 0; bars = 0; }
	int value() { return dots + (bars * 5); }
};

struct Number {
	vector<Digit> digits;
	int value() { 
		int exponent = 0;
		int totalValue = 0;
		for (int i = digits.size() - 1; i >= 0; i--, exponent++) {
			totalValue += digits[i].value() * power(20, exponent);
		}
		return totalValue;
	}
};

class MayanCalc {
	char _operator;
	vector<Number> numbers;
	void printMayanSymbols(Number number) {
		bool hasPrintedNonZero = false;
		if (number.value() == 0) {
			hasPrintedNonZero = true;
		}
		for (int i = 0; i < number.digits.size(); i++) {
			if (number.digits[i].dots > 0) {
				for (int x = 0; x < number.digits[i].dots; x++) {
					cout << "*";
				}
				cout << endl;
				hasPrintedNonZero = true;
			}
			if (number.digits[i].bars > 0) {
				for (int x = 0; x < number.digits[i].bars; x++) {
					cout << "-----" << endl;
				}
				hasPrintedNonZero = true;
				
			}
			if (number.digits[i].value() == 0 && hasPrintedNonZero) {
				cout << "@" << endl;
			}
			if (i != number.digits.size() - 1 && hasPrintedNonZero) {
				cout << endl;
			}
			
		}
		cout << "#" << endl;
	}
	void toBase20(int value) {
		int ans = 0;
		Digit digit;
		Number number;
		if (value != 0) {
			for (int i = 8000; value != 0; i /= 2, i /= 10) {
				ans = value / i;
				value -= (i * ans);
				digit.bars = (ans / 5);
				digit.dots = (ans - (digit.bars * 5));
				number.digits.push_back(digit);
			}
		}
		else {
			number.digits.push_back(digit);
		}
		printMayanSymbols(number);
	}

public:

	bool getHeading() {
		string input = "";
		getline(cin, input);
		if (input != "END") {
			cout << input << endl;
			return true;
		}
		else {
			return false;
		}
	}
	void getNumber() {
		Digit digit;
		Number number;
		string input = "";
		bool keepGoing = true;
		do {
			getline(cin, input);
			switch (input[0]) {
			case '@': break;
			case '-': digit.bars++; break;
			case '*': digit.dots = input.size(); break;
			case '\0': number.digits.push_back(digit); digit.reset(); break;
			case '#': number.digits.push_back(digit); keepGoing = false; break;
			}
		} while (input != "#");
		numbers.push_back(number);
	}
	void getOperator() {
		cin >> _operator;
		cin.ignore();
	}
	void evaluate() {
		switch (_operator) {
		case '+': toBase20(numbers[0].value() + numbers[1].value()); break;
		case '-': toBase20(numbers[0].value() - numbers[1].value()); break;
		}
		numbers.clear();
	}
};

int main() {
	MayanCalc calc;
	while (calc.getHeading()) {
		calc.getNumber();
		calc.getOperator();
		calc.getNumber();
		calc.evaluate();
	}
}
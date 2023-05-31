#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "polynomial.h"

//
// TODO: You may NOT use a vector for your project.
//       You MUST implement your own Polynomial type as a linked list.
//

// Test whether there are any (non-whitespace) characters left in the stream
bool empty(std::istream& in) {
	char c;
	if (in >> c) {
		in.putback(c);
		return false;
	}
	else {
		return true;
	}
}

// Try to get specified character from the stream
bool readChar(std::istream& in, char required) {
	char c;
	if (in >> c) {
		if (c == required) {
			return true;
		}
		in.putback(c);
	}
	return false;
}

// Try to get an operator (+/-) from the stream
bool readOperator(std::istream& in, char& op) {
	if (readChar(in, '-')) {
		op = '-';
		return true;
	}
	else if (readChar(in, '+')) {
		op = '+';
		return true;
	}
	else {
		return false;
	}
}

// Try to get the coefficient from the stream
bool readCoefficient(std::istream& in, double& coeff) {
	bool neg = readChar(in, '-');
	if (!(in >> coeff)) {
		// Coefficient is optional
		coeff = 1.0;
		in.clear();
	}
	if (neg) {
		coeff = -coeff;
	}
	return true;
}

// Try to get variable + exponent from the stream
bool readExp(std::istream& in, unsigned int& exp) {
	if (readChar(in, 'x')) {
		if (readChar(in, '^')) {
			// If there's a caret, there must be an exponent
			if (!(in >> exp)) return false;
		}
		else {
			// No caret
			exp = 1;
		}
	}
	else {
		// No variable
		exp = 0;
	}
	return true;
}

// Try to get a term from the stream
// @param hasOp = is there an operator (+/-) before this term?
bool readTerm(std::istream& in, bool hasOp, Term& term) {
	char op = '+';
	if (hasOp) {
		if (!readOperator(in, op)) return false;
	}

	if (!readCoefficient(in, term.coeff)) return false;
	if (op == '-') {
		term.coeff = -term.coeff;
	}

	if (!readExp(in, term.exp)) return false;

	return true;
}

// Try to get a polynomial from the stream
bool readPolynomial(std::istream& in, Polynomial& polynomial) {
	double coeff;
	unsigned int exp;
	bool hasOp = false;

	do {
		Term t;
		if (!readTerm(in, hasOp, t)) return false;
		polynomial.push_back(t);
		//
		// TODO: you won't be using a vector, so you can't use push_back
		//       use the function you wrote for adding a term to a polynomial
		//
		hasOp = true;
	} while (!empty(in));

	return true;
}

// Read one polynomial at a time
// Print out each polynomial found
int main() {
	std::string line;
	while (std::getline(std::cin, line)) {
		// Make a stream just for this one line
		std::istringstream strIn(line);
		if (!empty(strIn)) {
			Polynomial p;

			//
			// TODO: Initialize p as necessary
			initialize(&p);
			//



			
			






			
			if (readPolynomial(strIn, p)) {
				for (size_t i = 0; i < p.size(); ++i) {
					std::cout << "Term(" << p[i].coeff << ", " << p[i].exp << ") ";
				}
				std::cout << std::endl;
				//
				// TODO: You are not printing out polynomials, so you won't use this for loop
				//       Instead add them up and keep track of the biggest one
				//
			}
			else {
				std::cerr << "Error: " << line << std::endl;
			}
			//
			// TODO: Tear down p
			//
		}
	}
}
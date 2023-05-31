// HEADER FILE BLUEPRINTS | IMPLEMENTATIONS

#include <iostream>
#include "polynomial.h"

// =========================
// What can a polynomial do?
// =========================

bool initialize(Polynomial* myPoly) {
	bool success = false;

	Term* newTerm = new Term;
	myPoly->Head = newTerm;
	newTerm->nextTerm = NULL;
	newTerm->coefficient = 0.00;
	newTerm->exponent = 0;
	success = true;

	return success;
};

bool addTerm(Polynomial myPoly, Term newTerm) {
	bool success = false;



	return success;
};

bool addPolynomial(Polynomial myPoly, Polynomial otherPoly) {
	bool success = false;

	

	return success;
};

int getDegree(Polynomial myPoly) {
	bool success = false;



	return success;
};

bool compare(Polynomial myPoly, Polynomial otherPoly) {
	bool success = false;



	return success;
};

bool print(Polynomial myPoly) {
	bool success = false;



	return success;
};

bool releaseMemory(Polynomial myPoly) {
	bool success = false;



	return success;
};
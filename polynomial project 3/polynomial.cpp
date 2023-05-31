#include <iostream>
#include "polynomial.h"
#include "privatePolynomialFunctions.h"

using std::cout;
using std::endl;

void initPoly(Polynomial* myPoly) {
	
	Term newTerm;
	newTerm.exp = 0;
	newTerm.coeff = 0;
	newTerm.next = NULL;
	insertTerm(&newTerm, myPoly);

}

void addTermWithPoly(Term myTerm, Polynomial* myPoly) {

	insertTerm(&myTerm, myPoly);

}

void addPolyWithPoly(Polynomial otherPoly, Polynomial* myPoly) {
	

	
}

void getDegFromPoly(Polynomial myPoly, unsigned int* degree) {

	Term* currentTerm = myPoly.head;
	for (int i = 0; i < getPolySize(&myPoly); i++) {
		if ((*degree) < currentTerm->exp) {
			(*degree) = currentTerm->exp;
		}
		currentTerm = currentTerm->next;
	}

}

void compareTwoPolys(Polynomial firstPoly, Polynomial secondPoly) {
	


}

void printPoly(Polynomial myPoly) {

	bool allCoefficientsAreZero = true;
	Term* currentTerm = myPoly.head;

	for (int i = 0; i < getPolySize(&myPoly); i++) {

		if (currentTerm->coeff != 0) {

			allCoefficientsAreZero = false;

			if (currentTerm->coeff != 1) {
				cout << currentTerm->coeff;
			}

			cout << "x";

			if (currentTerm->exp != 0 && currentTerm->exp != 1) {
				cout << "^" << currentTerm->exp;
			}

			cout << " ";

			if (currentTerm->next->coeff < 0) {
				cout << " - ";
				// turn the negative number positive because 
				// it's part of the polynomial syntax
				currentTerm->next->coeff = currentTerm->next->coeff * -1;
			}
			else if (currentTerm->next->coeff > 0) {
				cout << " + ";
				// turn the positive number negative because 
				// it's part of the polynomial syntax
				currentTerm->next->coeff = currentTerm->next->coeff * -1;
			}
		}
		currentTerm = currentTerm->next;
	}

	if (allCoefficientsAreZero) {
		cout << "0" << endl;
	}
}

void releasePoly(Polynomial* myPoly) {
	
	Term* currentTerm;
	do  {
		currentTerm = (*myPoly).head;
		(*myPoly).head = currentTerm->next;
		delete currentTerm;
	} while (currentTerm->next != NULL);
	
}
#include <iostream>
#include "privatePolynomialFunctions.h"
#include "polynomial.h"

bool empty(Polynomial myList) {

	bool listIsEmpty = false;
	if ((myList).head == NULL) {
		listIsEmpty = true;
	}
	return listIsEmpty;

}

int getPolySize(Polynomial* myPoly) {

	int count = 0;
	Term* currentTerm = (*myPoly).head;
	while (currentTerm != NULL) {
		currentTerm = currentTerm->next;
		count++;
	}
	return count;
	
}

void insertTerm(Term* myTerm, Polynomial* myPoly) {

	(*myTerm).next = (*myPoly).head;
	(*myPoly).head = myTerm;

}


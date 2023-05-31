#include <iostream>
#include "linkedList.h"
#include "polynomial.h"

// =========================
// What can a linked list do?
// =========================

bool sort(Polynomial* myPoly) {

}

bool add(Term* thisTerm, Term* thatTerm) {

}

bool insert(Polynomial* myPoly, Term* newTerm) {
	bool success = false;

	newTerm->next = myPoly->Head;
	myPoly->Head = newTerm;
	success = true;

	return success;
}

bool isEmpty(Polynomial* myPoly) {
	bool empty = false;

	if ((*myPoly).Head == NULL) {
		empty = true;
	}

	return empty;
}

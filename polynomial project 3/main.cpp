#include <iostream>
#include "polynomial.h"

int main() {

	Polynomial myPoly;
	initPoly(&myPoly);

	Term myTerm;
	myTerm.coeff = 7;
	myTerm.exp = 2;
	myTerm.next = NULL;

	addTermWithPoly(myTerm, &myPoly);

	printPoly(myPoly);

	///////////////////////////////////////////
	//Polynomial myPoly;
	//initPoly(&myPoly);
	///////////////////////////////////////////
	//Term myTerm;
	//myTerm.coeff = 5;
	//myTerm.coeff = 4;
	//myTerm.next = NULL;
	//addTermToPoly(myTerm, &myPoly);
	///////////////////////////////////////////
	//Polynomial otherPoly;
	//initPoly(&otherPoly);
	//addPolyToPoly(otherPoly, &myPoly);
	///////////////////////////////////////////
	//unsigned int myDegree;
	//getDegFromPoly(myPoly, &myDegree);
	///////////////////////////////////////////
	//comparePolys(myPoly, otherPoly);
	///////////////////////////////////////////
	//printPoly(myPoly);
	///////////////////////////////////////////
	//releasePoly(&myPoly);
	//releasePoly(&otherPoly);
	///////////////////////////////////////////
}
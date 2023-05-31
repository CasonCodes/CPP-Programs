// CLIENT FILE | MAIN

#include <iostream>
#include "readInput.h"
#include "polynomial.h"

using std::cout;
using std::endl;

int main() {

	Polynomial newPoly;

	while (!cin.eof()) {

		(newPoly) = new Polynomial;

		initialize(&newPoly);

		string thePoly;
		string theTerm;
		readIn(&thePoly);
		theTerm = parse(&thePoly);
		add(&theTerm);



	}
}
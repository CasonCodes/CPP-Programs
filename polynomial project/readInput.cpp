#include <iostream>
#include <string>
#include "readInput.h"
#include "polynomial.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;

bool readIn(string* thePoly) {
	bool success = false;

	getline(cin, (*thePoly));
	success = true;

	return success;
}

string parse(string* thePoly) {
	
	string theTerm;

	for (int i = 0; i < thePoly->size(); i++) {

		// whitespace
		if (thePoly[i] != " ") { 
			// marks end of term

			// operators
			if (thePoly[i] == "+" || thePoly[i] == "-" || thePoly[i] == "^") { 
				theTerm.append(thePoly[i]);
			}

			if (thePoly[i] == "x") {
				theTerm.append(thePoly[i]);
			}

			if (thePoly[i] == "0" || thePoly[i] == "5" || // digits
				thePoly[i] == "1" || thePoly[i] == "6" ||
				thePoly[i] == "2" || thePoly[i] == "7" ||
				thePoly[i] == "3" || thePoly[i] == "8" ||
				thePoly[i] == "4" || thePoly[i] == "9") {
				theTerm.append(thePoly[i]);
		}

		

		}
	}
	return theTerm;
}

bool add(string* theTerm) {
	
}
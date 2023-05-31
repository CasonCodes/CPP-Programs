///////////////////////////////////////////
// NAME:		Cason Kirschner
// COURSE:		COMP 345
// INSTRUCTOR:	G Faust
// HOMEWORK:	#1 - Command Line Programs
// PROGRAM:		rand.cpp
///////////////////////////////////////////

#include <iostream>
#include <random>

using std::cout;
using std::cerr;
using std::endl;

std::random_device rd;
std::default_random_engine engine(rd());

// generates one random number and prints it to the screen.
// 2 parameters: min value, max value
void generateRandomNumber(int fromThis, int toThis) {
	std::uniform_int_distribution<int> random(fromThis, toThis);
	int random_number = random(engine);
	cout << random_number << " ";
}

// generates "thisMany" random numbers and prints them to the screen.
// 1 parameter: how many numbers to generate
void printThisManyRandomNumbers(int thisMany) {
	for (int index = 0; index < thisMany; index++) {
		generateRandomNumber(0, 100);
	}
}

// generates "thisMany" random numbers between 0 and a max value passed in.
// 2 parameters: how many numbers to generate, max value 
void printThisManyRandomNumbersBetweenZeroAndThis(int thisMany, int toThis) {
	for (int index = 0; index < thisMany; index++) {
		generateRandomNumber(0 , toThis);
	}
}

// generates "thisMany" random numbers between min and max values passed in.
// 3 parameters: how many numbers to generate, min value, max value
void printThisManyRandomNumbersBetweenThisAndThis(int thisMany, int fromThis, int toThis) {
	for (int index = 0; index < thisMany; index++) {
		generateRandomNumber(fromThis, toThis);
	}
}

// prints how to enter commmands for the programto the screen.
// 0 parameters:
void printErrorMessage() {
	cerr << "Usage: rand" << endl;
	cerr << "       rand count" << endl;
	cerr << "       rand count upper" << endl;
	cerr << "       rand count lower upper" << endl;
}

// main funtion: interprets the different values of argc as 
// status codes to understand different kinds of user input.
// 2 parameters: command line arguments: argc, argv[]
int main(int argc, char* argv[]) {

	// argc - stores how many elements are in argv[].
	// argv[] - stores the command line arguments.

	switch (argc) {
	case 1: generateRandomNumber(0, 100); break;
	case 2: printThisManyRandomNumbers(atoi(argv[1])); break;
	case 3: printThisManyRandomNumbersBetweenZeroAndThis(atoi(argv[1]), (atoi(argv[2])));  break;
	case 4: printThisManyRandomNumbersBetweenThisAndThis(atoi(argv[1]), atoi(argv[2]), atoi(argv[3])); break;
	default: printErrorMessage(); break;
	}
}
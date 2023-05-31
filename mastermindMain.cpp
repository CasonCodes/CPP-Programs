////////////////////////////////////
// NAME:		Cason Kirschner
// COURSE:		COMP 345
// INSTRUCTOR:	G Faust
// PROJECT:		#1 - Mastermind
////////////////////////////////////



#include <iostream>
#include <vector>
#include <random>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::ofstream;

std::random_device rd;
std::default_random_engine engine(rd());

// Prompts user for the input of two numbers, then performs data 
// validation to make sure they aren't out of range for the game.
void getLengthAndMaxValues(int& combinationLength, int& maxValidValue) {

	cin >> combinationLength >> maxValidValue;

	if (combinationLength < 2) {
		combinationLength = 2;
	}
	else if (combinationLength > 8) {
		combinationLength = 8;
	}

	if (maxValidValue < 6) {
		maxValidValue = 6;
	}
	else if (maxValidValue > 20) {
		maxValidValue = 20;
	}
}



// Passes in an int vector by reference and generate n 
// pseudorandom integers for the vector to store.
void generateRandomSecret(vector<int>& theSecretCombination,
	int theCombinationLength, int theMaxValidValue) {

	for (int i = 0; i < theCombinationLength; i++) {
		std::uniform_int_distribution<int> random(1, theMaxValidValue);
		int randomNumber = random(engine);
		theSecretCombination.push_back(randomNumber);
	}
}



// Determines whether the user is setting a given password
// or a random password. If a chosen secret is given by the
// user, it stores the numbers in a passed in vector, but if
// the user enters all zeros for the secret, the program
// will generate a random secret for the user to guess.
void getSecretCombination(vector<int>& theSecretCombination,
	int theCombinationLength, int theMaxValidValue, ofstream& outputFile) {

	bool needRandomSecret = true;

	for (int i = 0; i < theCombinationLength; i++) {
		int number;
		cin >> number;
		theSecretCombination.push_back(number);

		if (number != 0)
			needRandomSecret = false;
	}

	if (needRandomSecret) {
		cout << "Using random secret." << endl << endl;
		outputFile << "Using random secret." << endl << endl;
		theSecretCombination.clear();
		generateRandomSecret(theSecretCombination, theCombinationLength, theMaxValidValue);
	}
	else if (!needRandomSecret) {
		cout << "Using given secret." << endl << endl;
		outputFile << "Using given secret." << endl << endl;
	}
}



// Sets up Mastermind by calling other routines to
// get the values of the required parameters for the game,
// outputs the game information prompt, and gets a secret
// combination for the user to guess.
void setupGame(int& theCombinationLength, int& theMaxValidValue,
	vector<int>& theSecretCombination, vector<int>& theUsersGuess, ofstream& outputFile) {

	getLengthAndMaxValues(theCombinationLength, theMaxValidValue);
	cout << "Playing Mastermind with " << theCombinationLength << " numbers (1-" << theMaxValidValue << ")." << endl;
	outputFile << "Playing Mastermind with " << theCombinationLength << " numbers (1-" << theMaxValidValue << ")." << endl;
	getSecretCombination(theSecretCombination, theCombinationLength, theMaxValidValue, outputFile);
}



// Continually asks for the input of four non-negative integers that represent
// the users guess at the secret combination. Performs data validation on the
// users guess to make sure it is within the correct parameters of the game
// and outputs each valid guess to the screen.
void inputGuess(int theNumberOfGuessesMade, int theCombinationLength,
	int theMaxValidValue, vector<int>& theUsersGuess, ofstream& outputFile) {

	bool anInvalidGuessWasDetected;
	bool allNumbersAreZero;

	do {
		theUsersGuess.clear();
		anInvalidGuessWasDetected = false;
		allNumbersAreZero = true;
		for (int i = 0; i < theCombinationLength; i++) {
			int number;
			cin >> number;
			if (number != 0) {
				allNumbersAreZero = false;
			}
			if (number < 1 || number > theMaxValidValue) {
				anInvalidGuessWasDetected = true;
			}
			theUsersGuess.push_back(number);
		}

		if (!allNumbersAreZero) {
			if (anInvalidGuessWasDetected) {
				cout << "Numbers must be between 1 and " << theMaxValidValue << "." << endl << endl;
				outputFile << "Numbers must be between 1 and " << theMaxValidValue << "." << endl << endl;
			}
		}
		else {
			cout << "Guess " << theNumberOfGuessesMade << ": ";
			outputFile << "Guess " << theNumberOfGuessesMade << ": ";
			for (int i = 0; i < theCombinationLength; i++) {
				cout << theUsersGuess[i] << " ";
				outputFile << theUsersGuess[i] << " ";
			}
			cout << endl;
			outputFile << endl;
		}
	} while (anInvalidGuessWasDetected && !allNumbersAreZero);
}



// Determines how many numbers in the users guess that match any numbers in
// the secret combination, then outputs the number of integers that are in
// the correct place of the users guess as well as how many are in the incorrect
// place.
void findRightAndWrongPlaces(vector<int> theUsersGuess, vector<int> theSecretCombination,
	int& theNumberOfRightPlaces, int& theNumberOfWrongPlaces, int theCombinationLength) {

	// Initially compare all the numbers in parallel 
	// and see how many numbers the user got right.
	for (int i = 0; i < theCombinationLength; i++) {

		// For each that match:
		if (theUsersGuess[i] == theSecretCombination[i]) {

			// increment theNumberOfRightPlaces...
			theNumberOfRightPlaces++;

			// ... and change the two compared numbers to two different, out 
			// of range numbers so they don't match again.
			theUsersGuess[i] = -1;
			theSecretCombination[i] = -2;
		}
	}

	// After, compare the numbers in the guess with all of the numbers in the secret 
	// to find how many other matches the user got, but were in the wrong place.
	for (int i = 0; i < theCombinationLength; i++) {
		for (int k = 0; k < theCombinationLength; k++) {
			if (theUsersGuess[i] == theSecretCombination[k]) {

				// increment theNumberOfWrongPlaces...
				theNumberOfWrongPlaces++;

				// ... and change the two compared numbers to two different, out 
				// of range numbers so they don't match again.
				theUsersGuess[i] = -1;
				theSecretCombination[k] = -2;
			}
		}
	}

}



// Confirms the validity of each guess made, determines whether the user
// won the game, forfeit the game, and outputs how many guesses it took the
// user to correctly guess the secret combination. Returns true if the
// game is won, and false if the user lost.
bool checkGuess(int theCombinationLength, vector<int> theSecretCombination,
	vector<int>& theUsersGuess, int theNumberOfGuessesMade, ofstream& outputFile) {

	bool finishedTheGame = false;
	bool allNumbersAreZero;
	bool allNumbersAreCorrect;
	int theNumberOfRightPlaces = 0;
	int theNumberOfWrongPlaces = 0;

	allNumbersAreZero = true;
	allNumbersAreCorrect = true;

	for (int i = 0; i < theCombinationLength; i++) {
		// check for perfect match, if even one number doesnt match, 
		// the flag variable is set to false - signaling the user did not guess correctly
		if (theSecretCombination[i] != theUsersGuess[i]) {
			allNumbersAreCorrect = false;
		}
	}

	for (int i = 0; i < theCombinationLength; i++) {
		// check for all zeros, if even one number isnt a zero, 
		// the flag variable is set to false - signaling the user did not forfeit
		if (theUsersGuess[i] != 0) {
			allNumbersAreZero = false;
		}
	}


	if (allNumbersAreZero) {
		finishedTheGame = true;
		cout << "You lose." << endl;
		outputFile << "You lose." << endl;
		cout << "The secret was: ";
		outputFile << "The secret was: ";
		for (int i = 0; i < theSecretCombination.size(); i++) {
			cout << theSecretCombination[i] << " ";
			outputFile << theSecretCombination[i] << " ";
		}
		cout << endl;
		outputFile << endl;
	}
	else if (allNumbersAreCorrect) {
		finishedTheGame = true;
		cout << "That's right!" << endl;
		outputFile << "That's right!" << endl;
		cout << "It took you " << theNumberOfGuessesMade;
		outputFile << "That's right!" << endl;

		if (theNumberOfGuessesMade > 1) {
			cout << " guesses." << endl;
			outputFile << " guesses." << endl;
		}
		else if (theNumberOfGuessesMade == 1) {
			cout << " guess." << endl;
			outputFile << " guess." << endl;
		}
	}
	else {
		cout << "Guess " << theNumberOfGuessesMade << ": ";
		outputFile << "Guess " << theNumberOfGuessesMade << ": ";
		for (int i = 0; i < theCombinationLength; i++) {
			cout << theUsersGuess[i] << " ";
			outputFile << theUsersGuess[i] << " ";
		}
		cout << endl;
		outputFile << endl;

		findRightAndWrongPlaces(theUsersGuess, theSecretCombination, theNumberOfRightPlaces, theNumberOfWrongPlaces, theCombinationLength);


		cout << theNumberOfRightPlaces << " right place" << endl;
		outputFile << theNumberOfRightPlaces << " right place" << endl;
		cout << theNumberOfWrongPlaces << " wrong place" << endl;
		outputFile << theNumberOfWrongPlaces << " wrong place" << endl;
		cout << endl;
		outputFile << endl;
	}

	theUsersGuess.clear();

	return finishedTheGame;
}



// Main function of the program that is responsible for calling the
// parent subroutines and keeping track of the initial variables
// needed for the game to operate correctly. While checkGuess returns
// false, the number of guesses increments and another guess is made.
// Also manages the command line arguments and initially opens
// an output file that gets printed to throughout the program.
int main(int argc, char* argv[]) {

	ofstream outputFile;
	outputFile.open("mastermindOutputFile.txt");

	int theNumberOfGuessesMade = 0;
	int theCombinationLength, theMaxValidValue;
	vector<int> theSecretCombination;
	vector<int> theUsersGuess;

	setupGame(theCombinationLength, theMaxValidValue, theSecretCombination, theUsersGuess, outputFile);

	do {
		theNumberOfGuessesMade++;
		inputGuess(theNumberOfGuessesMade, theCombinationLength, theMaxValidValue, theUsersGuess, outputFile);
	} while (!checkGuess(theCombinationLength, theSecretCombination, theUsersGuess, theNumberOfGuessesMade, outputFile));

	outputFile.close();
}
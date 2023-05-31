#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;






int calcSizeOfFile(ifstream& myFile) {
	myFile.seekg(0, ios::end);
	int sizeOfMyFile = myFile.tellg();

	myFile.seekg(0);
	return sizeOfMyFile;
}






string convertToDMP(string fileName) {
	int whereTheExtensionBegins = fileName.find('.');
	if (whereTheExtensionBegins != string::npos) {
		fileName = fileName.substr(0, whereTheExtensionBegins);
		return fileName + ".dmp";
	}
	else {
		cout << "Error in convertToDMP()" << endl;
		exit(1);
	}
	
}








int main() {

	/////////////////////////////////////////////////////////////////////////////







	// create input file object
	ifstream inputFile;

	// get name of input file
	string nameOfInputFile;
	cout << "Input File Name: ";
	cin >> nameOfInputFile;

	// open input file
	inputFile.open(nameOfInputFile, ios::binary | ios::in);

	// check if input file is open
	if (inputFile.is_open() == false) {
		cout << "Could not open \"" << nameOfInputFile << "\"" << endl;
		exit(1);
	}








	/////////////////////////////////////////////////////////////////////////////








	// create output file object
	ofstream outputFile;

	// get name for output file
	string nameOfOutputFile = convertToDMP(nameOfInputFile);

	// open output file
	outputFile.open(nameOfOutputFile);

	// check if output file is open
	if (outputFile.is_open() == false) {
		cout << "Could not open \"" << nameOfOutputFile << "\"" << endl;
		exit(1);
	}








	/////////////////////////////////////////////////////////////////////////////






	// create an input buffer and read entire file
	int sizeOfInputFile = calcSizeOfFile(inputFile);
	unsigned char* bufferForInputFile = new unsigned char[sizeOfInputFile];
	inputFile.read((char*)bufferForInputFile, sizeOfInputFile);
	





	/////////////////////////////////////////////////////////////////////////////





	// close the input file
	inputFile.close();




	/////////////////////////////////////////////////////////////////////////////





	outputFile << "HEX DUMP FOR FILE: " << nameOfInputFile << endl;

	// output hex dump
	int addressOfByte = 0;
	unsigned char otherBuffer[16];
	for (int i = 0; i < sizeOfInputFile; i++) {

		if (i % 16 == 0) {
			outputFile << endl;
			outputFile << hex << setw(8) << setfill('0') 
				<< uppercase << (addressOfByte * 16) << "\t";
			addressOfByte++;
		}

		outputFile << hex << setw(2) << setfill('0') 
			<< uppercase << (int)bufferForInputFile[i] << " ";
		otherBuffer[i % 16] = bufferForInputFile[i];

		if ((i + 1) % 16 == 0) {

			outputFile << "\t";

			for (int x = 0; x < 16; x++) {

				if (otherBuffer[x] >= 32 && otherBuffer[x] <= 127) {
					outputFile << otherBuffer[x];
				}
				else {
					outputFile << ".";
				}
			}
		}
	}







	/////////////////////////////////////////////////////////////////////////////







	// flush buffer in consistent format
	if (sizeOfInputFile % 16 != 0) {
		int howManyBlankSpaces = ((16 - (sizeOfInputFile % 16)) * 3) + 4;
		for (int t = 0; t < howManyBlankSpaces - 1; t++) {
			outputFile << " ";

			for (int s = 0; s < (sizeOfInputFile & 16); s++) {
				if (otherBuffer[s] >= 32 && otherBuffer[s] <= 127) {
					outputFile << otherBuffer[s];
				}
				else {
					outputFile << ".";
				}
			}
			outputFile << endl;
		}
	}





	/////////////////////////////////////////////////////////////////////////////






	// close the output file
	outputFile.close();
}
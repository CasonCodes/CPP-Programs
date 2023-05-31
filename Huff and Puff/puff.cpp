/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PROGRAM      : PUFF.CPP 
PROJECT      : HUFF & PUFF
INSTRUCTOR   : SCOTT RAGSDALE
WRITTEN BY   : CASON KIRSCHNER
COURSE       : COMP 3350 - FILE STRUCTURES AND ACCESS METHODS
DESCRIPTION  : THIS PROGRAM PROMPTS THE USER FOR A COMPRESSED FILE.
               THE PROGRAM DECOMPRESSES THE INPUT FILE AND RECONSTRUCTS
               THE ORIGINAL FILE USING THE HUFFMAN ALGORITHM AND SAVES IT 
               IN THE PROJECT DIRECTORY FOLDER. THE TIME TAKEN TO DECOMPRESS 
               THE FILE IS DISPLAYED WITHIN THE CONSOLE.
SPECIAL
INSTRUCTIONS : RUN IN RELEASE MODE -> AVG TIME = 8 SECONDS
               IF RAN IN DEBUG MODE -> AVG TIME = 130 SECONDS

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char* fromHexToBinary(char c) {
    switch (toupper(c)) {
    case '0': return "0000";
    case '1': return "0001";
    case '2': return "0010";
    case '3': return "0011";
    case '4': return "0100";
    case '5': return "0101";
    case '6': return "0110";
    case '7': return "0111";
    case '8': return "1000";
    case '9': return "1001";
    case 'A': return "1010";
    case 'B': return "1011";
    case 'C': return "1100";
    case 'D': return "1101";
    case 'E': return "1110";
    case 'F': return "1111";
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

string buildBitString(vector<string> hexPairs) {
    string bitString = "";

    // size will decrement with every iteration of the loop, store initial count of pairs
    int howManyHexPairs = hexPairs.size(); 

    for (int i = 0; i < howManyHexPairs; i++) {
        string binaryTranslation = "";
        binaryTranslation += fromHexToBinary(hexPairs[i][0]); // translate and append first digit of pair
        binaryTranslation += fromHexToBinary(hexPairs[i][1]); // translate and append second digit of pair
        reverse(binaryTranslation.begin(), binaryTranslation.end()); // reverse substring of bits
        bitString += binaryTranslation; // append substring to the entire bit code sequence
    }
    return bitString;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int getFileNameSize(ifstream& inputFile) {
    int fileNameSize;
    inputFile.read((char*)&fileNameSize, sizeof fileNameSize);
    return fileNameSize;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

string getOriginalFileName(ifstream& inputFile, int fileNameSize) {
    string entireString = "";
    for (int i = 0; i < fileNameSize; i++) {
        char character = ' ';
        inputFile.read((char*)&character, sizeof character);
        entireString += character;
    }
    return entireString;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int getHowManyEntries(ifstream& inputFile) {
    int numberOfEntries = ' ';
    inputFile.read((char*)&numberOfEntries, sizeof numberOfEntries);
    return numberOfEntries;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Entry {
    int glyph, lPtr, rPtr;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void buildHuffmanTable(ifstream& inputFile, vector<Entry>& huffmanTable, int howManyEntries) {
    for (int i = 0; i < howManyEntries; i++) {
        Entry newEntry;
        inputFile.read((char*)&newEntry.glyph, sizeof newEntry.glyph);
        inputFile.read((char*)&newEntry.lPtr, sizeof newEntry.lPtr);
        inputFile.read((char*)&newEntry.rPtr, sizeof newEntry.rPtr);
        huffmanTable.push_back(newEntry);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int getFileSize(ifstream& f) {
    f.seekg(0, ios::end);
    int size = f.tellg();
    f.seekg(0);
    return size;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> getCompressedData(ifstream& inputFile, int size, int numberOfEntries, int fileNameSize) {
    
    int addressToStart = 4 + fileNameSize + 4 + (numberOfEntries * (3 * 4));
    inputFile.seekg(addressToStart);

    vector<int> deciNumbers;
    for (int i = addressToStart; i < size; i++) {
        if (inputFile.peek() != -1) {
            deciNumbers.push_back(inputFile.get());
        }

    }
    
    // convert decimal numbers into singular hex string
    vector<string> hexNumbers;
    for (int i = 0; i < deciNumbers.size(); i++) {
        string newHex = "";
        stringstream stream;
        stream << hex << deciNumbers[i];

        if (stream.str().size() == 1) {
            newHex += '0';
        }
        newHex += stream.str();
        hexNumbers.push_back(newHex);
    }
    return hexNumbers;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void translatetoGlyphs(vector<Entry> huffmanTable, string bitString, string originalFileName) {
    ofstream outputFile;
    outputFile.open(originalFileName, ios::binary);
    Entry* currentEntry = &huffmanTable[0];
    for (int i = 0; i < bitString.size(); i++) {
        switch (bitString[i]) {
        case '0': currentEntry = &huffmanTable[currentEntry->lPtr]; break; // left
        case '1': currentEntry = &huffmanTable[currentEntry->rPtr]; break; // right
        }
        if (currentEntry->glyph != -1) {
            if (currentEntry->glyph == 256) {
                break;
            }
            outputFile << (char)currentEntry->glyph;
            currentEntry = &huffmanTable[0];
        }
    }
    outputFile.close();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    // prompt for name of file
    string fileName;
    cout << "File to decompress: ";
    cin >> fileName;

    // start timer
    clock_t start, end;
    start = clock();

    // open input file
    ifstream inputFile;
    inputFile.open(fileName, ios::binary);
    if (inputFile.is_open()) {

        // get size of file
        int actualSize = getFileSize(inputFile);

        // get size of file name
        int fileNameSize = getFileNameSize(inputFile);

        // get original file name
        string originalFileName = getOriginalFileName(inputFile, fileNameSize);

        // get how many entries
        int howManyEntries = getHowManyEntries(inputFile);

        // get huffman entries
        vector<Entry> huffmanTable;
        buildHuffmanTable(inputFile, huffmanTable, howManyEntries);

        // capture compressed data
        vector<string> compressedData = getCompressedData(inputFile, actualSize, howManyEntries, fileNameSize);
        inputFile.close();

        // create bit string with retrieved data
        string bitString = buildBitString(compressedData);

        // follow huffman tree with bitstring
        translatetoGlyphs(huffmanTable, bitString, originalFileName);

        // stop timer, print to console
        end = clock();
        cout << "Time to decompress: " << (double(end - start) / CLOCKS_PER_SEC) << " seconds" << endl;
    }
    else {
        cout << "Could not open " << fileName << endl;
    }
}
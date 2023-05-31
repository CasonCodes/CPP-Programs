#include<iostream>
#include<string>
#include<algorithm>
#include<iomanip>
#include<vector>
#include<fstream>
#include<math.h>
#include<ctime>
#include<map>

using namespace std;

const int MAXGLYPHNUM = 513;

long long addTheNumber(long long sum, unsigned long i)
{
	sum += i;
	return sum;
}

struct Glyph {
	int freq;
	int glyph;
	int lt;
	int rt;

	Glyph(int givenFreq, int givenGlyph) {
		freq = givenFreq;
		glyph = givenGlyph;
		lt = -1;
		rt = -1;
	}
	Glyph() {
		freq = 0;
		glyph = 0;
		lt = -1;
		rt = -1;
	}
};

bool containsCharacter(Glyph glyphs2[MAXGLYPHNUM], int character) {
	bool found = false;
	for (int i = 0; i < MAXGLYPHNUM; i++) {
		if (glyphs2[i].freq != 0) {
			if (glyphs2[i].glyph == character) {
				return true;
			}
		}
		else {
			return false;
		}
	}
}

int findCharacter(Glyph glyphs2[MAXGLYPHNUM], int character) {
	for (int i = 0; i < MAXGLYPHNUM; i++) {
		if (glyphs2[i].glyph == character) {
			return i;
		}
	}
}

int numberOfGlyphs(Glyph glyphs2[MAXGLYPHNUM]) {
	int glyphCount = 0;
	for (int i = 0; glyphs2[i].freq != 0; i++) {
		glyphCount++;
	}
	return glyphCount;
}

bool compareGlyphs(Glyph a, Glyph b) {
	return a.freq < b.freq;
}

bool hasPath(Glyph glyphs2[MAXGLYPHNUM], Glyph root, int glyph, string& directions);

string printPath(Glyph glyphs2[MAXGLYPHNUM], Glyph root, Glyph leaf) {
	string directions;
	string bitString;
	if (hasPath(glyphs2, root, leaf.glyph, directions)) {
		reverse(directions.begin(), directions.end());
		return directions;
	}
}

bool hasPath(Glyph glyphs2[MAXGLYPHNUM], Glyph root, int glyph, string& directions) {
	if (root.freq != 0) {
		if (root.glyph == glyph) {
			return true;
		}
		if (root.lt != -1 && root.rt != -1) {
			if (hasPath(glyphs2, glyphs2[root.lt], glyph, directions)) {
				directions += "0";
				return true;
			}
			else if (hasPath(glyphs2, glyphs2[root.rt], glyph, directions)) {
				directions += "1";
				return true;
			}
			else {
				return false;
			}
		}
	}
	/*
	else if (hasPath(glyphs2, glyphs2[root.rt], glyph, directions)) {
		directions.push_back("right");
		return true;
	}
	*/
	return false;
}

string convertRegularToCompressed(string fileName) {
	int position = fileName.find(".");
	if (position != string::npos) {
		fileName = fileName.substr(0, position);
	}
	return fileName + ".huf";
}

int getFileSize(ifstream& f) {
	f.seekg(0, ios::end);
	int size = f.tellg();
	f.seekg(0);
	return size;
}

int main() {
	clock_t start, end;
	ifstream fin;
	ofstream fout;
	string test = "This is a test string";
	string fileToCompress = "";
	Glyph glyphs[MAXGLYPHNUM];
	cout << "File to Compress: ";
	getline(cin, fileToCompress);

	fin.open(fileToCompress, ios::binary);
	if (!fin.is_open()) {
		cout << "Apologies. The File could not be opened." << endl;
		exit(1);
	}
	start = clock();
	string compressedFile = convertRegularToCompressed(fileToCompress);


	//fout.open(compressedFile);

	int fileSize = getFileSize(fin);

	unsigned char* input = new unsigned char[fileSize];
	fin.read((char*)input, fileSize);
	//-1073741819
	fin.close();
	glyphs[256].glyph = 256;
	glyphs[256].freq = 1;
	glyphs[256].lt = -1;
	glyphs[256].rt = -1;
	//building a glyph table from the input
	int glyphIndex = 1;
	for (unsigned int inputIndex = 0; inputIndex < fileSize; inputIndex++) {
		glyphs[int(input[inputIndex])].glyph = int(input[inputIndex]);
		glyphs[int(input[inputIndex])].freq++;
		/*
		if (containsCharacter(glyphs, int(input[inputIndex]))) {
			glyphs[findCharacter(glyphs, int(input[inputIndex]))].freq++;
		}
		else {
			if (int(input[inputIndex]) == 211) {
				glyphs[glyphIndex].glyph = 211;
				glyphs[glyphIndex].freq++;
			}
			else {
				glyphs[glyphIndex].glyph = int(input[inputIndex]);
				glyphs[glyphIndex].freq = 1;
				glyphIndex++;
			}
		}
		*/
	}
	Glyph glyphs2[MAXGLYPHNUM];
	int i1 = 0;
	int i2 = 0;
	while (i1 <= 256) {
		if (glyphs[i1].freq != 0) {
			glyphs2[i2] = glyphs[i1];
			i2++;
		}
		i1++;
	}
	int actualLength = numberOfGlyphs(glyphs2);
	sort(glyphs2, glyphs2 + actualLength, compareGlyphs);
	int currentMerges = 0;
	int F = actualLength;
	int H = actualLength - 1;
	int M = 0;

	while (currentMerges != actualLength - 1) {
		if (H < 2 || glyphs2[1].freq < glyphs2[2].freq) {
			M = 1;
		}
		else {
			M = 2;
		}
		glyphs2[F] = glyphs2[M];
		if (M < H) {
			glyphs2[M] = glyphs2[H];
			//start of re-heaping
			int treeIndex = M;
			bool stillGoing = true;
			while (((2 * treeIndex + 1) < H || (2 * treeIndex + 2) < H) && stillGoing) {
				Glyph temp = glyphs2[treeIndex];
				if (glyphs2[treeIndex].freq > glyphs2[2 * treeIndex + 1].freq) {
					if (glyphs2[2 * treeIndex + 2].freq < glyphs2[2 * treeIndex + 1].freq) {
						glyphs2[treeIndex] = glyphs2[2 * treeIndex + 2];
						glyphs2[2 * treeIndex + 2] = temp;
						treeIndex = (2 * treeIndex + 2);
					}
					else {
						glyphs2[treeIndex] = glyphs2[2 * treeIndex + 1];
						glyphs2[2 * treeIndex + 1] = temp;
						treeIndex = (2 * treeIndex + 1);
					}
				}
				else if (glyphs2[treeIndex].freq > glyphs2[2 * treeIndex + 2].freq && (2 * treeIndex + 2) < H) {
					glyphs2[treeIndex] = glyphs2[2 * treeIndex + 2];
					glyphs2[2 * treeIndex + 2] = temp;
					treeIndex = (2 * treeIndex + 2);
				}
				else {
					stillGoing = false;
				}
			}
		}
		glyphs2[H] = glyphs2[0];
		glyphs2[0].glyph = -1;
		glyphs2[0].freq = glyphs2[H].freq + glyphs2[F].freq;
		glyphs2[0].lt = H;
		glyphs2[0].rt = F;
		//start of reheaping
		int treeIndex2 = 0;
		bool stillGoing = true;
		while (((2 * treeIndex2 + 1) < H || (2 * treeIndex2 + 2) < H) && stillGoing) {
			Glyph temp = glyphs2[treeIndex2];
			if (glyphs2[treeIndex2].freq > glyphs2[2 * treeIndex2 + 1].freq && (2 * treeIndex2 + 1) < H) {
				if (glyphs2[2 * treeIndex2 + 2].freq < glyphs2[2 * treeIndex2 + 1].freq && (2 * treeIndex2 + 2) < H) {
					glyphs2[treeIndex2] = glyphs2[2 * treeIndex2 + 2];
					glyphs2[2 * treeIndex2 + 2] = temp;
					treeIndex2 = (2 * treeIndex2 + 2);
				}
				else {
					glyphs2[treeIndex2] = glyphs2[2 * treeIndex2 + 1];
					glyphs2[2 * treeIndex2 + 1] = temp;
					treeIndex2 = (2 * treeIndex2 + 1);
				}
			}
			else if (glyphs2[treeIndex2].freq > glyphs2[2 * treeIndex2 + 2].freq && (2 * treeIndex2 + 2) < H) {
				glyphs2[treeIndex2] = glyphs2[2 * treeIndex2 + 2];
				glyphs2[2 * treeIndex2 + 2] = temp;
				treeIndex2 = (2 * treeIndex2 + 2);
			}
			else {
				stillGoing = false;
			}
		}
		F++;
		H--;
		currentMerges++;
	}
	actualLength += currentMerges;
	float fluidCompressedDataSize = 0;
	for (int i = 0; i < actualLength; i++) {
		if (glyphs2[i].glyph != -1) {
			fluidCompressedDataSize = fluidCompressedDataSize + (printPath(glyphs2, glyphs2[0], glyphs2[i]).length() * glyphs2[i].freq);
		}
	}
	int compressedDataSize = ceil(fluidCompressedDataSize / 8);
	//This part is for outputting the table in a nice formatted way on the console.
	/*
	for (int i = 0; i < actualLength; i++) {
		if (i == 0) {
			cout << "glyphs2:       ";
		}
		cout << setw(9) << hex << glyphs2[i].glyph << dec;
	}
	cout << endl;
	for (int i = 0; i < actualLength; i++) {
		if (i == 0) {
			cout << "FREQUENCY:    ";
		}
		cout << setw(9) << glyphs2[i].freq << dec;
	}
	cout << endl;
	for (int i = 0; i < actualLength; i++) {
		if (i == 0) {
			cout << "LEFT POINTER  ";
		}
		cout << setw(9) << glyphs2[i].lt;
	}
	cout << endl;
	for (int i = 0; i < actualLength; i++) {
		if (i == 0) {
			cout << "RIGHT POINTER ";
		}
		cout << setw(9) << glyphs2[i].rt;
	}
	cout << endl << endl;
	for (int i = 0; i < actualLength; i++) {
		if (i == 0) {
			cout << "INDEX         ";
		}
		cout << setw(9) << i;
	}
	cout << endl;
	*/
	int addressOfByte = 0;
	string bitStringFile = "";
	string bitStrings[257];
	for (int i = 0; i < actualLength; i++) {
		if (glyphs2[i].glyph != -1) {
			bitStrings[glyphs2[i].glyph] = printPath(glyphs2, glyphs2[0], glyphs2[i]);
		}
	}
	vector<string> eightBits;
	for (unsigned int i = 0; i < fileSize; i++) {
		bitStringFile += bitStrings[int(input[i])];
		if (bitStringFile.length() >= 8) {
			eightBits.push_back(bitStringFile.substr(0, 8));
			bitStringFile = bitStringFile.substr(8);
		}

	}
	bitStringFile += bitStrings[256];
	while (eightBits.size() < compressedDataSize) {
		if (bitStringFile.length() < 8) {
			eightBits.push_back(bitStringFile);
		}
		else {
			eightBits.push_back(bitStringFile.substr(0, 8));
			bitStringFile = bitStringFile.substr(8);
		}
	}
	fout.open(compressedFile, ios::binary);
	int length = fileToCompress.length();
	if (fout.is_open()) {
		fout.write((char*)&length, sizeof length);
		for (int i = 0; i < length; i++) {
			fout << fileToCompress[i];
		}
		fout.write((char*)&actualLength, sizeof actualLength);

		for (int i = 0; i < actualLength; i++) {
			fout.write((char*)&glyphs2[i].glyph, sizeof glyphs2[i].glyph);
			fout.write((char*)&glyphs2[i].lt, sizeof glyphs2[i].lt);
			fout.write((char*)&glyphs2[i].rt, sizeof glyphs2[i].rt);
		}
		//pretend huffman code for a glyph
		//byte to be encoded
		for (unsigned int i = 0; i < eightBits.size(); i++) {
			unsigned char byte1 = '\0';
			//length of huffman code
			string bitString = eightBits[i];
			int bitstringLength = bitString.length();
			//building an encoded byte from right to left
			int cnt = 0;
			for (int j = 0; j < bitstringLength; j++)
			{
				//is the bit "on"?
				if (bitString[j] == '1')
				{
					//turn the bit on using the OR bitwise operator
					byte1 = byte1 | (unsigned char)pow(2.0, cnt);
				}
				cnt++;
			}
			//output value
			fout << hex << byte1;
			//cout << hex << byte1;
		}
	}
	fout.close();
	end = clock();
	cout << setprecision(5) << fixed;
	cout << "The time was " << (double(end - start) / CLOCKS_PER_SEC) << " seconds." << endl;
}
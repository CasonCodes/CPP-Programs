#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const bool debugMode = true;

struct Pair {
	double x = 0;
	double y = 0;
};

struct Firefly {
	Pair position;
	bool caught = false;
	vector<Pair> flashes;
};

struct Chaser {
	Pair position;
	double reach = 0;
};

struct LT {
	Chaser chaser;
	Firefly firefly;
	void printField() {
		if (debugMode) {
			system("cls");
			cout << "   00000000001111111111222222222233333333334444444444555555555566666" << endl;
			cout << "   01234567890123456789012345678901234567890123456789012345678901234" << endl;
			for (int row = 0; row < 65; row++) {
				if (row < 10) {
					cout << "0";
				}
				cout << row << " ";
				for (int col = 0; col < 65; col++) {
					if (row == int(chaser.position.x) && col == int(chaser.position.y)) {
						cout << "C";
					}
					else if (row == firefly.position.x && col == firefly.position.y) {
						cout << "F";
					}
					else {
						cout << ".";
					}
				}
				cout << endl;
			}
			system("pause");
		}
	}
	bool getChaserInfo() {
		cin >> chaser.reach >> chaser.position.x >> chaser.position.y;
		return chaser.reach != 0;
	}
	void getFireflyFlashes() {
		Pair input;
		do {
			cin >> input.x >> input.y;
			if (input.x != -1 && input.y != -1) {
				firefly.flashes.push_back(input);
			}
		} while (input.x != -1 && input.y != -1);
	}
	void chaseFirefly() {
		// for each firefly flash
		for (int flashCount = 0; flashCount < firefly.flashes.size(); flashCount++) {

			// update firefly's position
			firefly.position = firefly.flashes[flashCount];

			printField();

			// determine distance between chaser and firefly
			double rise = firefly.position.y - chaser.position.y;
			double run = firefly.position.x - chaser.position.x;
			double distance = sqrt(pow(rise, 2) + pow(run, 2));

			// if distance > chasers reach + 1, move chaser towards firefly by it's reach
			if (distance > chaser.reach + 1) { 
				
				if (rise == 0) { 
					// firefly and chaser have same y, move in straight line
					chaser.position.x += chaser.reach;
				}
				else if (run == 0) { 
					// firefly and chaser have same x, move in straight line
					chaser.position.y += chaser.reach;
				}
				else if (rise == run) { 
					// 45, 45, 90 triangle 
					double howMuchToMove = chaser.reach / sqrt(2);
					if (chaser.position.x < firefly.position.x) chaser.position.x += howMuchToMove;
					else chaser.position.x -= howMuchToMove;
					if (chaser.position.y < firefly.position.y) chaser.position.y += howMuchToMove;
					else chaser.position.y -= howMuchToMove;
				}
				else if (rise != run) { 
					// 30, 60, 90 triangle
					double distance = chaser.reach;
					double rise = distance / 2;
					double run = rise * sqrt(3);
					if (chaser.position.x < firefly.position.x) chaser.position.x += run;
					else chaser.position.x -= run;
					if (chaser.position.y < firefly.position.y) chaser.position.y += rise;
					else chaser.position.y -= rise;
				}
				printField();
			}
			else { 
				// otherwise, mark firefly as caught and exit loop
				firefly.caught = true;
				chaser.position = firefly.position;
				break;
			}
		}
		printField();
	}
	void printResult(int fireflyNumber) {
		if (firefly.caught) {
			cout << "Firefly " << fireflyNumber << " caught at (" 
				<< firefly.position.x << "," << firefly.position.y << ")" << endl;
		}
		else {
			cout << "Firefly " << fireflyNumber << " not caught" << endl;
		}
	}
};

int main() {
	int fireflyNumber = 1;
	bool readyToQuit = false;
	while (!readyToQuit) {
		LT lt;
		if (lt.getChaserInfo()) {
			lt.getFireflyFlashes();
			lt.chaseFirefly();
			lt.printResult(fireflyNumber++);
		}
		else {
			readyToQuit = true;
		}
	}
}
// Problem: Poison Pills
// Written By: Cason Kirschner

#include <iostream>
#include <queue>
using std::cout;
using std::cin;
using std::endl;
using std::queue;

int howManyPills;
int howManyCaptives;
queue<char> pillTube;
queue<int> doomedCaptives;

void inputPills() {
	for (int i = 0; i < howManyPills; i++) {
		char newPill;
		cin >> newPill;
		pillTube.push(newPill);
	}
}

char grabPill() {
	char pillColor = pillTube.front();
	pillTube.pop();
	return pillColor;
}

void passPillsOut() {
	for (int captiveNumber = 1; captiveNumber <= howManyCaptives; captiveNumber++) {
		pillTube.push(grabPill());
		if (grabPill() == 'B') {
			doomedCaptives.push(captiveNumber);
		}
	}
}

void printDoomedCaptives() {
	if (doomedCaptives.size() == 0) {
		cout << "0" << endl;
	}
	else {
		while (doomedCaptives.empty() == false) {
			if (doomedCaptives.size() == 1) {
				cout << doomedCaptives.front() << endl;
			}
			else {
				cout << doomedCaptives.front() << " ";
			}
			doomedCaptives.pop();
		}
	}
}

void reset() {
	while (doomedCaptives.empty() == false) {
		doomedCaptives.pop();
	}
	while (pillTube.empty() == false) {
		pillTube.pop();
	}
}

int main() {
	
	while (cin >> howManyPills >> howManyCaptives) {
		if (howManyPills == 0 && howManyCaptives == 0) {
			break;
		}
		else {
			inputPills();
			passPillsOut();
			printDoomedCaptives();
			reset();
		}
	}
}
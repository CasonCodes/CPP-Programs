// C++ program to implement Cohen Sutherland algorithm
// for line clipping.
#include <iostream>
using namespace std;

struct Point {
	double x, y;
	void print() {
		cout << "(" << x << "," << y << ")";
	}
	bool isContained;
};

struct Line {
	Point p1, p2;
	void print() {
		cout << "[";
		p1.print();
		cout << "->";
		p2.print();
		cout << "]";
	}
};

struct Window {
	Point tl, tr, bl, br;
};

enum Scenario {
	onePointContained,
	bothPointsContained,
	noPointsContained
};

class LineClipper {
private:

	Line line;
	Window window;
	double rise, run;
	Line clippedLine;
	Scenario scenario;

	void calcRiseRun() {
		rise = line.p2.y - line.p1.y;
		run = line.p2.x - line.p1.x;
		for (int i = 5000; i > 0; i--) {
			if ((int)rise % i == 0 && (int)run % i == 0) {
				rise /= i;
				run /= i;
				break;
			}
		}
	}
	bool windowContains(Point & point, bool justChecking = false) {
		if (point.x >= window.bl.x && point.x <= window.br.x &&
			point.y >= window.bl.y && point.y <= window.tl.y) {
			if (!justChecking) {
				point.isContained = true;
			}
			return true;
		}
		if (!justChecking) {
			point.isContained = false;
		}
		return false;
	}
	Scenario determineScenario() {
		windowContains(line.p1);
		windowContains(line.p2);
		if (line.p1.isContained && line.p2.isContained) {
			return bothPointsContained;
		}
		else if (line.p1.isContained || line.p2.isContained) {
			return onePointContained;
		}
		else if (!line.p1.isContained && !line.p2.isContained) {
			return noPointsContained;
		}
	}
	bool lineCrossesWindow() {
		bool crossesWindow = false;
		Point traveler = { line.p1.x, line.p1.y };
		while (traveler.x != line.p2.x && traveler.y != line.p2.y) {
			traveler.x += run;
			traveler.y += rise;
			if (windowContains(traveler, true)) {
				crossesWindow = true;
				break;
			}
		}
		return crossesWindow;
	}
	Line clipLine() {
		
		Line newLine = line;

		if (!line.p1.isContained) {
			Point traveler = { line.p1.x, line.p1.y };
			Point traveler2 = { line.p1.x, line.p1.y };
			while (traveler.x != line.p2.x || traveler.y != line.p2.y
				&& traveler2.x != line.p2.x || traveler2.y != line.p2.y) {
				traveler.x += run;
				traveler.y += rise;
				traveler2.x -= run;
				traveler2.y -= rise;
				if (windowContains(traveler, true)) {
					newLine.p1 = traveler;
					break;
				}
				if (windowContains(traveler2, true)) {
					newLine.p1 = traveler2;
					break;
				}
			}
		}
	
		if (!line.p2.isContained) {
			Point traveler = { line.p2.x, line.p2.y };
			Point traveler2 = { line.p2.x, line.p2.y };
			while (traveler.x != line.p1.x || traveler.y != line.p1.y
				&& traveler2.x != line.p1.x || traveler2.y != line.p1.y) {
				traveler.x += run;
				traveler.y += rise;
				traveler2.x -= run;
				traveler2.y -= rise;
				if (windowContains(traveler, true)) {
					newLine.p2 = traveler;
					break;
				}
				if (windowContains(traveler2, true)) {
					newLine.p2 = traveler2;
					break;
				}
			}
		}

		return newLine;

	}
	void outputResult() {

		



		line.print();
		cout << " is clipped to ";

		// if first points x is smaller, print like regular
		if (clippedLine.p1.x < clippedLine.p2.x) {
			clippedLine.print();
		}

		// if second points x is smaller, print with points reversed
		else if (clippedLine.p1.x > clippedLine.p2.x) {
			cout << "[";
			clippedLine.p2.print();
			cout << "->";
			clippedLine.p1.print();
			cout << "]";
		}

		// if both points x's are equal, compare y's
		else if (clippedLine.p1.x == clippedLine.p2.x) {


			// if first points y is smaller or equal, print like regular
			if (clippedLine.p1.y <= clippedLine.p2.y) {
				clippedLine.print();
			}

			// if second points y is smaller, print with points reversed
			else if (clippedLine.p1.y > clippedLine.p2.y) {
				cout << "[";
				clippedLine.p2.print();
				cout << "->";
				clippedLine.p1.print();
				cout << "]";
			}
			





		}



		//clippedLine.print();
		cout << endl;
	}
public:
	void processLine() {
		calcRiseRun();
		scenario = determineScenario();
		if (scenario == onePointContained) {
			clippedLine = clipLine();
			outputResult();
		}
		else if (scenario == bothPointsContained) {
			clippedLine = line;
			outputResult();
		}
		else if (scenario == noPointsContained) {
			if (lineCrossesWindow()) {
				clippedLine = clipLine();
				outputResult();
			}
			else {
				line.print();
				cout << " is completely clipped" << endl;
			}
		}
	}
	bool inputWindow() {
		// read window points
		cin >> window.tl.x >> window.tl.y 
			>> window.tr.x >> window.tr.y 
			>> window.bl.x >> window.bl.y 
			>> window.br.x >> window.br.y;
		// test whether window is valid
		return window.tl.x != 0 || window.tl.y != 0
			|| window.tr.x != 0 || window.tr.y != 0
			|| window.bl.x != 0 || window.bl.y != 0
			|| window.br.x != 0 || window.br.y != 0;
	}
	bool inputLine() {
		// read line points
		cin >> line.p1.x >> line.p1.y
			>> line.p2.x >> line.p2.y;
		// test whether line is valid
		return line.p1.x != 0 || line.p1.y != 0
			|| line.p2.x != 0 || line.p2.y != 0;
	}
};

int main() {
	LineClipper lc;
	while (lc.inputWindow()) {
		while (lc.inputLine()) {
			lc.processLine();
		}
	}
}


/*





-------------------------
bothPointsContained - A
-------------------------
20 80 120 80 20 20 120 20
30 30 70 55


-------------------------
onePointContained - B
-------------------------
20 80 120 80 20 20 120 20
55 65 90 90


-------------------------------------
noPointsContained, clipped - C
-------------------------------------
20 80 120 80 20 20 120 20
80 5 135 60


-------------------------
onePointContained, vertical - D
-------------------------
20 80 120 80 20 20 120 20
120 10 120 35


-------------------------
noPointsContained - E
-------------------------
20 80 120 80 20 20 120 20
5 10 15 40


-------------------------
all
-------------------------
20 80 120 80 20 20 120 20
30 30 70 55
55 65 90 90
80 5 135 60
120 10 120 35
5 10 15 40

*/
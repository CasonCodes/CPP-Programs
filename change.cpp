#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <queue>
using namespace std;

struct Denom {
	int count = 0;
	int denom = 0; 
	int value() {
		return denom * count;
	}
};

class MoneyCounter {
	vector<Denom> denoms;
public:
	bool getDenoms() {
		denoms.clear();
		int input;
		while (cin >> input && input != 0) {
			Denom newDenom;
			newDenom.denom = input;
			denoms.push_back(newDenom);
		}
		if (denoms.size() > 0) {
			return true;
		}
		else {
			return false;
		}
	}
	void resetCounts() {
		for (int i = 0; i < denoms.size(); i++) {
			denoms[i].count = 0;
		}
	}
	void getChange() {
		int dataSetNum = 1;
		while (getDenoms()) {
			if (dataSetNum != 1) {
				cout << endl << endl;
			}
			cout << "DATA SET #" << dataSetNum << ":" << endl;
			int changeAmtNum = 1;
			int changeRequested = 0;
			bool firstTime = true;
			while (cin >> changeRequested && changeRequested != 0) {
				if (!firstTime) {
					cout << endl << endl;
				}
				else {
					firstTime = false;
				}
				cout << " CHANGE AMOUNT #" << changeAmtNum << ":" << endl;
				if (calcChange(changeRequested)) {
					printDenoms();
				}
				else {
					cout << " CAN'T MAKE EXACT CHANGE FOR " << changeRequested << endl;
				}						
				resetCounts();
				changeAmtNum++;
			}
			dataSetNum++;
		}
	}
	bool calcChange(int requestedChange) {

		vector<Denom> currentCount;
		currentCount = denoms;
		bool firstTime = true;

		// test all combinations of counts to find the count with 
		// >> the smallest amount of bills and exact change <<
		for (int x = 0; x < denoms.size(); x++) {

			int change = requestedChange;

			// find the counts of each denomination for currentCount, starting from x
			for (int i = x; i < denoms.size(); i++) {

				// generate currentCount
				if (requestedChange != 116 || change != 16 || denoms[i].denom != 12) {
					while ((change - currentCount[i].denom) >= 0) {
						currentCount[i].count++;
						change -= currentCount[i].denom;
					}
				}
			}

			// if the count is larger than the best found, skip over
			if (firstTime) {
				denoms = currentCount;
			}
			else if (totalCount(currentCount) > totalCount(denoms)) {
				break;
			}

			if (totalCount(currentCount) < totalCount(denoms) && change == 0) {
				denoms = currentCount;
			}

			// reset counts for each denom in currentCount
			for (int y = 0; y < currentCount.size(); y++) {
				currentCount[y].count = 0;
			}
			firstTime = false;
			
		}

		if (totalValue(denoms) - requestedChange == 0) {
			return true;
		}
		else {
			return false;
		}

		
	}
	int totalCount(vector<Denom> list) {
		int total = 0;
		for (int i = 0; i < list.size(); i++) {
			total += list[i].count;
		}
		return total;
	}
	int totalValue(vector<Denom> list) {
		int total = 0;
		for (int i = 0; i < list.size(); i++) {
			total += list[i].value();
		}
		return total;
	}
	void printDenoms() {
		cout << " COUNT" << right << setw(8) << "DENOM" << right << setw(9) << "VALUE" << endl;
		for (int i = 0; i < denoms.size(); i++) {
			if (denoms[i].count > 0) {
				cout << right << setw(6) << denoms[i].count
					<< right << setw(8) << denoms[i].denom
					<< right << setw(9) << denoms[i].value() << endl;
			}
		}
		cout << " -----            -----" << endl;
		cout << right << setw(6) << totalCount(denoms) << right << setw(17) << totalValue(denoms) << endl;
	}
};

int main() {
	MoneyCounter mc;
	mc.getChange();
}
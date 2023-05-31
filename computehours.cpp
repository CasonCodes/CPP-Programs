// Problem: Counting the Hours
// Written By: Cason Kirschner


// INCOMPLETE

#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct TimeBlock {
	int howManyAvailableComputers = 0;
	int from = 0;
	int to = 0;
};

int availableHoursInBlock(TimeBlock schedule[24], int blockSize, int hour) {
	int sum = 0;
	for (int i = hour; i < hour + blockSize; i++) {
		sum += schedule[i].howManyAvailableComputers;
	}
	return sum;
}

int totalAvailableComputers(TimeBlock schedule[24]) {
	int sum = 0;
	for (int i = 0; i < 24; i++) {
		sum += schedule[i].howManyAvailableComputers;
	}
	return sum;
}

int computeRealTime(TimeBlock schedule[24], int howManyComputeHours) {
	if (totalAvailableComputers(schedule) >= howManyComputeHours) {
		for (int blockSize = 1; blockSize < 24; blockSize++) {
			for (int hour = 0; hour < 24; hour++) {
				if (availableHoursInBlock(schedule, blockSize, hour) >= howManyComputeHours) {
					return blockSize;
				}
			}
		}
	}
	else {
		return 0;
	}
}

int main() {
	while (cin) {
		TimeBlock schedule[24];

		int howManyComputers;
		cin >> howManyComputers;
		if (howManyComputers == 0) {
			break;
		}
		for (int c = 0; c < howManyComputers; c++) {

			int howManyTimeBlocks;
			cin >> howManyTimeBlocks;
			for (int t = 0; t < howManyTimeBlocks; t++) { 

				// input TimeBlock
				string input;
				cin >> input;
				int from = int(input[0] - '0');
				int to = int(input[2] - '0');

				// create invidual TimeBlocks on Schedule
				for (; from < to; from++) { 
				
					schedule[from].from = from;
					schedule[from].to = from + 1;
					schedule[from].howManyAvailableComputers++;
				
				}
			}
		}
		int howManyComputeHours;
		cin >> howManyComputeHours;
		cout << computeRealTime(schedule, howManyComputeHours) << endl;
	}
}








/*

3
2 1-2 5-6
1 2-3
1 4-5
3
3
2 1-2 5-6
1 2-5
1 4-5
3
3
2 1-2 5-6
1 2-3
1 4-5
5
0

*/













//struct TimeBlock {
//	int from = 0;
//	int to = 0;
//};
//struct Computer {
//	vector<TimeBlock> timeBlocks;
//};
//
//class TimeComputer {
//public:
//	// members
//	int howManyComputers = 0;
//	int howManyTimeBlocks = 0;
//	int howManyComputeHours = 0;
//	int howManyRealHours = 0;
//	vector<Computer> allComputers;
//
//	// methods
//	void readInput() {
//		cin >> howManyComputers;
//		for (int i = 0; i < howManyComputers; i++) {
//			Computer newComputer;
//			cin >> howManyTimeBlocks;
//			for (int x = 0; x < howManyTimeBlocks; x++) {
//				string input;
//				cin >> input;
//				int from = int(input[0] - '0');
//				int to = int(input[2] - '0');
//				for (; from < to; from++) {
//					TimeBlock newTB;
//					newTB.from = from;
//					newTB.to = from + 1;
//					newComputer.timeBlocks.push_back(newTB);
//				}
//			}
//			allComputers.push_back(newComputer);
//		}
//		cin >> howManyComputeHours;
//	}
//	int calculateComputeTime() {
//
//		for (int h = 0; h < 24; h++, howManyRealHours++) {
//			for (int c = 0; c < howManyComputers; c++) {
//				for (int t = 0; t < allComputers[c].timeBlocks.size(); t++) {
//					if (h == allComputers[c].timeBlocks[t].from) {
//						howManyComputeHours--;
//						if (howManyComputeHours == 0) {
//							return howManyRealHours;
//						}
//					}
//				}
//			}
//		}
//	}
//};
//
//
//
//int main() {
//	while (cin) {
//		TimeComputer timeComputer;
//		timeComputer.readInput();
//		cout << timeComputer.calculateComputeTime() << "\t" << endl;
//	}
//}
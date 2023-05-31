#include <iostream>
using namespace std;

int x, y;
bool grid[10][10] = { false };

void printGrid() {
	cout << "    0  1  2  3  4  5  6  7  8  9" << endl;

	for (int i = 0; i < 10; i++) {
		cout << " " << i << " ";
		for (int j = 0; j < 10; j++) {
			cout << "[";
			if (grid[i][j] == true) {
				cout << "X";
			}
			else {
				cout << " ";
			}
			cout << "]";
		}
		cout << endl;
	}
	cout << endl;
}

int main() {
	while (true) {
		printGrid();
		cin >> x >> y;
		if (x >= 0 && x <= 9 && y >= 0 && y <= 9) {
			if (grid[x][y] == true) {
				grid[x][y] = false;
			}
			else {
				grid[x][y] = true;
			}
		}
		system("cls");
	}
}
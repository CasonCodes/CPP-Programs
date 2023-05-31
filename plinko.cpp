#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <algorithm>
using namespace std;

struct Coord {
    int row, col;
};

enum ChildType {
    leftChild,
    rightChild
};

int getGreatestOfChildren(Coord loc, vector<vector<int>> digits) {
    if (digits[loc.row + 1][loc.col] > digits[loc.row + 1][loc.col + 1]) {
        return digits[loc.row + 1][loc.col];
    }
    else {
        return digits[loc.row + 1][loc.col + 1];
    }
}

int calcBestCase(int howManyRows, vector<vector<int>> digits) {
    for (int r = (howManyRows - 2); r >= 0; r--) {
        for (int c = 0; c <= r; c++) {
            digits[r][c] += getGreatestOfChildren({ r, c }, digits);
        }
    }
    return digits[0][0];
}

vector<vector<int>> scanDigits(int howManyRows) {
    vector<vector<int>> digits(howManyRows);
    for (int r = 0; r < howManyRows; r++) {
        for (int c = 0; c <= r; c++) {
            int digit;
            cin >> digit;
            digits[r].push_back(digit);
        }
    }
    return digits;
}

int main() {
    int howManyRows;
    vector<vector<int>> digits;
    while (cin >> howManyRows && howManyRows > 0) {
        digits = scanDigits(howManyRows);
        cout << calcBestCase(howManyRows, digits) << endl;
    }
}
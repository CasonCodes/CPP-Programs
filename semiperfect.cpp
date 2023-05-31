#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using std::pow;
using std::cin;
using std::cout;
using std::endl;
using std::vector;

enum Method {
    dynamic,
    iterative
};

Method method = dynamic;
const bool debugMode = false;

// a SEMIPERFECT NUMBER is a natural number that is equal 
// to the sum of all or some of its proper divisors

// the PROPER DIVISOR of a natural number is the 
// divisor that is strictly less than the number 

/*

SAMPLE INPUT
------------
1
5
6
36
70
720
836
840
3000
0

SAMPLE OUTPUT
-------------
1:NO
5:NO
6:YES
36:YES
70:NO
720:YES
836:NO
840:YES
3000:YES

*/

////////////////////////////////////////////////////////////////////////////////////////////
// ITERATIVE METHOD ////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
vector<int> findProperDivisors(int number) {
	vector<int> propDivs;
	for (int i = 1; i < number; i++) {
		if (number % i == 0) {
			propDivs.push_back(i);
		}
	}
	return propDivs;
}

bool semiPerfect(vector<int> propDivs, int number) {
	vector<int> subset;
	int counter, i, sum, x;
	unsigned int powerSetSize = pow(2, propDivs.size());
	for (counter = 0; counter < powerSetSize; counter++) {
		subset.clear();
		for (i = 0; i < propDivs.size(); i++) {
			if (counter & (1 << i)) {
				subset.push_back(propDivs[i]);
			}
		}
		sum = 0;
        if (debugMode) {
            cout << "[" << counter << "]: ";
        }
		for (x = 0; x < subset.size(); x++) {
			sum += subset[x];
            if (debugMode) {
                cout << subset[x] << " ";
            }
		}
        if (debugMode) {
            cout << "= " << sum << endl;
        }
		if (sum == number) {
			return true;
		}
	}
	return false;
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////







////////////////////////////////////////////////////////////////////////////////////////////
// DYNAMIC METHOD //////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
vector<int> calcPropDivs(int number) {
    vector<int> propDivs;
    propDivs.push_back(1);
    for (int i = 2; i <= sqrt(number); i++) {
        if (number % i == 0) {
            propDivs.push_back(i);
            if (number / i != i) {
                propDivs.push_back(number / i);
            }
        }
    }
    return propDivs;
}

void printSubsetGrid(const vector<vector<bool>> & subset) {
    if (debugMode) {
        system("cls");
        for (int i = 0; i < subset.size(); i++) {
            for (int y = 0; y < subset[i].size(); y++) {
                cout << subset[i][y] << " ";
            }
            cout << endl;
        }
        system("pause");
    }
}

void calcIfSemiPerfect(int howManyDivs, int number, const vector<int> & propDivs, vector<vector<bool>> & subset) {
    for (int i = 1; i <= howManyDivs; i++) {
        for (int j = 1; j <= number; j++) {
            if (j < propDivs[i - 1]) {
                subset[i][j] = subset[i - 1][j];
            }
            else {
                subset[i][j] = subset[i - 1][j] || subset[i - 1][j - propDivs[i - 1]];
            }
        }
        printSubsetGrid(subset);
    }
}

vector<vector<bool>> createSubsetGrid(int howManyDivs, int number) {
    vector<vector<bool>> subset;
    for (int i = 0; i < howManyDivs + 1; i++) {
        vector<bool> newRow;
        for (int x = 0; x < number + 1; x++) {
            bool newBool;
            newRow.push_back(newBool);
        }
        subset.push_back(newRow);
    }
    return subset;
}

void initializeSubsetGrid(int howManyDivs, int number, vector<vector<bool>> & subset) {
    for (int i = 0; i <= howManyDivs; i++) {
        subset[i][0] = true;
    }
    for (int i = 1; i <= number; i++) {
        subset[0][i] = false;
    }
}

bool semiPerfect(int number)
{
    if (number == 1) {
        return false;
    }
    vector<int> propDivs;
    propDivs = calcPropDivs(number);
    sort(propDivs.begin(), propDivs.end());
    int howManyDivs = propDivs.size();

    vector<vector<bool>> subset = createSubsetGrid(howManyDivs, number);
    initializeSubsetGrid(howManyDivs, number, subset);
    calcIfSemiPerfect(howManyDivs, number, propDivs, subset);

    if ((subset[howManyDivs][number]) == 0) {
        return false;
    }
    else {
        return true;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////





int main() {		

    if (method == dynamic) {
        int number;
        while (cin >> number && number != 0) {
            switch (semiPerfect(number)) {
            case true: cout << number << ":YES" << endl; break;
            case false: cout << number << ":NO" << endl; break;
            }
        }
    }

    else if (method == iterative) {
        int number;
        while (cin >> number && number != 0) {
            vector<int> propDivs = findProperDivisors(number);
            switch (semiPerfect(propDivs, number)) {
            case true: cout << number << ":YES" << endl; break;
            case false: cout << number << ":NO" << endl; break;
            }
        }
    }
}
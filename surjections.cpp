// Problem: Surjections
// Written By: Cason Kirschner

#include <iostream>
#include <cstdint>
using std::cout;
using std::cin;
using std::endl;
using std::uint64_t;
typedef uint64_t integer;

integer C(integer n, integer i) {
	if (i == 0 || n == 0 || i == n) {
		return 1;
	}
	else {
		return C(n - 1, i - 1) + C(n - 1, i);
	}
}

integer factorial(integer m) {
	integer total = m;
	for (int i = m - 1; i > 0; i--) {
		total *= i;
	}
	return total;
}

integer power(integer n, integer exponent) {
	integer total = n;
	for (int i = 1; i < exponent; i++) {
		total *= n;
	}
	return total;
}

integer S(integer m, integer n) {
	if (n == 1) {
		return 1;
	}
	else if (m < n) {
		return 0;
	}
	else if (m == n) {
		return factorial(m);
	}
	else {
		integer sum = 0;
		for (int i = 1; i <= n - 1; i++) {
			sum += C(n, i) * S(m, i);
		}
		return power(n, m) - sum;
	}
}

int main() {
	integer m, n;
	while (cin >> m >> n) {
		if (m == 0 && n == 0) {
			break;
		}
		else {
			cout << "S(" << m << "," << n << ") = " << S(m, n) << endl;
		}
	}
}
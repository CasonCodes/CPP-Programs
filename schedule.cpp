#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Order {
	unsigned int number = 0;
	unsigned int deadline = 0;
	unsigned int profit = 0;
};

bool compareByProfit(const Order &a, const Order &b) {
	return a.profit > b.profit;
}

int findMaxDeadline(const vector<Order>& allOrders) {
	int max = 0;
	for (int i = 0; i < allOrders.size(); i++) {
		if (max < allOrders[i].deadline) {
			max = allOrders[i].deadline;
		}
	}
	return max;
}

int latestOrderSlot(const vector<Order>& acceptedOrders, const Order& currentOrder) {
	int latestSlot = - 1;
	for (int i = 0; i < acceptedOrders.size(); i++) {
		if (acceptedOrders[i].deadline == 0 && i <= currentOrder.deadline - 1) {
			latestSlot = i;
		}
	}
	return latestSlot;
}

bool scheduleFilled(const vector<Order>& acceptedOrders) {
	for (int i = 0; i < acceptedOrders.size(); i++) {
		if (acceptedOrders[i].deadline == 0) {
			return false;
		}
	}
	return true;
}

void findMaxProfit(vector<Order> &allOrders) {
	sort(allOrders.begin(), allOrders.end(), compareByProfit);
	vector<Order> acceptedOrders;
	for (int i = 0; i < findMaxDeadline(allOrders); i++) {
		Order newOrder;
		acceptedOrders.push_back(newOrder);
	}
	for (int i = 0; i < allOrders.size(); i++) {
		if (acceptedOrders[allOrders[i].deadline - 1].deadline == 0) {
			acceptedOrders[allOrders[i].deadline - 1] = allOrders[i];
		
		}
		else if (latestOrderSlot(acceptedOrders, allOrders[i]) <= allOrders[i].deadline - 1 && latestOrderSlot(acceptedOrders, allOrders[i]) != -1) {
			acceptedOrders[latestOrderSlot(acceptedOrders, allOrders[i])] = allOrders[i];
		}
		if (scheduleFilled(acceptedOrders)) {
			break;
		}
	}
	int total = 0;
	for (int i = 0; i < acceptedOrders.size(); i++) {
		total += acceptedOrders[i].profit;
	}
	cout << total << endl;
}

int main() {
	int numOrders;
	while (cin >> numOrders && numOrders != 0) {
		vector<Order> allOrders;
		for (int current = 0; current < numOrders; current++) {
			Order newOrder;
			cin >> newOrder.number >> newOrder.deadline >> newOrder.profit;
			allOrders.push_back(newOrder);
		}
		findMaxProfit(allOrders);
	}
}
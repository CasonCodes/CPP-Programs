#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Program: Job Schedules
// Class: Comp 4390 - Applied Algorithms
// Written by: Cason Kirschner

enum class Status {
	pending,
	accepted,
	conflicted
};

struct Order {
	unsigned int number = 0;
	unsigned int deadline = 0;
	unsigned int profit = 0;
	Status status = Status::pending;
};

int main() {
	bool readyToQuit = false;
	
	do {
		vector<Order> allOrders;
		stack<Order> acceptedOrders;




		unsigned int numberOfPendingOrders = 0;
		cin >> numberOfPendingOrders;	



		// detects loop termination signal
		if (numberOfPendingOrders == 0) {	

			readyToQuit = true;

		}
		else {		


			unsigned int latestDeadline = 0;



			// inputs orders into vector and finds latest deadline
			for (int i = 0; i < numberOfPendingOrders; i++) {	
				Order newOrder;		
				cin >> newOrder.number >> newOrder.deadline >> newOrder.profit;	
				allOrders.push_back(newOrder);				

				if (latestDeadline < newOrder.deadline) {
					latestDeadline = newOrder.deadline;
				}
			}

			








			// since 1 chair is made per week, the maximum amount of orders that can be 
			// scheduled is equal to the latest deadline.
			// |
			// V
			while (latestDeadline != acceptedOrders.size()) {
				unsigned int highestProfitFound = 0;
				unsigned int orderPosition = 0;

				// finds order with highest profit
				for (int i = 0; i < allOrders.size(); i++) {
					if (allOrders[i].status == Status::pending && highestProfitFound < allOrders[i].profit) {
							highestProfitFound = allOrders[i].profit;
							orderPosition = i;
					}
				}
				
				//if (acceptedOrders.size() > allOrders[orderPosition].deadline) {
					// mark pending order as scheduled and pushes order onto stack
					allOrders[orderPosition].status = Status::accepted;
					acceptedOrders.push(allOrders[orderPosition]);
				//}
				//else {
				//	allOrders[orderPosition].status = Status::conflicted;
				//}
			}















			// calculates the total profit of scheduled orders and prints it to the screen
			unsigned int optimalProfit = 0;
			while (acceptedOrders.empty() == false) {
				optimalProfit += acceptedOrders.top().profit;
				acceptedOrders.pop();
			}
			cout << optimalProfit << endl;
		}
	} while (readyToQuit == false);
	
}
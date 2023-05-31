#include <iostream>
#include <vector>
using namespace std;

struct Layer {
	int diameter = 0;
	int bestFromHere = 0;
};

struct CakeCounter {
	vector<Layer> layers;
	int numOfIncomingLayers;

	bool getHowManyLayers() {
		cin >> numOfIncomingLayers;
		return numOfIncomingLayers == 0;
	}
	bool canStack(Layer topLayer, int i) {
		return topLayer.diameter <= layers[i].diameter;
	}
	int bestFromHere(Layer topLayer) {
		int bestHeight = 0;
		for (int i = 0; i < layers.size(); i++) {
			if (canStack(topLayer, i)) {
				if (bestHeight <= layers[i].bestFromHere) {
					bestHeight = layers[i].bestFromHere;
				}
			}
		}
		return bestHeight + 1;
	}
	void makeTallestCake() {
		for (int i = 0; i < numOfIncomingLayers; i++) {

			// input next layer
			Layer newLayer;
			cin >> newLayer.diameter;

			// record max amount of layers with newest layer as base
			newLayer.bestFromHere = bestFromHere(newLayer);

			// push newest layer on vector
			layers.push_back(newLayer);
		}
	}
	void printMaxFound() {
		int maxFound = 0;
		for (int i = 0; i < layers.size(); i++) {
			if (maxFound < layers[i].bestFromHere) {
				maxFound = layers[i].bestFromHere;
			}
		}
		cout << maxFound << endl;
	}
};

int main() {
	bool readyToQuit = false;
	while (!readyToQuit) {
		CakeCounter cc;
		readyToQuit = cc.getHowManyLayers();
		if (!readyToQuit) {
			cc.makeTallestCake();
			cc.printMaxFound();
		}
	}
}
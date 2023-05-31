


/*
----------------- [HEADER] ------------------

NAME: Cason Kirschner
COURSE: Comp-4300 A.I.
PROGRAM: Digit Recognition Neural Network

--------------- [DESCRIPTION] ---------------

The goal of this program is to recognize
a handwritten digit from a 28x28px bmp file.

---------------- [APPROACH] -----------------

28 x 28 = 784 pixels
input layer --> 784 nodes
hidden layer --> some amount
output layer --> 10 nodes (representing 0 - 9)

1. process bitmap file
2. convert to grayscale
3. obtain pixel data (brightness value 0.0 - 1.0)
4. convert to 2d vector for printing purposes
5. flatten 2d vector to use as input layer
6. the unique patterns that each digit creates 
    should more or less uniquely identify each digit.
7. There is much more detail than what I am choosing
    to write down.

---------------------------------------------
*/







#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <cmath>
#include <algorithm>
#include <random>
#include <array>
#include <iterator>
using namespace std;

#pragma region FILE_HANDLING_CODE
#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
    
};
#pragma pack(pop)

#pragma pack(push, 1)
struct BMPInfoHeader {
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
};
#pragma pack(pop)

void printPixelData(vector<vector<double>>& pixels) {
    cout << "    0 1 2 3 4 5 6 7 8 9 A B C D E F G H I J K L M N O P Q R" << endl;
    cout << "    -------------------------------------------------------" << endl;
    for (int r = 0; r < 28; r++) {
        if (r < 10) {
            cout << r << " | ";
        }
        else {
            cout << (char)(r + 55) << " | ";
        }
        for (int c = 0; c < 28; c++) {
            if (pixels[r][c] > 0.1) {
                cout << "0" << " ";
            }
            else {
                cout << " " << " ";
            }
        }
        cout << endl;
    }
}
bool inputBmpFile(vector<vector<double>>& pixels, string fileName) {
    // Open the input file
    ifstream inputFile(fileName, ios::binary);

    if (inputFile.is_open() == false) {
        cout << "Error opening specified file: " << fileName << endl;
        system("pause");
        return false;
    }

    // Read the BMP file header and DIB header
    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;
    inputFile.read((char*)&fileHeader, sizeof(fileHeader));
    inputFile.read((char*)&infoHeader, sizeof(infoHeader));

    // Calculate the size of the pixel data in bytes    
    uint32_t rowSize = (infoHeader.biBitCount * infoHeader.biWidth + 31) / 32 * 4;
    uint32_t dataSize = rowSize * abs(infoHeader.biHeight);

    // Allocate memory to store the pixel data
    vector<uint8_t> pixelData(dataSize);
    inputFile.seekg(fileHeader.bfOffBits);
    inputFile.read((char*)pixelData.data(), dataSize);

    // Convert the pixel data to a vector of bools
    int k = 0;
    for (int r = 0; r < 28; r++) {
        vector<double> newRow;
        for (int c = 0; c < 28; c++) {
            if (pixelData[k]) {
                newRow.push_back(0);
            }
            else {
                newRow.push_back(1);
            }
            k += 3;
        }
        pixels.push_back(newRow);
    }

    // Reverse the pixelDataBools 2d vector and return
    reverse(pixels.begin(), pixels.end());

    return true;
}
vector<double> flattenData(vector<vector<double>>& vect) {
    vector<double> result;
    for (int r = 0; r < 28; r++) {
        for (int c = 0; c < 28; c++) {
            result.push_back(vect[r][c]);
        }
    }
    return result;
}
#pragma endregion



#pragma region HELPER_LOGIC_CODE
int findMaxIndex(vector<double>& v) {
    int max = 0;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] > v[max]) {
            max = i;
        }
    }
    return max;
}
#pragma endregion



#pragma region LAYER_LOGIC_CODE
struct Layer {

    int nodesIn, nodesOut;
    vector<double> weights;

    Layer(int nodesIn, int nodesOut) {
        // initializes nodes in and out
        this->nodesIn = nodesIn;
        this->nodesOut = nodesOut;
        // initializes weights
        weights.resize(nodesIn, 0.1);
        initializeRandomWeights();
                                                
    }
    double activationFunction(double weightedInput) {
        // return (weightedInput > 0) ? 1 : 0;
        //return max(0.0, weightedInput); // reLu
        //return 1.0 / (1.0 + exp(-weightedInput)); // sigmoid
        return weightedInput;
    }
    vector<double> calcOutputs(vector<double> inputs) {
        // initializes weightedInputs
        vector<double> activations(nodesOut);
                                                            
        for (int o = 0; o < nodesOut; o++) {
            double weightedInput = 0;
            for (int i = 0; i < nodesIn; i++) {
                weightedInput += inputs[i];
            }
            activations[o] = (activationFunction(weightedInput));
        }
        // returns activations to be passed to next layer
        return activations;
    }
    void initializeRandomWeights() {
        for (int i = 0; i < nodesIn; i++) {            
                random_device dev;
                mt19937 rng(dev());
                uniform_int_distribution<mt19937::result_type> dist6(1, 6);
                weights[i] = dist6(rng);           
        }
    }

};
#pragma endregion



#pragma region NETWORK_LOGIC_CODE
struct Network {

    vector<Layer> layers;

    Network(vector<int> sizesOfLayers) {
        // initializes layers
        for (int i = 0; i < sizesOfLayers.size() - 1; i++) {
            Layer newLayer(sizesOfLayers[i], sizesOfLayers[i + 1]);
            layers.push_back(newLayer);
        }
    }
    vector<double> calcOutputs(vector<double>& inputs) {
        vector<double> nextInputs(inputs);
        for (int i = 0; i < layers.size(); i++) {
            nextInputs = layers[i].calcOutputs(inputs);
            for (int x = 0; x < nextInputs.size(); x++) {
                cout << "[" << nextInputs[x] << "] ";
            }
            cout << endl << endl;
        }
        return nextInputs;
    }
    int Classify(vector<double>& inputs) {
        vector<double> outputs = calcOutputs(inputs);
        return findMaxIndex(outputs);
    }

};
#pragma endregion



#pragma region MAIN_LOGIC_CODE
int main() {

    string filename;
    Network network({ 784, 1024, 1024, 10 });
    cout << "==================== [NEURAL NETWORK] ====================" << endl;
    cout << "Enter 28x28px bitmap filename (excluding .bmp): ";
    while (cin >> filename && filename != "quit") {
        cout << endl;
        vector<vector<double>> pixels;
        if (inputBmpFile(pixels, (filename + ".bmp"))) {
            printPixelData(pixels);
            vector<double> inputs = flattenData(pixels);
            cout << endl << "==================== [Network Determined: " << network.Classify(inputs) << "] ====================" << endl << endl;
            system("pause");
        }
        system("cls");
        cout << "==================== [NEURAL NETWORK] ====================" << endl;
        cout << "Enter 28x28px bitmap filename (excluding .bmp): ";
    }

}
#pragma endregion
#include "Tensor1D.h"
#include <iostream>

using namespace std;

int main() {
    int64_t a_batch = 1, a_channel = 3, a_height = 3, a_width = 3;
	int64_t b_batch = 1, b_channel = 3, b_height = 2, b_width = 2;
    int64_t randomMax = 10;
    cout << "Define Tensor A Dimensions: " << endl;
    cin >> a_batch >> a_channel >> a_height >> a_width;
    cout << "Define Tensor B Dimensions: " << endl;
    cin >> b_batch >> b_channel >> b_height >> b_width;

    if(a_channel != b_channel || a_height < b_height || a_width < b_width) {
        cout << "Warning: wrong dimensions" << endl;
        return -1;
    }

    cout << "Specify the potential largest number to fill the tensor: " << endl;
    cin >> randomMax;
    Tensor1D<int> B(b_batch, b_channel, b_height, b_width);
    Tensor1D<int> A(a_batch, a_channel, a_height, a_width);
    A.randomAssign(randomMax);
    B.randomAssign(randomMax);
    Tensor1D<int> C = A * B;
    
    A.printAddress();
    A.print();
    // B.printAddress();
    // C.printAddress();
}
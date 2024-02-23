#pragma once
#include "Tensor.h"
#include <iostream>
#include <vector>

using namespace std;
template <class T>
class Tensor1D : public Tensor<T>{
    private:
        vector<T> _tensor;
    
    public:
        Tensor1D() {
            Tensor1D(0, 0, 0, 0);
        }

        Tensor1D(int64_t N, int64_t C, int64_t H, int64_t W) {
            this->batch = N;
		    this->channel = C;
		    this->height = H;
		    this->width = W;
            _tensor.resize(N * C * H * W);
        }

        // Return Tensor1D object
        vector<T> getTensor() {
            return _tensor;
        }

        // Return the reference at tensor[i][j][k][m]
        T& operator() (int64_t i, int64_t j, int64_t m, int64_t n) override {
            return _tensor[i * this->channel * this->height * this->width
                        + j * this->height * this->width + m * this->width + n];
        }

        // Return the const reference at tensor[i][j][k][m]
        const T& operator() (int64_t i, int64_t j, int64_t m, int64_t n) const override {
            return _tensor[i * this->channel * this->height * this->width
                        + j * this->height * this->width + m * this->width + n];
        }

};
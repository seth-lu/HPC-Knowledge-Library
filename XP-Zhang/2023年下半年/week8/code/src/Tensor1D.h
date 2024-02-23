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

        // Convolution A * B
        // Tensor1D<T> operator* (const Tensor1D<T>& B) {
        //     int64_t s = 1;
        //     Tensor1D<T> C(this->batch, B.batch, this->height - B.height + 1, this->width - B.width + 1);
        //     for(size_t i = 0; i < C.batch; ++i)
        //         for(int j = 0; j < C.channel; ++j)
        //             for(size_t m = 0; m < C.height; ++m)
        //                 for(size_t n = 0; n < C.width; ++n)
        //                     for(size_t r = 0; r < B.channel; ++r)
        //                         for(size_t u = 0; u < B.height; ++u)
        //                             for(size_t v = 0; v < B.width; ++v)
        //                                 C(i, j, m, n) += (*this)(i, r, m * s + u, n * s + v) * B(j, r, u, v);
        //     return C;
        // }

        Tensor1D<T> operator* (const Tensor1D<T>& B) {
            return convolutionWithStride(B, 1);
        }

        Tensor1D<T> convolutionWithStride (const Tensor1D<T>& B, int64_t s) {
            Tensor1D<T> C(this->batch, B.batch, (this->height - B.height) / s + 1, (this->width - B.width) / s + 1);
            for(size_t i = 0; i < C.batch; ++i)
                for(size_t j = 0; j < C.channel; ++j)
                    for(size_t m = 0; m < C.height; ++m)
                        for(size_t n = 0; n < C.width; ++n)
                            for(size_t r = 0; r < B.channel; ++r)
                                for(size_t u = 0; u < B.height; ++u)
                                    for(size_t v = 0; v < B.width; ++v)
                                        C(i, j, m, n) += (*this)(i, r, m * s + u, n * s + v) * B(j, r, u, v);
            return C;
        }
};
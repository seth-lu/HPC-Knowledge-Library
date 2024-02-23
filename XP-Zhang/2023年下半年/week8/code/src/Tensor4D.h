#pragma once
#include "Tensor.h"
#include <iostream>
#include <vector>


using namespace std;
template <typename T>//定义模板数据结构
class Tensor4D : public Tensor<T>
{
private:
	vector<vector<vector<vector<T>>>> tensors;

public:
	Tensor4D() {
		this->batch = 0;
		this->channel = 0;
		this->height = 0;
		this->width = 0;
		this->tensors.resize(0);
	}

	Tensor4D(int64_t N, int64_t C, int64_t H, int64_t W) {
		this->batch = N;
		this->channel = C;
		this->height = H;
		this->width = W;
		// 给四维数组分配空间
		this->tensors.resize(N);
		for (int64_t i = 0; i < this->batch; ++i) {
			this->tensors[i].resize(C);
			for (int64_t j = 0; j < this->channel; ++j) {
				this->tensors[i][j].resize(H);
				for (int64_t k = 0; k < this->height; ++k) {
					this->tensors[i][j][k].resize(W);
				}
			}
		}

		// // 初始化
		// for (int64_t i = 0; i < this->batch; ++i) {
		// 	for (int64_t j = 0; j < this->channel; ++j) {
		// 		for (int64_t k = 0; k < this->height; ++k) {
		// 			for (int64_t l = 0; l < this->width; ++l) {
		// 				this->tensors[i][j][k][l] = 0;
		// 			}
		// 		}
		// 	}
		// }
	}

	// Revised Ma' print method because it can't run on my machine
	// Print out the tensor
	// void print() {
	// 	for(int i = 0; i < this->batch; ++i) {
	// 		cout << "Batch " << i << endl;
	// 		for(int j = 0; j < this->channel; ++j) {
	// 			cout << "Channel " << j << endl;
	// 			for(int m = 0; m < this->height; ++m) {
	// 				for(int n = 0; n < this->width; ++n) {
	// 					cout << (*this)(i, j, m, n) << " ";
	// 				}
	// 				cout << endl;
	// 			}
	// 		}
	// 	}
	// }

	vector<vector<vector<vector<T>>>> getTensors() {
		return this->tensors;
	}

	// void setTensors(int64_t i, int64_t j, int64_t m, int64_t n, T num) {
	// 	this->tensors[i][j][m][n] += num;
	// }

	T&  operator() (int64_t i, int64_t j, int64_t m, int64_t n) override
	{
		return tensors[i][j][m][n];
	}
	const T& operator() (int64_t i, int64_t j, int64_t m, int64_t n)const override
	{
		return tensors[i][j][m][n];
	}

	// // Revised Ma' convolution method to overloaded operators
	// Tensor4D<T> operator* (const Tensor4D<T>& B) {
	// 	int64_t s = 1;
	// 	Tensor4D<int> C(this->batch, B.batch, this->height - B.height + 1, this->width - B.width + 1);
	// 	for(size_t i = 0; i < C.batch; ++i)
	// 		for(int j = 0; j < C.channel; ++j)
	// 			for(size_t m = 0; m < C.height; ++m)
	// 				for(size_t n = 0; n < C.width; ++n)
	// 					for(size_t r = 0; r < B.channel; ++r)
	// 						for(size_t u = 0; u < B.height; ++u)
	// 							for(size_t v = 0; v < B.width; ++v)
	// 								C(i, j, m, n) += (*this)(i, r, m * s + u, n * s + v) * B(j, r, u, v);
	// 	return C;
	// }
	
	Tensor4D<T> operator* (const Tensor4D<T>& B) {
		return convolutionWithStride(B, 1);
	}

	Tensor4D<T> convolutionWithStride (const Tensor4D<T>& B, int64_t s) {
		Tensor4D<T> C(this->batch, B.batch, (this->height - B.height) / s + 1, (this->width - B.width) / s + 1);
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
#pragma once
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

	}

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

};

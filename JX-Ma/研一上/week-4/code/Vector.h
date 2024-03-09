#include <iostream>
#include <random>
#include <ctime>
#include<cmath>
class Vector
{
private:
	int length;	
	int* v_data;
public:
	Vector() {
		this->length = 0;
		this->v_data = nullptr;
	}
	Vector(int length, int* v_data) {
		this->v_data = new int[length + 1];
		this->length = length;
		this->v_data = v_data;
	}
	// 随机生成向量
	Vector(int length) {
		this->v_data = new int[length + 1];
		this->length = length;
		std::random_device engine;
		for (int i = 0; i < this->length; ++i) {
			this->v_data[i] =abs((int)(engine() % 100));
		}
	}
	void setLength(int length) {
		this->length = length;
	}
	int getLength() {
		return this->length;
	}
	int* getVData() {
		return this->v_data;
	}
	void setVData(int* v_data) {
		this->v_data = v_data;
	}

	void printVector() {
		for (int i = 0; i < this->length; ++i) {
			std::cout << this->v_data[i] << " ";
		}
		std::cout << std::endl;
	}

	// 重载运算符[]
	int operator[](int index)const { return this->v_data[index]; }

	// 重载运算符向量加法
	Vector operator+(Vector A) {
		if (this->length != A.getLength()) {
			std::cout << "向量长度不同，无法进行向量相加" << std::endl;
		}
		for (int i = 0; i < this->length; ++i) {
			this->v_data[i] += A.getVData()[i];
		}
		return *this;
	}

	// 重载运算符+
	Vector operator+(int a) {
		for (int i = 0; i < this->length; ++i) {
			this->v_data[i] += a;
		}
		return *this;
	}

	// 重载运算符-
	Vector operator-(Vector A) {
		if (this->length != A.getLength()) {
			std::cout << "向量长度不同，无法进行向量相加" << std::endl;
		}
		for (int i = 0; i < this->length; ++i) {
			this->v_data[i] -= A.getVData()[i];
		}
		return *this;
	}

	Vector operator-(int a) {
		for (int i = 0; i < this->length; ++i) {
			this->v_data[i] -= a;
		}
		return *this;
	}

	// 数乘
	Vector operator*(int a) {
		for (int i = 0; i < this->length; ++i) {
			this->v_data[i] *= a;
		}
		return *this;
	}
};

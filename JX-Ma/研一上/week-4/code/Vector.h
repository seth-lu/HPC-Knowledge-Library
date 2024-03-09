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
	// �����������
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

	// ���������[]
	int operator[](int index)const { return this->v_data[index]; }

	// ��������������ӷ�
	Vector operator+(Vector A) {
		if (this->length != A.getLength()) {
			std::cout << "�������Ȳ�ͬ���޷������������" << std::endl;
		}
		for (int i = 0; i < this->length; ++i) {
			this->v_data[i] += A.getVData()[i];
		}
		return *this;
	}

	// ���������+
	Vector operator+(int a) {
		for (int i = 0; i < this->length; ++i) {
			this->v_data[i] += a;
		}
		return *this;
	}

	// ���������-
	Vector operator-(Vector A) {
		if (this->length != A.getLength()) {
			std::cout << "�������Ȳ�ͬ���޷������������" << std::endl;
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

	// ����
	Vector operator*(int a) {
		for (int i = 0; i < this->length; ++i) {
			this->v_data[i] *= a;
		}
		return *this;
	}
};

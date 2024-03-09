#include<iostream>
#include "Vector.h"

class Matrix
{
private:
	int m_row;
	int m_column;
	Vector * m_data;

public:
	Matrix() {
		this->m_row = 0;
		this->m_column = 0;
		this->m_data = nullptr;
	}
	Matrix(int row, int column, Vector* data) {
		this->m_column = column;
		this->m_row = row;
		this->m_data = data;
	}
	Matrix(int row, int column) {
		this->m_column = column;
		this->m_row = row;
		this->m_data = new Vector[row];
		for (int i = 0; i < row; ++i) {
			this->m_data[i] = Vector(column);
		}
	}

	void initMatrix() {
		for (int i = 0; i < this->getMRow(); ++i) {
			for (int j = 0; j < this->getMColumn(); ++j) {
				this->m_data[i].getVData()[j] = 0;
			}
		}
	}

	int getMRow() { return this->m_row; }
	int getMColumn() { return this->m_column; }
	Vector* getMData() { return this->m_data; }

	void setMRow(int row) { this->m_row = row; }
	void setMColumn(int column) { this->m_column = column; }
	void setMData(Vector* data) { this->m_data = data; }

	void printMatrix() {
		for (int i = 0; i < this->m_row; ++i) {
			for (int j = 0; j < this->m_column; ++j) {
				std::cout << this->m_data[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

	
	// 矩阵+矩阵
	Matrix operator+(Matrix A) {
		if ((A.getMRow() != this->getMRow()) || A.getMColumn() != this->getMColumn()) {
			std::cout << "矩阵格式错误" << std::endl;
		}
		for (int i = 0; i < this->getMRow(); ++i) {
			for (int j = 0; j < this->getMColumn(); ++j) {
				this->m_data[i].getVData()[j] += A.getMData()[i][j];
			}
		}
		return *this;
	}

	// 矩阵+常数
	Matrix operator+(int a) {
		for (int i = 0; i < this->getMRow(); ++i) {
			for (int j = 0; j < this->getMColumn(); ++j) {
				this->m_data[i].getVData()[j] += a;
			}
		}
		return *this;
	}

	// 矩阵-矩阵
	Matrix operator-(Matrix A) {
		if ((A.getMRow() != this->getMRow()) || A.getMColumn() != this->getMColumn()) {
			std::cout << "矩阵格式错误" << std::endl;
		}
		for (int i = 0; i < this->getMRow(); ++i) {
			for (int j = 0; j < this->getMColumn(); ++j) {
				this->m_data[i].getVData()[j] -= A.getMData()[i][j];
			}
		}
		return *this;
	}

	// 矩阵-常数
	Matrix operator-(int a) {
		for (int i = 0; i < this->getMRow(); ++i) {
			for (int j = 0; j < this->getMColumn(); ++j) {
				this->m_data[i].getVData()[j] -= a;
			}
		}
		return *this;
	}

	// 矩阵*矩阵
	/*Matrix operator*(Matrix A) {
		if (this->m_column != A.getMRow()) {
			std::cout << "格式错误：无法相乘" << std::endl;
		}
		int C_row = this->m_row;
		int C_column = A.getMColumn();
		Matrix C(C_row, C_column);
		C.initMatrix();
		for (int i = 0; i < C_row; ++i) {
			for (int j = 0; j < C_column; ++j) {
				for (int k = 0; k < A.getMRow(); ++k) {
					C.getMData()[i].getVData()[j] += this->m_data[i][k] * A.getMData()[k][j];
				}
			}
		}
		return C;
	}*/

	// 矩阵*常数
	Matrix operator*(int a) {
		for (int i = 0; i < this->getMRow(); ++i) {
			for (int j = 0; j < this->getMColumn(); ++j) {
				this->m_data[i].getVData()[j] *= a;
			}
		}
		return *this;
	}

	// 矩阵*矩阵 Hoisting 优化
	/*Matrix operator*(Matrix A) {
		if (this->m_column != A.getMRow()) {
			std::cout << "格式错误：无法相乘" << std::endl;
		}
		int C_row = this->m_row;
		int C_column = A.getMColumn();
		Matrix C(C_row, C_column);
		for (int i = 0; i < C_row; ++i) {
			for (int j = 0; j < C_column; ++j) {
				int t = 0;
				for (int k = 0; k < A.getMRow(); ++k) {
					t += this->m_data[i][k] * A.getMData()[k][j];
				}
				C.getMData()[i].getVData()[j] = t;
			}
		}
		return C;
	}*/

	// 矩阵*矩阵 Unrolling
	Matrix operator*(Matrix A) {
		if (this->m_column != A.getMRow()) {
			std::cout << "格式错误：无法相乘" << std::endl;
		}
		int C_row = this->m_row;
		int C_column = A.getMColumn();
		Matrix C(C_row, C_column);
		C.initMatrix();
		for (int i = 0; i < C_row; i+=2) {
			for (int j = 0; j < C_column; j+=2) {
				for (int k = 0; k < A.getMRow(); ++k) {
					C.getMData()[i].getVData()[j] += this->m_data[i][k] * A.getMData()[k][j];
					C.getMData()[i].getVData()[j+1] += this->m_data[i][k] * A.getMData()[k][j+1];
					C.getMData()[i+1].getVData()[j] += this->m_data[i+1][k] * A.getMData()[k][j];
					C.getMData()[i+1].getVData()[j+1] += this->m_data[i+1][k] * A.getMData()[k][j+1];
				}
			}
		}
		return C;
	}

	// 矩阵*矩阵 UNrolling+hoisting
	/*Matrix operator*(Matrix A) {
		if (this->m_column != A.getMRow()) {
			std::cout << "格式错误：无法相乘" << std::endl;
		}
		int C_row = this->m_row;
		int C_column = A.getMColumn();
		Matrix C(C_row, C_column);
		C.initMatrix();
		for (int i = 0; i < C_row; i += 2) {
			for (int j = 0; j < C_column; j += 2) {
				int t00 = C.getMData()[i][j];
				int t01 = C.getMData()[i][j + 1];
				int t10 = C.getMData()[i + 1][j];
				int t11 = C.getMData()[i + 1][j + 1];

				for (int k = 0; k < A.getMRow(); ++k) {
					t00 += this->m_data[i][k] * A.getMData()[k][j];
					t01 += this->m_data[i][k] * A.getMData()[k][j + 1];
					t10 += this->m_data[i + 1][k] * A.getMData()[k][j];
					t11 += this->m_data[i + 1][k] * A.getMData()[k][j + 1];
				}
				C.getMData()[i].getVData()[j] = t00;
				C.getMData()[i].getVData()[j + 1] = t01;
				C.getMData()[i + 1].getVData()[j] = t10;
				C.getMData()[i + 1].getVData()[j + 1] = t11;
			}
		}
		return C;
	}*/
};


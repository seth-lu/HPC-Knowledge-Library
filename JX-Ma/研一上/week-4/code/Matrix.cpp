#include "Matrix.h"
#include <chrono>
using namespace std;
class Vector;

double calculateGFloat(double time, long long count) {
	return count / time;
}
//template<class Matrix,class Matrix,class Matrix>
//void multiply1(Matrix C,  Matrix A,  Matrix B ) {
//	for (int i = 0; i < C.getMRow(); ++i) {
//		for (int j = 0; j < C.getMColumn(); ++j) {
//			for (int k = 0; k < A.getMRow(); ++k) {
//				C.getMData()[i].getVData()[j] += A.getMData()[i][k] * B.getMData()[k][j];
//			}
//		}
//	}
//}

int main() {
	Matrix m1(2048,2048);
	Matrix m2(2048,2048);
	/*cout << "��ʼ������Ϊ:" << endl;
	m1.printMatrix();
	cout << "�˷�����Ϊ:" << endl;
	m2.printMatrix();*/

	//cout << "���Ծ���ӷ�:" << endl;
	//m1 = m1 + m2;
	//m1.printMatrix();

	//cout << "���Ծ���ӳ���:" << endl;
	//m1 = m1 + 3;
	//m1.printMatrix();

	//cout << "���Ծ������:" << endl;
	//m1 = m1 - m2;
	//m1.printMatrix();

	/*cout << "���Ծ���˷���:" << endl;
	Matrix m3 = m1 * m2;
	m3.printMatrix();*/

	Matrix m3(2048,2048);
	auto c1 = chrono::system_clock().now();
	m3 = m1 * m2;
	cout << "����ʱ��:" << (double)chrono::duration<double, milli>(chrono::system_clock().now() - c1).count() << "ms" << endl;
	/*m3.printMatrix();*/
	
}



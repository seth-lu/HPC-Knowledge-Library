#include "Tensor4D.h"
#include "Tensor1D.h"


struct Timer
{
	chrono::time_point<chrono::system_clock> start, end;
	Timer()
	{
		start = chrono::system_clock::now();
	}
	~Timer()
	{
		end = chrono::system_clock::now();
		cout << "花费的时间4:" << chrono::duration<double, milli>(end - start).count() << "ms" << endl;
	}
};

template<typename T>
void Convolution(const Tensor4D<T>& A, const Tensor4D<T>& B, Tensor4D<T>& C) {
	//cout<<"运算次数"<<(C.num_batch()-1) *  (C.num_channel()-1) *(C.num_height()-1) *(C.num_width()-1)*(B.num_channel()-1)
	// *(B.num_height() - 1)*(B.num_width()-1) *2<<endl;
	Timer timer;
	for (int64_t i = 0; i < C.num_batch(); ++i)
		for (int64_t j = 0; j < C.num_channel(); ++j)
			for (int64_t m = 0; m < C.num_height(); ++m)
				for (int64_t n = 0; n < C.num_width(); ++n)
					for (int64_t r = 0; r < B.num_channel(); ++r)
						for (int64_t u = 0; u < B.num_height(); ++u)
							for (int64_t v = 0; v < B.num_width(); ++v)
								//C.SetTensor(i, j, m, n, (A(i, r, m + u, n + v) * B(j, r, u, v)));
								C(i, j, m, n) += A(i, r, m  + u, n  + v) * B(j, r, u, v);
}



int main() {
	int64_t a_batch = 0, a_channel = 0, a_height = 0, a_width = 0;
	int64_t b_batch = 0, b_channel = 0, b_height = 0, b_width = 0;
	cout << "输入张量四个维度:";
	cin >> a_batch >> a_channel >> a_height >> a_width;

	cout << "输入卷积核四个维度:";
	cin >> b_batch >> b_channel >> b_height >> b_width;

	if (a_channel != b_channel)
		cout << "卷积核的通道维度必须等于输入张量的通道维度";

	for(int i = 0; i < 8; ++i){
		Tensor4D<int> A(a_batch, a_channel, a_height, a_width);
		Tensor4D<int> B(b_batch, b_channel, b_height, b_width);
		Tensor4D<int> C(a_batch, b_batch, a_height - b_height + 1, a_width - b_width + 1);
		Tensor1D<int> A1(a_batch, a_channel, a_height, a_width);
		Tensor1D<int> B1(b_batch, b_channel, b_height, b_width);
		Tensor1D<int> C1(a_batch, b_batch, a_height - b_height + 1, a_width - b_width + 1);
		/*cout << "一维张量中a[0][0][0][0]的地址:" << &A1(0, 0, 0, 0)<<endl;
		cout << "四维张量中a[0][0][0][0]的地址:" << &A(0, 0, 0, 0)<<endl;
		cout << "一维张量中a[0][0][1][0]的地址:" << &A1(0, 0, 1, 0) << endl;
		cout << "四维张量中a[0][0][1][0]的地址:" << &A(0, 0, 1, 0) << endl;
		cout << "一维张量中a[0][1][0][0]的地址:" << &A1(0, 1, 0, 0) << endl;
		cout << "四维张量中a[0][1][0][0]的地址:" << &A(0, 1, 0, 0) << endl;
		cout << "一维张量中a[1][0][0][0]的地址:" << &A1(1, 0, 0, 0) << endl;
		cout << "四维张量中a[1][0][0][0]的地址:" << &A(1, 0, 0, 0) << endl;*/

		
		A.randomAssign(100);
		B.randomAssign(100);
		A1.randomGenerate(100);
		B1.randomGenerate(100);
		cout<<i+1<<endl;
		Convolution(A, B, C);
		C1 = A1 * B1;
		if(i<3){
			a_batch+=10;
		}
		if(i>=3){
			a_width+=50;
			a_height+=50;
		}
	}
	/*A1.print();
	B1.print();
	C1.print();*/
	//C.printTensor();
}
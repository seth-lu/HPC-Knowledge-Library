#include "Tensor4D.h"
#include "Tensor1D.h"
#include"Timer.h"

// struct Timer0
// {
// 	chrono::time_point<chrono::system_clock> start, end;
	
// 	Timer0()
// 	{
// 		start = chrono::system_clock::now();
// 	}
// 	~Timer0()
// 	{
// 		end = chrono::system_clock::now();

// 		cout << "花费的时间:" << chrono::duration<double,milli>(end-start).count()  << "ms" << endl;
// 	}
	
// };

template<typename T>
void Convolution(const Tensor<T>& A,const Tensor<T>& B,Tensor<T>& C) {
	// 初始化输出张量
	
	// Timer0 timer0;
	for (int64_t i = 0; i <= C.num_batch()-1; ++i)
		for (int64_t j = 0; j <= C.num_channel()-1; ++j) {
			//cout << "进行中" << endl;
			for (int64_t m = 0; m <= C.num_height()-1; ++m)
				for (int64_t n = 0; n <= C.num_width()-1; ++n)
					for (int64_t r = 0; r <= A.num_channel() - 1; ++r)
						for (int64_t u = 0; u <= B.num_height()-1; ++u)
							for (int64_t v = 0; v <= B.num_width()-1; ++v) {
								C(i, j, m, n) += A(i, r, m + u, n + v) * B(j, r, u, v);
								//C.setTensors(i, j, m, n, (A(i, r, m + u, n + v) * B(j, r, u, v)));
							}
		}

	
}
int main() {
	// int64_t a_batch = 0, a_channel = 0, a_height = 0, a_width = 0;
	// int64_t b_batch = 0, b_channel = 0, b_height = 0, b_width = 0;

	// cout << "输入输入张量中的四个维度:";
	// cin >> a_batch >> a_channel >> a_height >> a_width;
	
	// cout << "输入卷积核中的四个维度:";
	// cin >> b_batch >> b_channel >> b_height >> b_width;

	//1×100×1000×1000 2e+08
	//1×500×1000×1000 1e+09
	//1×1000×1000×1000 2e+09

	int64_t a_batch = 1, a_channel = 1000, a_height = 1000, a_width = 1000;
	int64_t b_batch = 1, b_channel = 1000, b_height = 1000, b_width = 1000;

	
	if (a_channel != b_channel)
		cout << "卷积核通道维度应该等于输入张量中的通道维度";


    Tensor1D<int> A(a_batch, a_channel, a_height, a_width);
	Tensor1D<int> B(b_batch, b_channel, b_height, b_width);
	Tensor1D<int> C(A.num_batch(), B.num_batch(), (A.num_height() - B.num_height() + 1), (A.num_width() - B.num_width() + 1));

	A.randomGenerate(10);
	B.randomGenerate(10);

    Tensor4D<int> A_4(a_batch, a_channel, a_height, a_width);
	Tensor4D<int> B_4(b_batch, b_channel, b_height, b_width);
	Tensor4D<int> C_4(A.num_batch(), B.num_batch(), (A.num_height() - B.num_height() + 1), (A.num_width() - B.num_width() + 1));

	A_4.randomGenerate(10);
	B_4.randomGenerate(10);

	cout<< "Tensor1D开始运行"<<endl;
	cout<< "a_batch=" <<a_batch <<" a_channel = " << a_channel << " a_height = "<< a_height << " a_width = "<<a_width <<endl;
	cout<< "b_batch=" <<b_batch <<" b_channel = " << b_channel << " b_height = "<< b_height << " b_width = "<<b_width <<endl;
	Timer T;
	T.start();
	Convolution(A, B, C);
	T.stop();
	cout<< "用时"<<T.elapsed() <<"ms"<<endl;

	// A.printTensor();
	// B.printTensor();
	// C.printTensor();

	cout<< "Tensor4D开始运行"<<endl;
	cout<< "a_batch=" <<a_batch <<" a_channel = " << a_channel << " a_height = "<< a_height << " a_width = "<<a_width <<endl;
	cout<< "b_batch=" <<b_batch <<" b_channel = " << b_channel << " b_height = "<< b_height << " b_width = "<<b_width <<endl;
	T.start();
	Convolution(A_4, B_4, C_4);
	T.stop();
	cout<< "用时"<<T.elapsed() <<"ms"<<endl;

	// A_4.printTensor();
	// B_4.printTensor();
	// C_4.printTensor();
}
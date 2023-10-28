#include "Tensor4D.h"
#include<chrono>

// struct Timer
// {
// 	chrono::time_point<chrono::system_clock> start, end;
	
// 	Timer()
// 	{
// 		start = chrono::system_clock::now();
// 	}
// 	~Timer()
// 	{
// 		end = chrono::system_clock::now();

// 		cout << "花费的时间:" << chrono::duration<double,milli>(end-start).count()  << "ms" << endl;
// 	}
	
// };

// template<typename T>
// Tensor4D<T> Convolution(Tensor4D<T> A, Tensor4D<T> B) {
// 	// 初始化输出张量
// 	Tensor4D<int> C(A.num_batch(), B.num_batch(), (A.num_height() - B.num_height() + 1), (A.num_width() - B.num_width() + 1));
// 	Timer timer;
// 	for (int64_t i = 0; i <= C.num_batch()-1; ++i)
// 		for (int64_t j = 0; j <= C.num_channel()-1; ++j) {
// 			//cout << "进行中" << endl;
// 			for (int64_t m = 0; m <= C.num_height()-1; ++m)
// 				for (int64_t n = 0; n <= C.num_width()-1; ++n)
// 					for (int64_t r = 0; r <= A.num_channel() - 1; ++r)
// 						for (int64_t u = 0; u <= B.num_height()-1; ++u)
// 							for (int64_t v = 0; v <= B.num_width()-1; ++v) {

// 								C.setTensors(i, j, m, n, (A(i, r, m + u, n + v) * B(j, r, u, v)));
// 							}
// 		}

	
// 	return C;
// }
int main() {
	int64_t a_batch = 0, a_channel = 0, a_height = 0, a_width = 0;
	int64_t b_batch = 0, b_channel = 0, b_height = 0, b_width = 0;
    int64_t randomMax = 10;
	cout << "Define Tensor A Dimensions: ";
	cin >> a_batch >> a_channel >> a_height >> a_width;
	
	cout << "Define Tensor B Dimensions: ";
	cin >> b_batch >> b_channel >> b_height >> b_width;
	
	if (a_channel != b_channel)
		cout << "Should have equal channel size";

	cout << "Specify the potential largest number to fill the tensor: " << endl;
    cin >> randomMax;

	Tensor4D<int> A(a_batch, a_channel, a_height, a_width);
	Tensor4D<int> B(b_batch, b_channel, b_height, b_width);
	
	cout << a_batch << a_channel << a_height << a_width;
	A.randomAssign(randomMax);
	B.randomAssign(randomMax);
	Tensor4D<int> C = A * B;
	A.print();
	// B.print();
	// C.print();
	A.printAddress();
}
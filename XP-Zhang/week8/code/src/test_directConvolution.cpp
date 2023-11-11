#include "Tensor1D.h"
#include "Tensor4D.h"

#include <vector>
using namespace std;

template<typename T>
void directConvolution_tensor(const Tensor<T>& A,const Tensor<T>& B,Tensor<T>& C,int64_t s){
    for (int64_t i = 0; i < C.num_batch(); ++i){
        for (int64_t j = 0; j < C.num_channel(); ++j){
			for (int64_t m = 0; m < C.num_height(); ++m){
                for (int64_t n = 0; n < C.num_width(); ++n){
                    // for (int64_t r = 0; r < A.num_channel(); ++r){
                    for (int64_t r = 0; r < B.num_channel(); ++r){
                        for (int64_t u = 0; u < B.num_height(); ++u){
                            for (int64_t v = 0; v < B.num_width(); ++v) {
								// C(i, j, m, n) += A(i, r, m + u, n + v) * B(j, r, u, v);
                                C(i, j, m, n) += A(i, r, m * s + u, n * s + v) * B(j, r, u, v);
								//C.setTensors(i, j, m, n, (A(i, r, m + u, n + v) * B(j, r, u, v)));
							}
                        }
                    }
                }
            }
		}
    }
}

template<typename T>
void directConvolution_tensor_1(const Tensor<T>& A,const Tensor<T>& B,Tensor<T>& C,int64_t s){
    for (size_t i = 0; i < C.num_batch(); ++i){
        for (size_t j = 0; j < C.num_channel(); ++j){
			for (size_t m = 0; m < C.num_height(); ++m){
                for (size_t n = 0; n < C.num_width(); ++n){
                    // for (int64_t r = 0; r < A.num_channel(); ++r){
                    for (size_t r = 0; r < B.num_channel(); ++r){
                        for (size_t u = 0; u < B.num_height(); ++u){
                            for (size_t v = 0; v < B.num_width(); ++v) {
								// C(i, j, m, n) += A(i, r, m + u, n + v) * B(j, r, u, v);
                                C(i, j, m, n) += A(i, r, m * s + u, n * s + v) * B(j, r, u, v);
								//C.setTensors(i, j, m, n, (A(i, r, m + u, n + v) * B(j, r, u, v)));
							}
                        }
                    }
                }
            }
		}
    }
}

template<typename T>
void directConvolution_tensor_2(const Tensor<T>& A,const Tensor<T>& B,Tensor<T>& C,int64_t s){
    for (size_t i = 0; i < C.num_batch(); ++i)
        for (size_t j = 0; j < C.num_channel(); ++j)
			for (size_t m = 0; m < C.num_height(); ++m)
                for (size_t n = 0; n < C.num_width(); ++n)
                    // for (int64_t r = 0; r < A.num_channel(); ++r)
                    for (size_t r = 0; r < B.num_channel(); ++r)
                        for (size_t u = 0; u < B.num_height(); ++u)
                            for (size_t v = 0; v < B.num_width(); ++v) {
								// C(i, j, m, n) += A(i, r, m + u, n + v) * B(j, r, u, v);
                                C(i, j, m, n) += A(i, r, m * s + u, n * s + v) * B(j, r, u, v);
								//C.setTensors(i, j, m, n, (A(i, r, m + u, n + v) * B(j, r, u, v)));
							}
}


int main() {
    const int randomMax = 10;
    Tensor1D<double> A(1,2,4,4); 
    Tensor1D<double> B(1,2,2,2);
    Tensor1D<double> C(1,1,3,3);
    A.randomAssign(randomMax);
    B.randomAssign(randomMax);
    A.print();
    B.print();
    C.print();

    // directConvolution_tensor(A,B,C,1);
    C=A*B;
    C.print();


}
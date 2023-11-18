#include "Tensor1D.h"
#include "Tensor4D.h"
#include "Timer.h"
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

struct tensorDimensions {
    int64_t channel;
    int64_t height;
    int64_t width;
};

int main(int argc,char *argv[]) {
    const int64_t G = 1e9;
    const int64_t MAXSIZE = 12; //the numbler of conv
    const int64_t a_batch = 10; //batch of input
    const int64_t randomMax = 10;

    // hard encoding tensor dimensions:
    vector<tensorDimensions> inputDimensions;
    inputDimensions.push_back(tensorDimensions{3, 227, 227});
    inputDimensions.push_back(tensorDimensions{3, 231, 231});
    inputDimensions.push_back(tensorDimensions{3, 227, 227});
    inputDimensions.push_back(tensorDimensions{64, 224, 224});

    inputDimensions.push_back(tensorDimensions{96, 24, 24});
    inputDimensions.push_back(tensorDimensions{256, 12, 12});
    inputDimensions.push_back(tensorDimensions{3, 224, 224});
    inputDimensions.push_back(tensorDimensions{64, 112, 112});

    inputDimensions.push_back(tensorDimensions{64, 56, 56});
    inputDimensions.push_back(tensorDimensions{128, 28, 28});
    inputDimensions.push_back(tensorDimensions{256, 14, 14});
    inputDimensions.push_back(tensorDimensions{512, 7, 7});

    vector<tensorDimensions> filterDimensions;
    filterDimensions.push_back(tensorDimensions{3, 11, 11});
    filterDimensions.push_back(tensorDimensions{3, 11, 11});
    filterDimensions.push_back(tensorDimensions{3, 7, 7});
    filterDimensions.push_back(tensorDimensions{64, 7, 7});

    filterDimensions.push_back(tensorDimensions{96, 5, 5});
    filterDimensions.push_back(tensorDimensions{256, 3, 3});
    filterDimensions.push_back(tensorDimensions{3, 3, 3});
    filterDimensions.push_back(tensorDimensions{64, 3, 3});

    filterDimensions.push_back(tensorDimensions{64, 3, 3});
    filterDimensions.push_back(tensorDimensions{128, 3, 3});
    filterDimensions.push_back(tensorDimensions{256, 3, 3});
    filterDimensions.push_back(tensorDimensions{512, 3, 3});
    // hard encoding stride: 
    vector<int64_t> strides {4, 4, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1};

    // hard encoding filter batch size
    vector<int64_t> bBatch {96, 96, 64, 64, 256, 512, 64, 128, 64, 128, 256, 512};

    // performance vectors
    vector<string> sizes;
    vector<double> times1d;
    vector<double> gflops1d;
    vector<double> times4d;
    vector<double> gflops4d;

    //timer
    Timer T;
    double elapsed;

    // record time cost
    for(int i = 0; i < MAXSIZE; ++i) {
        sizes.push_back("Conv" + to_string(i + 1));
        // 2 flops per iteration
        int64_t operations = a_batch * bBatch[i] * ((inputDimensions[i].height - filterDimensions[i].height) / strides[i] + 1) * ((inputDimensions[i].width - filterDimensions[i].width) / strides[i] + 1)
                         * filterDimensions[i].channel * filterDimensions[i].height * filterDimensions[i].width * 2;

        // Tensor1D
        Tensor1D<double> A(a_batch, inputDimensions[i].channel, inputDimensions[i].height, inputDimensions[i].width); 
        Tensor1D<double> B(bBatch[i], filterDimensions[i].channel, filterDimensions[i].height, filterDimensions[i].width);
        Tensor1D<double> C(a_batch, bBatch[i], (inputDimensions[i].height - filterDimensions[i].height) / strides[i] + 1, (inputDimensions[i].width - filterDimensions[i].width) / strides[i] + 1);
        A.randomAssign(randomMax);
        B.randomAssign(randomMax);
        T.start();
        directConvolution_tensor(A,B,C,strides[i]);
        T.stop();
        elapsed = T.elapsed();
        times1d.push_back(elapsed);
        gflops1d.push_back((operations / elapsed)/G);
        // Tensor 4D
        Tensor4D<double> M(a_batch, inputDimensions[i].channel, inputDimensions[i].height, inputDimensions[i].width); 
        Tensor4D<double> N(bBatch[i], filterDimensions[i].channel, filterDimensions[i].height, filterDimensions[i].width);
        Tensor4D<double> O(a_batch, bBatch[i], (inputDimensions[i].height - filterDimensions[i].height) / strides[i] + 1, (inputDimensions[i].width - filterDimensions[i].width) / strides[i] + 1);
        M.randomAssign(randomMax);
        N.randomAssign(randomMax);
        T.start();
        directConvolution_tensor(M,N,O,strides[i]);
        T.stop();
        elapsed = T.elapsed();
        times4d.push_back(elapsed);
        gflops4d.push_back((operations / elapsed)/G);

        cout<< "size " << i << " complete" << endl;
    }

    return 0;

}

#include "Tensor1D.h"
#include "Tensor4D.h"
#include "../include/matplotlibcpp.h"
#include <chrono>
#include <vector>
using namespace std;
using namespace chrono;
namespace plt = matplotlibcpp;

struct tensorDimensions {
    int64_t channel;
    int64_t height;
    int64_t width;
};



int main() {

    const int64_t G = 1e9;
    const int64_t MAXSIZE = 12;
    const int64_t a_batch = 10;
    const int64_t randomMax = 10;
    // const int64_t a_batch = 1, a_channel = 3;
	// const int64_t b_batch = 1, b_channel = 3, b_height = 3, b_width = 3;
    // const int64_t m_batch = 1, m_channel = 3;
	// const int64_t n_batch = 1, n_channel = 3, n_height = 3, n_width = 3;
    
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

    // initialize tensors

    // const Tensor1D<int> B(b_batch, b_channel, b_height, b_width);
    // const Tensor4D<int> N(n_batch, n_channel, n_height, n_width);

    // performance vectors
    vector<string> sizes;
    vector<double> times1d;
    vector<double> gflops1d;
    vector<double> times4d;
    vector<double> gflops4d;

    // record time cost
    for(int i = 0; i < MAXSIZE; ++i) {
        sizes.push_back("Conv" + to_string(i + 1));
        // 2 flops per iteration
        int64_t operations = a_batch * bBatch[i] * (i - filterDimensions[i].height + 1) * (i - filterDimensions[i].height + 1)
                         * filterDimensions[i].channel * filterDimensions[i].height * filterDimensions[i].width * 2;
        // Tensor1D
        Tensor1D<int> A(a_batch, inputDimensions[i].channel, inputDimensions[i].height, inputDimensions[i].width); 
        Tensor1D<int> B(bBatch[i], filterDimensions[i].channel, filterDimensions[i].height, filterDimensions[i].width);
        A.randomAssign(randomMax);
        B.randomAssign(randomMax);
        auto start = system_clock::now();
        Tensor1D<int> C = A.convolutionWithStride(B, strides[i]);
        auto end = system_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        double elapsed = double(duration.count()) * microseconds::period::num / microseconds::period::den;
        times1d.push_back(elapsed);
        gflops1d.push_back((operations / elapsed)/G);


        // Tensor 4D
        Tensor4D<int> M(a_batch, inputDimensions[i].channel, inputDimensions[i].height, inputDimensions[i].width); 
        Tensor4D<int> N(bBatch[i], filterDimensions[i].channel, filterDimensions[i].height, filterDimensions[i].width);
        M.randomAssign(randomMax);
        N.randomAssign(randomMax);
        start = system_clock::now();
        Tensor4D<int> O = M.convolutionWithStride(N, strides[i]);
        end = system_clock::now();
        duration = duration_cast<microseconds>(end - start);
        elapsed = double(duration.count()) * microseconds::period::num / microseconds::period::den;
        times4d.push_back(elapsed);
        gflops4d.push_back((operations/ elapsed)/G);

        cout<< "size " << i << " complete" << endl;
    }

    // plot runtime
    // the index starting from 1
    plt::figure(1);
    plt::named_plot("Tensor1D", sizes, times1d);
    plt::named_plot("Tensor4D", sizes, times4d);
    plt::title("Convs vs. Time Cost");
    plt::xlabel("Convs");
    plt::ylabel("Time Cost(s)");
    plt::legend(); 
    plt::grid(true);

    // plot GFLOPS
    plt::figure(2);
    plt::named_plot("Tensor1D", sizes, gflops1d);
    plt::named_plot("Tensor4D", sizes, gflops4d);
    plt::title("Convs vs. GFLOPS");
    plt::xlabel("Convs");
    plt::ylabel("GFLOPS(s)");
    plt::legend(); 
    plt::grid(true);

    plt::show();

    return 0;
}
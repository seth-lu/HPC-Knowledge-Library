#include "Tensor1D.h"
#include "Tensor4D.h"
#include "../include/matplotlibcpp.h"
#include <chrono>
using namespace std;
using namespace chrono;
namespace plt = matplotlibcpp;

int main() {

    const int64_t G = 1e9;
    const int64_t MAXSIZE = 5000;
    const int64_t a_batch = 1, a_channel = 3;
	const int64_t b_batch = 1, b_channel = 3, b_height = 3, b_width = 3;
    const int64_t m_batch = 1, m_channel = 3;
	const int64_t n_batch = 1, n_channel = 3, n_height = 3, n_width = 3;

    const Tensor1D<int> B(b_batch, b_channel, b_height, b_width);
    const Tensor4D<int> N(n_batch, n_channel, n_height, n_width);

    // performance vectors
    vector<int> sizes;
    vector<double> times1d;
    vector<double> gflops1d;
    vector<double> times4d;
    vector<double> gflops4d;

    // record time cost
    for(int i = 100; i <= MAXSIZE; i+=100) {
        sizes.push_back(i);
        // 2 flops per iteration
        int operations = a_batch * b_batch * (i - b_height + 1) * (i - b_height + 1)
                         * b_channel * b_height * b_width * 2;
        // Tensor1D
        Tensor1D<int> A(a_batch, a_channel, i, i); 
        auto start = system_clock::now();
        Tensor1D<int> C = A * B;
        auto end = system_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        double elapsed = double(duration.count()) * microseconds::period::num / microseconds::period::den;
        times1d.push_back(elapsed);
        gflops1d.push_back((operations / elapsed)/G);


        // Tensor 4D
        Tensor4D<int> M(m_batch, m_channel, i, i); 
        start = system_clock::now();
        Tensor4D<int> O = M * N;
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
    plt::title("Sizes vs. Time Cost");
    plt::xlabel("Tensor A's Height&Width");
    plt::ylabel("Time Cost(s)");
    plt::legend(); 
    plt::grid(true);

    // plot GFLOPS
    plt::figure(2);
    plt::named_plot("Tensor1D", sizes, gflops1d);
    plt::named_plot("Tensor4D", sizes, gflops4d);
    plt::title("Sizes vs. GFLOPS");
    plt::xlabel("Tensor A's Height&Width");
    plt::ylabel("GFLOPS(s)");
    plt::legend(); 
    plt::grid(true);

    plt::show();

    return 0;
}
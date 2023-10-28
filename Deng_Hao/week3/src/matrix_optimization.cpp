#include "../include/matplotlibcpp.h"
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
using namespace std;
using namespace chrono;
namespace plt = matplotlibcpp;

class Matrix {
public:
    Matrix(size_t M, size_t N)
        : num_rows_(M), num_cols_(N), storage_(num_rows_ * num_cols_) {}
    Matrix(size_t M, size_t N, double init)
        : num_rows_(M), num_cols_(N), storage_(num_rows_ * num_cols_, init) {}

    double &operator()(size_t i, size_t j) {
        return storage_[i * num_cols_ + j]; 
    }
    const double& operator()(size_t i, size_t j) const {
        return storage_[i * num_cols_ + j]; 
    }

    size_t num_rows() const { return num_rows_; }
    size_t num_cols() const { return num_cols_; }

    void zeroize() {
        for(size_t i = 0; i < num_rows_; ++i)
            for(size_t j = 0; j < num_cols_; ++j)
                storage_[i * num_cols_ + j] = 0;
    }

    void print() {
        for(int i = 0; i < num_rows_; ++i) {
            for(int j = 0; j < num_cols_; ++j) {
                cout << storage_[i * num_cols_ + j] << " ";
            }
        cout << endl;
        }
    }

    void randomAssign(int64_t max) {
        for(int i = 0; i < num_rows_; ++i)
            for(int j = 0; j < num_cols_; ++j)
                storage_[i * num_cols_ + j] = max * ( (double)rand() / (double)RAND_MAX );
    }

private:
    size_t num_rows_, num_cols_;
    vector<double> storage_;
};

// C = A * B
void multiply(const Matrix& A, const Matrix& B, Matrix& C) {
    for(size_t i = 0; i < A.num_rows(); ++i)
        for(size_t j = 0; j < B.num_cols(); ++j)
            for(size_t k = 0; k < A.num_cols(); ++k)
                C(i, j) += A(i, k) * B(k, j);
}

// Hoisting: C = A * B
void hoisting(const Matrix& A, const Matrix& B, Matrix& C) {
    for(size_t i = 0; i < A.num_rows(); ++i)
        for(size_t j = 0; j < B.num_cols(); ++j) {
            double t = C(i, j);
            for(size_t k = 0; k < A.num_cols(); ++k) {
                t += A(i, k) * B(k, j);
            }
            C(i, j) = t;
        }
}

// Unroll and Jam: C = A * B
void unrollAndJam(const Matrix& A, const Matrix& B, Matrix& C) {
    for(size_t i = 0; i < A.num_rows(); i += 2)
        for(size_t j = 0; j < B.num_cols(); j += 2)
            for(size_t k = 0; k < A.num_cols(); ++k) {
                C(i, j) += A(i, k) * B(k, j);
                C(i, j + 1) += A(i, k) * B(k, j + 1);
                C(i + 1, j) += A(i + 1, k) * B(k, j);
                C(i + 1, j + 1) += A(i + 1, k) * B(k, j + 1);
            }
}

// Tiling and Hoisting: C = A * B
void hoistedTiling(const Matrix& A, const Matrix&B, Matrix&C) {
    for (size_t i = 0; i < A.num_rows(); i += 2) {
        for (size_t j = 0; j < B.num_cols(); j += 2) {
            double t00 = C(i, j); double t01 = C(i, j + 1);
            double t10 = C(i+1, j); double t11 = C(i + 1, j + 1);
            for (size_t k = 0; k < A.num_cols(); ++k) {
                t00 += A(i , k) * B(k, j );
                t01 += A(i , k) * B(k, j + 1);
                t10 += A(i + 1, k) * B(k, j );
                t11 += A(i + 1, k) * B(k, j + 1);
            }
            C(i, j) = t00; C(i, j + 1) = t01;
            C(i + 1,j) = t10; C(i + 1,j + 1) = t11;
        }
    }
}

void experiment(vector<double>& times, vector<double>& gflops, const int64_t operations, const Matrix& A, 
    const Matrix&B, Matrix&C, function<void(const Matrix& A, 
    const Matrix&B, Matrix&C)> func) {
    auto start = system_clock::now();
    func(A, B, C);
    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    double elapsed = double(duration.count()) * microseconds::period::num / microseconds::period::den;
    times.push_back(elapsed);
    gflops.push_back((operations / elapsed) / 1e9);
}

int main() {
    
    // performance vectors
    vector<int> sizes;
    vector<double> multiplyTimes;
    vector<double> multiplyGflops;
    vector<double> hoistingTimes;
    vector<double> hoistingGflops;
    vector<double> unrollTimes;
    vector<double> unrollGflops;
    vector<double> hoistedTilingTimes;
    vector<double> hoistedTilingGflops;

    for(int64_t i = 2; i <= 2048; i *= 2) {
        sizes.push_back(i);
        // total float operations
        int64_t operations = i * i * i * 2;
        Matrix A(i, i), B(i, i), C(i, i);
        A.randomAssign(100);
        B.randomAssign(100);
        experiment(multiplyTimes, multiplyGflops, operations, A, B, C, &multiply);
        experiment(hoistingTimes, hoistingGflops, operations, A, B, C, &hoisting);
        experiment(unrollTimes, unrollGflops, operations, A, B, C, &unrollAndJam);
        experiment(hoistedTilingTimes, hoistedTilingGflops, operations, A, B, C, &hoistedTiling);
        cout << "size " << i << " complete" << endl;
    }

    // plot runtime
    // the index starting from 1
    plt::figure(1);
    plt::named_plot("Multiply", sizes, multiplyTimes);
    plt::named_plot("Hoisting", sizes, hoistingTimes);
    plt::named_plot("Unroll and Jam", sizes, unrollTimes);
    plt::named_plot("Tiling and Hoisting", sizes, hoistedTilingTimes);   
    plt::title("Sizes vs. Time Cost");
    plt::xlabel("Matrix Size (Height&Width)");
    plt::ylabel("Time Cost(s)");
    plt::legend(); 
    plt::grid(true);

    // plot GFLOPS
    plt::figure(2);
    plt::named_plot("Multiply", sizes, multiplyGflops);
    plt::named_plot("Hoisting", sizes, hoistingGflops);
    plt::named_plot("Unroll and Jam", sizes, unrollGflops);
    plt::named_plot("Tiling and Hoisting", sizes, hoistedTilingGflops); 
    plt::title("Sizes vs. GFLOPS");
    plt::xlabel("Matrix Size (Height&Width)");
    plt::ylabel("GFLOPS(s)");
    plt::legend(); 
    plt::grid(true);

    plt::show();

    return 0;

}

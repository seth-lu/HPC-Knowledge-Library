#include<iostream>
#include <chrono>
#include"Matrix.cpp"
#include"Timer.cpp"

using namespace std;

//未优化的举证乘法，C为输出矩阵
void multiply(const Matrix& A,const Matrix& B,Matrix& C){
    for(size_t i=0;i<C.num_rows();++i){
        for(size_t j=0;j<C.num_cows();++j){
            for(size_t k=0;k<A.num_cows();++k){
                C(i,j)+=A(i,k)*B(k,j);
            }
        }
    }
}

//把累加提到循环外面
void multiply_hoisting(const Matrix& A,const Matrix& B,Matrix& C){
    for(size_t i=0;i<C.num_rows();++i){
        for(size_t j=0;j<C.num_cows();++j){
            double t = C(i,j);
            for(size_t k=0;k<A.num_cows();++k){
                t+=A(i,k)*B(k,j);
            }
            C(i,j) = t;
        }
    }
}

//一次循环执行多个乘积累加
void multiply_tiled2x2(const Matrix& A,const Matrix& B,Matrix& C){
    for(size_t i=0;i<C.num_rows();i += 2){
        for(size_t j=0;j<C.num_cows();j += 2){
            for(size_t k=0;k<A.num_cows();++k){
                C(i,j)+=A(i,k)*B(k,j);
                C(i,j+1)+= A(i,k)*B(k,j+1);
                C(i+1,j)+=A(i+1,k)*B(k,j);
                C(i+1,j+1)+=A(i+1,k)*B(k,j+1);
            }
        }
    }
}
void multiply_tiled2x4(const Matrix& A,const Matrix& B,Matrix& C){
    for(size_t i=0;i<C.num_rows();i += 2){
        for(size_t j=0;j<C.num_cows();j += 4){
            for(size_t k=0;k<A.num_cows();++k){
                C(i,j)+=A(i,k)*B(k,j);
                C(i,j+1)+= A(i,k)*B(k,j+1);
                C(i,j+2)+=A(i,k)*B(k,j+2);
                C(i,j+3)+= A(i,k)*B(k,j+3);
                C(i+1,j)+=A(i+1,k)*B(k,j);
                C(i+1,j+1)+=A(i+1,k)*B(k,j+1);
                C(i+1,j+2)+=A(i+1,k)*B(k,j+2);
                C(i+1,j+3)+=A(i+1,k)*B(k,j+3);
            }
        }
    }
}
void multiply_tiled4x2(const Matrix& A,const Matrix& B,Matrix& C){
    for(size_t i=0;i<C.num_rows();i += 4){
        for(size_t j=0;j<C.num_cows();j += 2){
            for(size_t k=0;k<A.num_cows();++k){
                C(i,j)+=A(i,k)*B(k,j);
                C(i,j+1)+= A(i,k)*B(k,j+1);
                C(i+1,j)+=A(i+1,k)*B(k,j);
                C(i+1,j+1)+=A(i+1,k)*B(k,j+1);
                C(i+2,j)+=A(i+2,k)*B(k,j);
                C(i+2,j+1)+= A(i+2,k)*B(k,j+1);
                C(i+3,j)+=A(i+3,k)*B(k,j);
                C(i+3,j+1)+=A(i+3,k)*B(k,j+1);
            }
        }
    }
}
void multiply_tiled4x4(const Matrix& A,const Matrix& B,Matrix& C){
    for(size_t i=0;i<C.num_rows();i += 4){
        for(size_t j=0;j<C.num_cows();j += 4){
            for(size_t k=0;k<A.num_cows();++k){
                C(i,j)+=A(i,k)*B(k,j);
                C(i,j+1)+= A(i,k)*B(k,j+1);
                C(i,j+2)+=A(i,k)*B(k,j+2);
                C(i,j+3)+= A(i,k)*B(k,j+3);
                C(i+1,j)+=A(i+1,k)*B(k,j);
                C(i+1,j+1)+=A(i+1,k)*B(k,j+1);
                C(i+1,j+2)+=A(i+1,k)*B(k,j+2);
                C(i+1,j+3)+=A(i+1,k)*B(k,j+3);
                C(i+2,j)+=A(i+2,k)*B(k,j);
                C(i+2,j+1)+= A(i+2,k)*B(k,j+1);
                C(i+2,j+2)+=A(i+2,k)*B(k,j+2);
                C(i+2,j+3)+= A(i+2,k)*B(k,j+3);
                C(i+3,j)+=A(i+3,k)*B(k,j);
                C(i+3,j+1)+= A(i+3,k)*B(k,j+1);
                C(i+3,j+2)+=A(i+3,k)*B(k,j+2);
                C(i+3,j+3)+= A(i+3,k)*B(k,j+3);
            }
        }
    }
}

int main(){
    cout << "N\tElapsed" << endl;
    for(int N=32;N <= 2048;N*=2){
        Matrix A(N,N,1),B(N,N,1),C(N,N,0);

        Timer T;T.start();
        // multiply(A,B,C);
        // multiply_hoisting(A,B,C);
        // multiply_tiled2x2(A,B,C);
        // multiply_tiled2x4(A,B,C);
        // multiply_tiled4x2(A,B,C);
        multiply_tiled4x4(A,B,C);
        T.stop();

        cout << N << "\t" << T.elapsed() << endl;


        // for(size_t i=0;i<C.num_rows();++i){
        //     cout <<"\n";
        //     for(size_t j=0;j<C.num_cows();++j){
        //         cout<< C(i,j) << " ";
        //     }
        //     cout <<"\n";
        // }
    
    }

    
    

}
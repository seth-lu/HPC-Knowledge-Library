#include "../include/WeTensor.hpp"
#include "../include/Timer.h"
#include <vector>
using namespace std;



void directConvolution_weTensor( DTensor& input, DTensor& fiter,DTensor& output,int64_t s){
    double* inptr = input.getDataPtr();
    double* fitr = fiter.getDataPtr();
    double* outptr = output.getDataPtr();
    for (int64_t i = 0; i < output.batch_size; ++i){
        for (int64_t j = 0; j < output.channel; ++j) {
			//cout << "进行中" << endl;
			for (int64_t m = 0; m < output.height; ++m){
                for (int64_t n = 0; n < output.width; ++n){
                    for (int64_t r = 0; r < input.channel; ++r){
                        for (int64_t u = 0; u < fiter.height; ++u){
                            for (int64_t v = 0; v < fiter.width; ++v) {
                                // C(i, j, m, n) += (*this)(i, r, m * s + u, n * s + v) * B(j, r, u, v);
								outptr[i*output.channel*output.width*output.height + j*output.width*output.height + m*output.width + n] += 
                                inptr[i*input.channel*input.width*input.height + r*input.width*input.height + (m*s+u)*input.width + n*s+v]*
                                fitr[j*fiter.channel*fiter.width*fiter.height + r*fiter.width*fiter.height + u*fiter.width + v];
								//C.setTensors(i, j, m, n, (A(i, r, m + u, n + v) * B(j, r, u, v)));
							}
                        }
                    }
                }
            }
		}
    }

}

void printf_weTensor(DTensor& t){
    double *date = t.getDataPtr();
    for(int i=0;i<t.batch_size;++i){
        cout <<"第" << i+1 << "批次:" << endl;
        for(int j=0;j<t.channel;++j){
            cout <<"第" << j+1 << "通道:";
            for(int k=0;k<t.height;++k){
                cout <<"第" << k+1 << "行:";
                for(int l=0;l<t.width;++l){
                    cout << date[i * t.channel * t.height *  t.width + j * t.height *  t.width + k * t.width + l] << " ";
                }

            }

        }
        cout << endl;
    }

}

void set_weTensor(DTensor& t,double d){
    double *date = t.getDataPtr();
    for(int i=0;i<t.batch_size;++i){
        for(int j=0;j<t.channel;++j){
            for(int k=0;k<t.height;++k){
                for(int l=0;l<t.width;++l){
                    date[i * t.channel * t.height *  t.width + j * t.height *  t.width + k * t.width + l] = d++;
                }

            }

        }
        cout << endl;
    }
}

int main(){
    // Timer timer;
    // DTensor M(2,2,10,10);
    // M.initDataTensor();
    // timer.start();
    // printf_weTensor(M);
    // timer.stop();
    // cout << "time:" << timer.elapsed() << endl;
    
    int64_t a = 1,b= 2, c = 3;
    Timer timer;
    DTensor input((size_t)a,(size_t)b,(size_t)c,(size_t)c);
    DTensor fiter((size_t)a,(size_t)b,(size_t)b,(size_t)b);
    DTensor output((size_t)a,(size_t)a,(size_t)b,(size_t)b);
    input.initDataTensor();
    fiter.initDataTensor();
    output.setZeroTensor();
    set_weTensor(input,1);
    set_weTensor(fiter,1);

    printf_weTensor(input);
    printf_weTensor(fiter);
    printf_weTensor(output);

    directConvolution_weTensor(input,fiter,output,(int64_t)1);
    cout << "结果：" << endl;    
    printf_weTensor(output);
}
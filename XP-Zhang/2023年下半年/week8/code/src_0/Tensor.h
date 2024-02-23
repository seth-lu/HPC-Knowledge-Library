#ifndef TENSOR_H
#define TENSOR_H
#include <cstdint>
#include <iostream>
#include <random>

using namespace std;

template <typename T>//定义模板数据结构
class Tensor
{
protected:
    int64_t batch, channel, height, width;
public:
    //获取指定位置的元素
    virtual T &operator()(int64_t,int64_t,int64_t,int64_t) = 0;
    virtual const T &operator()(int64_t,int64_t,int64_t,int64_t)const = 0;
    //获取batch, channel, height,width;
    int64_t num_batch()const{ return batch;}
    int64_t num_channel()const{ return channel;}
    int64_t num_height()const{ return height;}
    int64_t num_width()const{ return width;}
    // Print Address
    void printAddress() {
        for(int i = 0; i < this->batch; ++i) {
            cout << "Batch " << i << endl;
            for(int j = 0; j < this->channel; ++j) {
                cout << "Channel " << j << endl;
                for(int m = 0; m < this->height; ++m) {
                    for(int n = 0; n < this->width; ++n) {
                        cout << &(*this)(i, j, m, n) << endl;
                    }
                    cout << endl;
                }
            }
        }
    }

    // Print out the tensor
    void print() {
        for(int i = 0; i < this->batch; ++i) {
            cout << "Batch " << i << endl;
            for(int j = 0; j < this->channel; ++j) {
                cout << "Channel " << j << endl;
                for(int m = 0; m < this->height; ++m) {
                    for(int n = 0; n < this->width; ++n) {
                        cout << (*this)(i, j, m, n) << " ";
                    }
                    cout << endl;
                }
            }
        }
    }
    
    // Fill the tensor with random number between 0 and max
    void randomAssign(int64_t max) {
        random_device engine;
        for (int64_t i = 0; i < this->batch; ++i)
            for (int64_t j = 0; j < this->channel; ++j)
                for (int64_t m = 0; m < this->height; ++m) 
                    for (int64_t n = 0; n < this->width; ++n)
                        (*this)(i, j, m, n) = abs((T)(engine() % max));
    }
    
};
#endif
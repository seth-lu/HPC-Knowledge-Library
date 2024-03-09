#pragma once
#include <cstdint>
template <typename T>//定义模板数据结构
class Tensor
{
protected:
    int64_t batch, channel, height, width;
public:
    //获取指定位置的元素
    virtual T& operator()(int64_t, int64_t, int64_t, int64_t) = 0;
    virtual const T& operator()(int64_t, int64_t, int64_t, int64_t)const = 0;
    //获取batch, channel, height,width;
    int64_t num_batch()const { return batch; }
    int64_t num_channel()const { return channel; }
    int64_t num_height()const { return height; }
    int64_t num_width()const { return width; }
};

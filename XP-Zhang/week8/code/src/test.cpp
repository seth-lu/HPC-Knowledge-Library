#include <torch/script.h>
#include <torch/torch.h>
#include <iostream>
int main() {
    std::cout << "检查CDUA是否可用：" << torch::cuda::is_available() << std::endl;
    std::cout << "检查cudnn是否可用：" << torch::cuda::cudnn_is_available() << std::endl;
    std::clock_t s, e;
    s = clock();
    torch::Tensor cuda_output;
    for (int i=0;i<1;i++) {
        cuda_output = torch::randn({ 5, 4 }, torch::device(torch::kCUDA));
    }
    std::cout << cuda_output << std::endl;
    e = clock();
    std::cout << "use time: " << (e - s) << " 微秒" << std::endl;
    return 0;
}



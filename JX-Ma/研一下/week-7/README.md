memory.xlsx --> 里面是我之前使用的测试方法和张新鹏测试方法内存分析

memory_t28.xlsx --> 里面是28个线程的静态调用，在一个Numa节点分配28个线程，还有正常分配28个线程的实验结果

memory_t56.xlsx --> 56个线程内存分析的结果，里面包含直接卷积和im2win卷积以及将他们batch和channel合并后的内存分析。

gflops.xlsx  --> 里面包含两个工作区间，t28是28个线程中跑静态调用Openmp，在numa分配28线程，正常28线程的结构，还有一个t56是直接卷积和im2win卷积以及将他们batch和channel合并后的gflops.

all_gflops.xlsx -->里面包含直接卷积和im2win卷积最好的结构以及im2col的结果。
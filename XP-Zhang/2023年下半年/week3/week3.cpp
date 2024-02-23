#include<iostream>
#include <chrono>

using namespace std;

class test_int{
    public:
      int i;
      test_int &operator++();
      int operator++(int);
};

test_int& test_int:: operator++(){
    i +=1;//增加
    return *this;//返回结果
}

int test_int:: operator++(int){
    int oldi = i;
    i +=1;//增加
    return oldi;//返回结果
}

int main(){
    test_int i;
    i.i = 0;

    auto beforeTime = chrono::steady_clock::now();
    for (int x=0;x<1000000000;++x){
        ++i.i;
        // cout << "i=" << ++i.i ;
    }
    auto afterTime = chrono::steady_clock::now();
    double time = chrono::duration<double, nano>(afterTime - beforeTime).count();
    cout << "\n使用++i总耗时:" << time << "纳秒";

    beforeTime = chrono::steady_clock::now();
    for (int x=0;x<1000000000;++x){
        i++;
        // cout << "i=" << i++ ;
    }
    afterTime = chrono::steady_clock::now();
    time = chrono::duration<double, nano>(afterTime - beforeTime).count();
    cout << "\n使用i++总耗时:" << time << "纳秒";
    /*
       ++i快，因为虽然i++和++i中的i都加了1，但是用++i赋值是增加后的i，i++是增加前的i。i++需要一个临时的变量来保存增加前的i，所以效率低一点
    */
}
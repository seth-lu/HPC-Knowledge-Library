#include <iostream>
#include <typeinfo>
#include<chrono>
#include"Timer.cpp"
#include <vector>
#include <cstdint>
#include <cfloat>

using namespace std;

template <typename T>//定义模板数据结构
//自定义类重载i++和++i
class OverloadT{
    protected:
      T valve;

    public:
      OverloadT(T t){  valve = t;}
      T get(){   return valve;}
      void set(T t){   valve = t;}
      T &operator++(){
        valve +=1;
        return valve;
      }
      T operator++(int){
        int valve_t = valve;
        valve +=1;
        return valve_t;
      }
};

template <typename T>
void testFunction(T data,int index) {
    cout << "测试数据结构：" << typeid(T).name() << endl;

    OverloadT<T>  number(data);

    Timer timer;timer.start();
    for (int i=0;i<index;++i){
        number++;
    }
    timer.stop();
    cout << "使用i++循环"<< index <<"次总耗时:" << timer.elapsed() << "毫秒,数字的值为:" << number.get()<<endl;

    number.set(data);
    timer.start();
    for (int i=0;i<index;++i){
        ++number;
    }
    timer.stop();
    cout << "\n使用++i循环"<< index <<"次总耗时:" << timer.elapsed() << "毫秒,数字的值为:" << number.get()<<endl;

}


int main(){
    //2000000
    //int32\_t、int64\_t、uint32\_t、uint64\_t、float、double
    int index = 100000000;//次数
    int32_t value_Int32 = 0;      // 声明int32_t类型变量
    int64_t value_Int64 = 0;      // 声明int64_t类型变量
    uint32_t value_UInt32 = 0;    // 声明uint32_t类型变量
    uint64_t value_UInt64 = 0;    // 声明uint64_t类型变量
    float value_Float = 0;        // 声明float类型变量
    double value_Double = 0;      // 声明double类型变量

    testFunction(value_Int32,index);
    testFunction(value_Int64,index);
    testFunction(value_UInt32,index);
    testFunction(value_UInt64,index);
    testFunction(value_Float,index);
    testFunction(value_Double,index);
}
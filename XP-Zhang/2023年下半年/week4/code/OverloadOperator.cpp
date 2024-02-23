#include<iostream>
#include <chrono>
using namespace std;

//不重载，直接用i++/++i循环
void directComparison(int index){
    int i=0;
    auto beforeTime = chrono::steady_clock::now();
    for (;i<index;i++){
    }
    auto afterTime = chrono::steady_clock::now();
    double time = chrono::duration<double, nano>(afterTime - beforeTime).count();
    cout << "使用i++循环"<< index <<"次总耗时:" << time << "纳秒,数字的值为:" << i;

    i=0;
    auto beforeTime2 = chrono::steady_clock::now();
    for (;i<index;++i){
    }
    auto afterTime2 = chrono::steady_clock::now();
    double time2 = chrono::duration<double, nano>(afterTime2 - beforeTime2).count();
    cout << "\n使用++i循环"<< index <<"次总耗时:" << time2 << "纳秒,数字的值为:" << i;

}

//整型。定义类重载i++和++i
class OverloadInt{
    protected:
      int valve;

    public:
      OverloadInt(int);
      int get();
      void set(int);
      int &operator++();
      int operator++(int);
};
OverloadInt::OverloadInt(int t){    valve = t;}
int OverloadInt::get(){    return valve;}
void OverloadInt:: set(int t){    valve = t;}
int & OverloadInt::operator++(){
    valve +=1;
    return valve;
}
int OverloadInt::operator++(int){
    int t = valve;
    valve +=1;
    return t;
}

//测试int，用重载后的类
void overloadIntComparison(int index){
    cout << "对比int";

    OverloadInt number(0); 
    auto beforeTime = chrono::steady_clock::now();
    for (int i=0;i<index;++i){
        number++;
    }
    auto afterTime = chrono::steady_clock::now();
    double time = chrono::duration<double, nano>(afterTime - beforeTime).count();
    cout << "\n使用i++循环"<< index <<"次总耗时:" << time << "纳秒,数字的值为:" << number.get();

    number.set(0);
    auto beforeTime2 = chrono::steady_clock::now();
    for (int i=0;i<index;++i){
        ++number;
    }
    auto afterTime2 = chrono::steady_clock::now();
    double time2 = chrono::duration<double, nano>(afterTime2 - beforeTime2).count();
    cout << "\n使用++i循环"<< index <<"次总耗时:" << time2 << "纳秒,数字的值为:" << number.get();
}

//浮点型。定义类重载i++和++i
class OverloadFloat{
    protected:
      float valve;

    public:
      OverloadFloat(float);
      float get();
      void set(float);
      float &operator++();
      float operator++(int);
};
OverloadFloat::OverloadFloat(float t){    valve = t;}
float OverloadFloat::get(){    return valve;}
void OverloadFloat:: set(float t){    valve = t;}
float & OverloadFloat::operator++(){
    valve +=1;
    return valve;
}
float OverloadFloat::operator++(int){
    float t = valve;
    valve +=1;
    return t;
}

//测试float，用重载后的类
void overloadFloatComparison(int index){
    cout << "对比float";

    OverloadFloat number(0); 
    auto beforeTime = chrono::steady_clock::now();
    for (int i=0;i<index;++i){
        number++;
    }
    auto afterTime = chrono::steady_clock::now();
    double time = chrono::duration<double, nano>(afterTime - beforeTime).count();
    cout << "\n使用i++循环"<< index <<"次总耗时:" << time << "纳秒,数字的值为:" << number.get();

    number.set(0);
    auto beforeTime2 = chrono::steady_clock::now();
    for (int i=0;i<index;++i){
        ++number;
    }
    auto afterTime2 = chrono::steady_clock::now();
    double time2 = chrono::duration<double, nano>(afterTime2 - beforeTime2).count();
    cout << "\n使用++i循环"<< index <<"次总耗时:" << time2 << "纳秒,数字的值为:" << number.get();
}

//双浮点型。定义类重载i++和++i
class OverloadDouble{
    protected:
      double valve;

    public:
      OverloadDouble(double);
      double get();
      void set(double);
      double &operator++();
      double operator++(int);
};
OverloadDouble::OverloadDouble(double t){    valve = t;}
double OverloadDouble::get(){    return valve;}
void OverloadDouble:: set(double t){    valve = t;}
double & OverloadDouble::operator++(){
    valve +=1;
    return valve;
}
double OverloadDouble::operator++(int){
    double t = valve;
    valve +=1;
    return t;
}

//测试double，用重载后的类
void overloadDoubleComparison(int index){
    cout << "对比double";

    OverloadDouble number(0); 
    auto beforeTime = chrono::steady_clock::now();
    for (int i=0;i<index;++i){
        number++;
    }
    auto afterTime = chrono::steady_clock::now();
    double time = chrono::duration<double, nano>(afterTime - beforeTime).count();
    cout << "\n使用i++循环"<< index <<"次总耗时:" << time << "纳秒,数字的值为:" << number.get();

    number.set(0);
    auto beforeTime2 = chrono::steady_clock::now();
    for (int i=0;i<index;++i){
        ++number;
    }
    auto afterTime2 = chrono::steady_clock::now();
    double time2 = chrono::duration<double, nano>(afterTime2 - beforeTime2).count();
    cout << "\n使用++i循环"<< index <<"次总耗时:" << time2 << "纳秒,数字的值为:" << number.get();
}

//长整型。定义类重载i++和++i
class OverloadLong{
    protected:
      long valve;

    public:
      OverloadLong(long);
      long get();
      void set(long);
      long &operator++();
      long operator++(int);
};
OverloadLong::OverloadLong(long t){    valve = t;}
long OverloadLong::get(){    return valve;}
void OverloadLong:: set(long t){    valve = t;}
long & OverloadLong::operator++(){
    valve +=1;
    return valve;
}
long OverloadLong::operator++(int){
    long t = valve;
    valve +=1;
    return t;
}

//测试long，用重载后的类
void overloadLongComparison(int index){
    cout << "对比long";

    OverloadLong number(0); 
    auto beforeTime = chrono::steady_clock::now();
    for (int i=0;i<index;++i){
        number++;
    }
    auto afterTime = chrono::steady_clock::now();
    double time = chrono::duration<double, nano>(afterTime - beforeTime).count();
    cout << "\n使用i++循环"<< index <<"次总耗时:" << time << "纳秒,数字的值为:" << number.get();

    number.set(0);
    auto beforeTime2 = chrono::steady_clock::now();
    for (int i=0;i<index;++i){
        ++number;
    }
    auto afterTime2 = chrono::steady_clock::now();
    double time2 = chrono::duration<double, nano>(afterTime2 - beforeTime2).count();
    cout << "\n使用++i循环"<< index <<"次总耗时:" << time2 << "纳秒,数字的值为:" << number.get();
}

//没符号的整型。定义类重载i++和++i
class OverloadUnsignedInt{
    protected:
      unsigned int valve;

    public:
      OverloadUnsignedInt(unsigned int);
      unsigned int get();
      void set(unsigned int);
      unsigned int &operator++();
      unsigned int operator++(int);
};
OverloadUnsignedInt::OverloadUnsignedInt(unsigned int t){    valve = t;}
unsigned int OverloadUnsignedInt::get(){    return valve;}
void OverloadUnsignedInt:: set(unsigned int t){    valve = t;}
unsigned int & OverloadUnsignedInt::operator++(){
    valve +=1;
    return valve;
}
unsigned int OverloadUnsignedInt::operator++(int){
    unsigned int t = valve;
    valve +=1;
    return t;
}

//测试unsigned int，用重载后的类
void overloadUnsignedIntComparison(int index){
    cout << "对比unsigned int";

    OverloadUnsignedInt number(0); 
    auto beforeTime = chrono::steady_clock::now();
    for (int i=0;i<index;++i){
        number++;
    }
    auto afterTime = chrono::steady_clock::now();
    double time = chrono::duration<double, nano>(afterTime - beforeTime).count();
    cout << "\n使用i++循环"<< index <<"次总耗时:" << time << "纳秒,数字的值为:" << number.get();

    number.set(0);
    auto beforeTime2 = chrono::steady_clock::now();
    for (int i=0;i<index;++i){
        ++number;
    }
    auto afterTime2 = chrono::steady_clock::now();
    double time2 = chrono::duration<double, nano>(afterTime2 - beforeTime2).count();
    cout << "\n使用++i循环"<< index <<"次总耗时:" << time2 << "纳秒,数字的值为:" << number.get();
}

int main(){
    //2000000000
    // directComparison(2000000000);
    // overloadIntComparison(2000000);
    // overloadFloatComparison(2000000);
    // overloadDoubleComparison(2000000);
    // overloadLongComparison(2000000);
    overloadUnsignedIntComparison(2000000);
}
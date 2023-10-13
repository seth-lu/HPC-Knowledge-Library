# 实验环境

cpu型号：Inter i5-9300H(2.4GHz)

操作系统：win10

编译器：gcc version 9.2.0 (MinGW.org GCC Build-2) （编译时优化等级为o0）

# for循环中比较i++和++i

测试代码

```c++
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
```

测试结果

第一次

![](笔记图片\1.png)

第二次

![](笔记图片\2.png)

第三次

![](笔记图片\3.png)

误差很大，效果不明显

# 通过函数int &operator++()和函数int operator++(int) 对比速度

## 对比整型

编写OverloadInt重载运算符

```c++
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
```

测试代码

```c++
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
```

结果

第一次

![](.\笔记图片\4.png)

第二次

![](.\笔记图片\5.png)

第三次

![](.\笔记图片\6.png)

效果比直接用循环明显的多

测试时第一次++i的比i++快了约18%，第二次++i的比i++快了约20%，第三次++i的比i++快了约21%

## 比较其他数据类型

循环2000000次

|                           | int      | float    | double   | long     | unsinged int |
| ------------------------- | -------- | -------- | -------- | -------- | ------------ |
| 第一次i++耗时             | 5.15512s | 5.51457s | 5.53748s | 5.18735s | 5.25454s     |
| 第一次++i耗时             | 4.21013s | 4.8618s  | 4.82121s | 4.32245s | 4.07352      |
| 第二次i++耗时             | 5.19237s | 5.50633s | 5.59334s | 5.28064s | 5.28678s     |
| 第二次++i耗时             | 4.13985s | 5.04861s | 4.83186s | 4.21859s | 4.07074s     |
| 第三次i++耗时             | 5.31382s | 5.77521s | 5.55272s | 5.3568s  | 5.15416s     |
| 第三次++i耗时             | 4.2119s  | 4.87158s | 4.95927s | 4.34393s | 4.06318s     |
| 平均i++耗时               | 5.2204s  | 5.599s   | 5.5612s  | 5.275s   | 5.2318s      |
| 平均++i耗时               | 4.1873s  | 4.927s   | 4.9273s  | 4.295s   | 4.0692s      |
| (++i耗时-i++耗时)/i++耗时 | 19.79%   | 12.00%   | 11.40%   | 18.58%   | 22.28%       |

分别循环1000000次和2000000次

|                                          | int     | float   | double  | long    | unsinged int |
| ---------------------------------------- | ------- | ------- | ------- | ------- | ------------ |
| 循环1000000次i++耗时                     | 2.6ms   | 2.984ms | 2.979ms | 2.993ms | 2.739ms      |
| 循环1000000次++i耗时                     | 1.996ms | 2.001ms | 2.035ms | 2.195ms | 1.994ms      |
| 循环1000000次，(++i耗时-i++耗时)/i++耗时 | 23.23%  | 32.94%  | 31.69%  | 26.66%  | 27.20%       |
| 循环2000000次i++耗时                     | 5.475ms | 5.387ms | 5.37ms  | 5.257ms | 5.078ms      |
| 循环2000000次++i耗时                     | 4.372ms | 5.036ms | 4.986ms | 4.266ms | 4.025ms      |
| 循环2000000次，(++i耗时-i++耗时)/i++耗时 | 20.15%  | 6.52%   | 7.15%   | 18.85%  | 20.74%       |

其他数据类型也是i++比++i慢，而且整型累加要比浮点型和双浮点型快，整型和长整型和无符号整型累加速度接近，浮点型和双浮点型累加速度接近。


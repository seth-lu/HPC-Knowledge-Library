#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

template <class T>
class Data{
    private:
        T _val;
        
    public: 
        Data(T t) : _val(t) {}
        T get() const { return _val;}
        Data& operator++() {
            _val += 1;
            return *this;
        }
        Data operator++(int) {
            Data temp = *this;
            ++*this;
            return temp;
        }
        Data& operator=(const Data& data) {
            if(this == &data) return *this;
            this->_val = data.get();
            return *this;
        }
        // void operator++() {
        //     _val += 1;
        // }
        // void operator++(int) {
        //     T temp = _val;
        //     temp += 1;
        //     _val = temp;
        // }
        // void operator=(const Data& data) {
        //     this->_val = data.get();
        // }
};

template <class T>
void incrementIteration(T data, int iterations) {
    cout << "Data type: " << typeid(T).name() << endl;
    Data<T> num(data);

    // postfix increment
    auto start = system_clock::now();
    for(int i = 0; i < iterations; ++i) num++;
    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Runtime for postfix increment: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << endl;

    // prefix increment
    num = data;
    start = system_clock::now();
    for(int i = 0; i < iterations; ++i) ++num;
    end = system_clock::now();
    duration = duration_cast<microseconds>(end - start);
    cout << "Runtime for prefix increment: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << endl;
}

int main() {
    // Initialization
    int32_t int32 = 0;
    int64_t int64 = 0;
    uint32_t uint32 = 0;
    uint64_t uint64 = 0;
    float f = 0.00;
    double d = 0.00;
    const int ITERATIONS = 2000000000;
    incrementIteration(int32, ITERATIONS);
    incrementIteration(int64, ITERATIONS);
    incrementIteration(uint32, ITERATIONS);
    incrementIteration(uint64, ITERATIONS);
    incrementIteration(f, ITERATIONS);
    incrementIteration(d, ITERATIONS);

    return 0;
}
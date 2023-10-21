#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

// Initialization
int32_t int32 = 0;
int64_t int64 = 0;
uint32_t uint32 = 0;
uint64_t uint64 = 0;
float f = 0.00;
double d = 0.00;
const int ITERATIONS = 2000000000;

void compare_int_32();
void compare_int_64();
void compare_uint_32();
void compare_uint_64();
void compare_float();
void compare_double();

int main() {
    cout << "int32_t" << endl;
    compare_int_32();
    cout << "int64_t" << endl;
    compare_int_64();
    cout << "uint32_t" << endl;
    compare_uint_32();
    cout << "uint_64" << endl;
    compare_uint_64();
    cout << "float" << endl;
    compare_float();
    cout << "double" << endl;
    compare_double();
 
    return 0;
}

    // Compare i++ and ++i on int32_t with 100000 iterations.
void compare_int_32() {
    // i++
    auto start = system_clock::now();
    for(int i = 0; i < ITERATIONS; i++) {
        int32++;
    }
    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "runtime for i++: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << endl;
    // ++i
    int32 = 0;
    start = system_clock::now();
    for(int i = 0; i < ITERATIONS; i++) {
        ++int32;
    }
    end = system_clock::now();
    duration = duration_cast<microseconds>(end - start);
    cout << "runtime for ++i: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << endl;
}

void compare_int_64() {
    // i++
    auto start = system_clock::now();
    for(int i = 0; i < ITERATIONS; i++) {
        int64++;
    }
    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "runtime for i++: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << endl;
    // ++i
    int64 = 0;
    start = system_clock::now();
    for(int i = 0; i < ITERATIONS; i++) {
        ++int64;
    }
    end = system_clock::now();
    duration = duration_cast<microseconds>(end - start);
    cout << "runtime for ++i: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << endl;
}

void compare_uint_32() {
    // i++
    auto start = system_clock::now();
    for(int i = 0; i < ITERATIONS; i++) {
        uint32++;
    }
    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "runtime for i++: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << endl;
    // ++i
    uint32 = 0;
    start = system_clock::now();
    for(int i = 0; i < ITERATIONS; i++) {
        ++uint32;
    }
    end = system_clock::now();
    duration = duration_cast<microseconds>(end - start);
    cout << "runtime for ++i: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << endl;
}

void compare_uint_64() {
    // i++
    auto start = system_clock::now();
    for(int i = 0; i < ITERATIONS; i++) {
        uint64++;
    }
    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "runtime for i++: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << endl;
    // ++i
    uint64 = 0;
    start = system_clock::now();
    for(int i = 0; i < ITERATIONS; i++) {
        ++uint64;
    }
    end = system_clock::now();
    duration = duration_cast<microseconds>(end - start);
    cout << "runtime for ++i: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << endl;
}

void compare_float() {
    // i++
    auto start = system_clock::now();
    for(int i = 0; i < ITERATIONS; i++) {
        f++;
    }
    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "runtime for i++: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << endl;
    // ++i
    f = 0.00;
    start = system_clock::now();
    for(int i = 0; i < ITERATIONS; i++) {
        ++f;
    }
    end = system_clock::now();
    duration = duration_cast<microseconds>(end - start);
    cout << "runtime for ++i: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << endl;
}
void compare_double() {
    // i++
    auto start = system_clock::now();
    for(int i = 0; i < ITERATIONS; i++) {
        d++;
    }
    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "runtime for i++: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << endl;
    // ++i
    d = 0.00;
    start = system_clock::now();
    for(int i = 0; i < ITERATIONS; i++) {
        ++d;
    }
    end = system_clock::now();
    duration = duration_cast<microseconds>(end - start);
    cout << "runtime for ++i: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << endl;
}
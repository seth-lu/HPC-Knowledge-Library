#include<chrono>
class Timer
{
private:
    typedef std::chrono::time_point<std::chrono::system_clock> time_t;
    time_t startTime,stopTime;
public:
    Timer() : startTime(),stopTime(){}

    time_t start() {return (startTime = std::chrono::system_clock::now());}
    time_t stop() {return (stopTime = std::chrono::system_clock::now());}

    double elapsed(){
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);
        double elapsed = double(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den;
        return elapsed;
    }
};
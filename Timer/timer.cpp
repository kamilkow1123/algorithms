#include<iostream>
#include<chrono>

using namespace std::chrono;

struct Timer
{
    
    high_resolution_clock::time_point start, end;
    duration<float> duration;

    Timer()
    {
        start = high_resolution_clock::now();
    }

    ~Timer(){}

    std::chrono::duration<float> getTime()
    {
        end = high_resolution_clock::now();
        duration = end - start;
        return duration;
    }
};
#include<iostream>
#include<chrono>

using namespace std::chrono;

struct Timer
{

    high_resolution_clock::time_point start, end;
    duration<float> duration;

    Timer()
    {
        start = high_resolution_clock::now(); //set the timer
    }

    ~Timer(){}

    std::chrono::duration<float> getTime()
    {
        end = high_resolution_clock::now(); //stop the timer
        duration = end - start; //count the duration based on the starting and ending times from the timer
        return duration; //return the duration
    }
};
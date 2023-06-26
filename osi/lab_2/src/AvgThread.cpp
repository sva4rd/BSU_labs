#include "..\include\AvgThread.h"
#include <thread>

AvgThread::AvgThread(const std::vector<double>& arr) : arr(arr) {}

void AvgThread::run()
{
    double sum = 0;
    for (auto x : arr) {
        sum += x;
        std::this_thread::sleep_for(std::chrono::milliseconds(12));
    }
    setAvg(sum / arr.size());
}

void AvgThread::setAvg(const double value)
{
    avgVal = value;
}

double AvgThread::getAvg() const
{
    return avgVal;
}

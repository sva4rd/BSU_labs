#include "../include/MinMaxThread.h"
#include <thread>

MinMaxThread::MinMaxThread(const std::vector<double>& arr) : arr(arr) {}

void MinMaxThread::run()
{
    for(int i = 0; i < arr.size(); i++)
    {
        if (arr[i] < minVal)
        {
            minVal = arr[i];
            minIdx = i;
        }
        else if (arr[i] > maxVal)
        {
            maxVal = arr[i];
            maxIdx = i;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(7));
    }
}

int MinMaxThread::getMinIdx() const
{
	return minIdx;
}

int MinMaxThread::getMaxIdx() const
{
	return maxIdx;
}

double MinMaxThread::getMin() const
{
	return minVal;
}

double MinMaxThread::getMax() const
{
	return maxVal;
}

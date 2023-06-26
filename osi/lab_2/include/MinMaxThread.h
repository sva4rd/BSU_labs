#pragma once
#include <vector>

class MinMaxThread
{
public:
    explicit MinMaxThread(const std::vector<double>& arr);
    void run();
    int getMinIdx() const;
    int getMaxIdx() const;
    double getMin() const;
    double getMax() const;

private:
    int minIdx = 0;
    int maxIdx = 0;
    double minVal = INT64_MAX;
    double maxVal = INT64_MIN;
    std::vector<double> arr;
};


#pragma once
#include <vector>
class AvgThread
{
public:
    explicit AvgThread(const std::vector<double>& arr);
    void run();
    void setAvg(const double value);
    double getAvg() const;

private:
    double avgVal = 0;
    std::vector<double> arr;
};


#include <iostream>
#include <thread>
#include <vector>
#include "../include/MinMaxThread.h"
#include "../include/AvgThread.h"

int main()
{
    std::cout << "Enter the size of the array: ";
    int size;
    std::cin >> size;

    std::vector<double> arr(size);
    std::cout << "Enter the array elements: ";
    for (int i = 0; i < size; i++)
        std::cin >> arr[i];

    auto minMaxObj = MinMaxThread(arr);
    auto avgObj = AvgThread(arr);

    std::thread MinMax(&MinMaxThread::run, &minMaxObj);
    MinMax.join();
    std::thread Avg(&AvgThread::run, &avgObj);
    Avg.join();

    std::cout << "\nAverage value: " << avgObj.getAvg();
    std::cout << "\nMin value: " << minMaxObj.getMin();
    std::cout << "\nMax value: " << minMaxObj.getMax();
    std::cout << "\nNew array: ";
    arr[minMaxObj.getMinIdx()] = avgObj.getAvg();
    arr[minMaxObj.getMaxIdx()] = avgObj.getAvg();
    std::cout << std::fixed;
    std::cout.precision(2);
    for (auto x : arr)
        std::cout << x << " ";
    std::cout << '\n';
    return 0;
}
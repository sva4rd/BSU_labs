#include "pch.h"
#include "../lab_3/AvgThread.h"
#include "../lab_3/MinMaxThread.h"
#include "../lab_3/AvgThread.cpp"
#include "../lab_3/MinMaxThread.cpp"

TEST(MinMaxTest, ValueTest) 
{
	std::vector<double> arr = { 1,2,3,4,5 };
	MinMaxThread thread(arr);
	thread.run();
	EXPECT_EQ(thread.getMin(), 1);
	EXPECT_EQ(thread.getMax(), 5);
}

TEST(MinMaxTest, IdxTest)
{
	std::vector<double> arr = { 14, -8, 43, 11, 42, 343, -5032, 23, 23, 89, 4567 };
	MinMaxThread thread(arr);
	thread.run();
	EXPECT_EQ(thread.getMinIdx(), 6);
	EXPECT_EQ(thread.getMaxIdx(), 10);
}

TEST(AvgTest, AvgValTest)
{
	std::vector<double> arr = { 14, -8, 43, 11, 42, 343, -5032, 23, 23, 89, 4567 };
	std::vector<double> arr2 = { 1,2,3,4,5 };
	AvgThread thread(arr);
	AvgThread thread2(arr2);
	thread.run();
	thread2.run();
	EXPECT_EQ(static_cast<double>(static_cast<int>(thread.getAvg()*100))/100, 10.45);
	EXPECT_EQ(thread2.getAvg(), 3);
}
#pragma once
#include <iostream>

class Strategy
{
public:
	Strategy() = default;
	virtual ~Strategy() = default;
	virtual void deliver(float cost, float speed, std::string rules);
};

class EconomyDelivery : public Strategy
{
public:
	void deliver(float cost, float speed, std::string rules) override;
};

class FastDelivery : public Strategy
{
public:
	void deliver(float cost, float speed, std::string rules) override;
};


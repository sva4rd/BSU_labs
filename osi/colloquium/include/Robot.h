#pragma once
#include <iostream>
#include "Strategy.h"

class Robot
{
private:
	float cost = 0;
	float maxSpeed = 0;
	std::string trafficRules;
protected:
	Strategy* orderType;
public:
	Robot() = default;
	virtual ~Robot() = default;
	virtual void deliver();
	virtual void setCost(float value);
	virtual void setMaxSpeed(float value);
	virtual void setTrafficRules(std::string value);
	virtual void setStrategy(Strategy* strategy);
	virtual float getCost();
	virtual float getMaxSpeed();
	virtual std::string getTrafficRules();
};

class Drone : public Robot
{
public:
	Drone();
};

class MiniCar : public Robot
{
public:
	MiniCar();
};

class DogRobot : public Robot
{
public:
	DogRobot();
};

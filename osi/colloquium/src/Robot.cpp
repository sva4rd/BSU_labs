#include "Robot.h"

void Robot::deliver()
{
	orderType->deliver(getCost(), getMaxSpeed(), getTrafficRules());
}

void Robot::setCost(float value)
{
	cost = value;
}

void Robot::setMaxSpeed(float value)
{
	maxSpeed = value;
}

void Robot::setTrafficRules(std::string value)
{
	trafficRules = value;
}

void Robot::setStrategy(Strategy* strategy)
{
	if (orderType != nullptr)
		delete orderType;
	orderType = strategy;
}

float Robot::getCost()
{
	return cost;
}


float Robot::getMaxSpeed()
{
	return maxSpeed;
}

std::string Robot::getTrafficRules()
{
	return trafficRules;
}

Drone::Drone()
{
	setCost(25);
	setMaxSpeed(90);
	setTrafficRules("Some drone rules");
}

MiniCar::MiniCar()
{
	setCost(15);
	setMaxSpeed(60);
	setTrafficRules("Some car rules");
}

DogRobot::DogRobot()
{
	setCost(20);
	setMaxSpeed(30);
	setTrafficRules("Some dog rules");
}

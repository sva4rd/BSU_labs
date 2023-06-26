#pragma once
#include "Robot.h"
class CountryFactory
{
public:
	CountryFactory() = default;
	virtual ~CountryFactory() = default;
	virtual Drone* createDrone();
	virtual MiniCar* createMiniCar();
	virtual DogRobot* createDogRobot();
};

class JapaneseFactory : public CountryFactory
{
public:
	Drone* createDrone() override;
	MiniCar* createMiniCar() override;
	DogRobot* createDogRobot() override;
	void japaneseSettings(Robot* robot);
};

class EuropeanFactory : public CountryFactory
{
public:
	Drone* createDrone() override;
	MiniCar* createMiniCar() override;
	DogRobot* createDogRobot() override;
	void europeanSettings(Robot* robot);
};

class ChineseFactory : public CountryFactory
{
public:
	Drone* createDrone() override;
	MiniCar* createMiniCar() override;
	DogRobot* createDogRobot() override;
	void chineseSettings(Robot* robot);
};


#include "CountryFactory.h"

Drone* CountryFactory::createDrone()
{
    return new Drone();
}

MiniCar* CountryFactory::createMiniCar()
{
    return new MiniCar();
}

DogRobot* CountryFactory::createDogRobot()
{
    return new DogRobot();
}

Drone* JapaneseFactory::createDrone()
{
    auto robot = new Drone();
    japaneseSettings(robot);
    return robot;
}

MiniCar* JapaneseFactory::createMiniCar()
{
    auto robot = new MiniCar();
    japaneseSettings(robot);
    return robot;
}

DogRobot* JapaneseFactory::createDogRobot()
{
    auto robot = new DogRobot();
    japaneseSettings(robot);
    return robot;
}

void JapaneseFactory::japaneseSettings(Robot* robot)
{
    robot->setCost(robot->getCost() * 1.2f);
    robot->setTrafficRules(robot->getTrafficRules() + "some japanese rules");
}

Drone* EuropeanFactory::createDrone()
{
    auto robot = new Drone();
    europeanSettings(robot);
    return robot;
}

MiniCar* EuropeanFactory::createMiniCar()
{
    auto robot = new MiniCar();
    europeanSettings(robot);
    return robot;
}

DogRobot* EuropeanFactory::createDogRobot()
{
    auto robot = new DogRobot();
    europeanSettings(robot);
    return robot;
}

void EuropeanFactory::europeanSettings(Robot* robot)
{
    robot->setCost(robot->getCost() * 1.3f);
    robot->setMaxSpeed(robot->getMaxSpeed() * 0.8f);
    robot->setTrafficRules(robot->getTrafficRules() + "some eu rules");
}

Drone* ChineseFactory::createDrone()
{
    auto robot = new Drone();
    chineseSettings(robot);
    return robot;
}

MiniCar* ChineseFactory::createMiniCar()
{
    auto robot = new MiniCar();
    chineseSettings(robot);
    return robot;
}

DogRobot* ChineseFactory::createDogRobot()
{
    auto robot = new DogRobot();
    chineseSettings(robot);
    return robot;
}

void ChineseFactory::chineseSettings(Robot* robot)
{
    robot->setCost(robot->getCost() * 1.5f);
    robot->setMaxSpeed(robot->getMaxSpeed() * 0.5f);
    robot->setTrafficRules(robot->getTrafficRules() + "some chinese rules");
}

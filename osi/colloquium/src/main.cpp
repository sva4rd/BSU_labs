#include <iostream>
#include "CountryFactory.h"

CountryFactory* getCountryID()
{
    std::cout << "Enter country id: ";
    int id;
    std::cin >> id;
    if (id == 1)
        return new JapaneseFactory();
    else if (id == 2)
        return new EuropeanFactory();
    else if (id == 3)
        return new ChineseFactory();
    else
        throw std::exception("\nError: Your country is not available for service\n");
}

int chooseRobot(Robot*& robot, CountryFactory* factory)
{
    int input;
    std::cout << "\nChoose your delivery robot:\n\t1) Drone\n\t2) Mini-car\n\t3) Robot-dog\n\t4)Exit\nEnter: ";
    std::cin >> input;
    if (input == 1)
        robot = factory->createDrone();
    else if (input == 2)
        robot = factory->createMiniCar();
    else if (input == 3)
        robot = factory->createDogRobot();
    else if (input == 4)
        return 0;
    else
    {
        std::cerr << "Error: Wrong input!\n";
        return -1;
    }
    return 1;
}

bool chooseType(Robot*& robot)
{
    int input;
    std::cout << "\nSelect delivery type:\n\t1)Economy\n\t2)Fast\nEnter: ";
    std::cin >> input;
    if (input == 1)
        robot->setStrategy(new EconomyDelivery());
    else if (input == 2)
        robot->setStrategy(new FastDelivery());
    else
    {
        std::cerr << "Error: Wrong input!\n";
        return false;
    }
    return true;
}

int main()
{
    CountryFactory* factory;
    try 
    {
        factory = getCountryID();
    }
    catch (std::exception& ex)
    {
        std::cerr << ex.what();
        return 0;
    }
    std::cout << "\nWelcome to Dijik Delivery Company!\n";
    int input;
    Robot* robot = nullptr;
    while (true)
    {
        input = chooseRobot(robot, factory);
        if (input == 0)
            break;
        if (input == -1 || !chooseType(robot))
            continue;
        robot->deliver();
    }

    delete robot;
    delete factory;

    return 0;
}


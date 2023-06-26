#include "Strategy.h"
#include <string>
#include <iostream>
#include <iomanip>

void Strategy::deliver(float cost, float speed, std::string rules)
{
	std::cerr << "\nError: No strategy\n";
}

void EconomyDelivery::deliver(float cost, float speed, std::string rules)
{
	float deliveryCost = cost;
	float deliverySpeed = speed / 2;
	std::string deliveryRules = rules + "some rules";
	std::cout << "\nEconomy delivery done (speed: ";
	std::cout << std::fixed << std::setprecision(2) << deliverySpeed;
	std::cout << ", price: ";
	std::cout << std::fixed << std::setprecision(2) << deliveryCost;
	std::cout << ")\n";
}

void FastDelivery::deliver(float cost, float speed, std::string rules)
{
	float deliveryCost = cost * 1.3;
	float deliverySpeed = speed;
	std::string deliveryRules = rules + "some rules";
	std::cout << "\nFast delivery done (speed: ";
	std::cout << std::fixed << std::setprecision(2) << deliverySpeed;
	std::cout << ", price: ";
	std::cout << std::fixed << std::setprecision(2) << deliveryCost;
	std::cout << ")\n";
}

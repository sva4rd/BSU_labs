#include "pch.h"
#include "../Colloquium/Robot.h"
#include "../Colloquium/CountryFactory.h"
#include "../Colloquium/Strategy.h"
#include "../Colloquium/Robot.cpp"
#include "../Colloquium/CountryFactory.cpp"
#include "../Colloquium/Strategy.cpp"

TEST(FactoryTest, JapaneseDroneCostTest) {
    CountryFactory* factory = new JapaneseFactory();
    Robot* robot = factory->createDrone();
    EXPECT_EQ(static_cast<int>(robot->getCost()), 30);
    delete robot;
    delete factory;
}

TEST(FactoryTest, EuropeanMiniCarMaxSpeedTest) {
    CountryFactory* factory = new EuropeanFactory();
    Robot* robot = factory->createMiniCar();
    EXPECT_EQ(static_cast<int>(robot->getMaxSpeed()), 48);
    delete robot;
    delete factory;
}

TEST(FactoryTest, ChineseRobotDogTest) {
    CountryFactory* factory = new ChineseFactory();
    Robot* robot = factory->createDogRobot();
    EXPECT_EQ(static_cast<int>(robot->getCost()), 30);
    EXPECT_EQ(static_cast<int>(robot->getMaxSpeed()), 15);
    delete robot;
    delete factory;
}

TEST(RobotTest, RobotSettersTest) {
    Robot robot = Robot();
    robot.setCost(10);
    robot.setMaxSpeed(10);
    robot.setTrafficRules("rules");
    EXPECT_EQ(static_cast<int>(robot.getCost()), 10);
    EXPECT_EQ(static_cast<int>(robot.getMaxSpeed()), 10);
    EXPECT_EQ(robot.getTrafficRules(), "rules");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
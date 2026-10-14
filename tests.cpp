#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "deliverySystem.h"

TEST_CASE("Rider vector initialised in correct order", 
          "[createRiders]") 
{
    DeliverySystem* testSystem = new DeliverySystem();
    REQUIRE(testSystem->getRiderList() == "Anne,Jim,Sue,Bill,James,Amy,Bob,Steve,");
    delete testSystem;
}

TEST_CASE("MopedRider constructs with correct attributes",
          "[MopedRider]")
{
    MopedRider* Test = new MopedRider("Test", 30);
    REQUIRE(Test->getName() == "Test");
    REQUIRE(Test->getSpeed() == 30);
    REQUIRE(Test->getVehicleType() == "Moped");
    REQUIRE(Test->getBusyUntil() == 0);
    REQUIRE(Test->getInQueue() == true);
    delete Test;
}

TEST_CASE("BicycleRider constructs with correct attributes",
          "[BicycleRider]")
{
    BicycleRider* Test = new BicycleRider("Test", 5, 20);
    REQUIRE(Test->getName() == "Test");
    REQUIRE(Test->getSpeed() == 5);
    REQUIRE(Test->getVehicleType() == "Bicycle");
    REQUIRE(Test->getBusyUntil() == 0);
    REQUIRE(Test->getInQueue() == true);
    REQUIRE(Test->getMaxMiles() == 20);
    REQUIRE(Test->getMilesTravelled() == 0);
    delete Test;
}

TEST_CASE("DeliveryRider initial queue status is true", 
          "[DeliveryRider]")
{
    MopedRider* Test = new MopedRider("Test", 25);
    REQUIRE(Test->getInQueue() == true);
    delete Test;
}

TEST_CASE("DeliveryRider queue status can be updated to false",
          "[DeliveryRider]")
{
    MopedRider* Test = new MopedRider("Test", 25);
    Test->updateQueueStatus(false);
    REQUIRE(Test->getInQueue() == false);
    delete Test;
}

TEST_CASE("DeliveryRider queue status can be toggled multiple times",
          "[DeliveryRider]")
{
    MopedRider* Test = new MopedRider("Test", 25);
    Test->updateQueueStatus(false);
    REQUIRE(Test->getInQueue() == false);
    Test->updateQueueStatus(true);
    REQUIRE(Test->getInQueue() == true);
    delete Test;
}

TEST_CASE("DeliveryRider initial busyUntil is 0",
          "[DeliveryRider]")
{
    MopedRider* Test = new MopedRider("Test", 25);
    REQUIRE(Test->getBusyUntil() == 0);
    delete Test;
}

TEST_CASE("DeliveryRider busyUntil can be updated", 
          "[DeliveryRider]")
{
    MopedRider* Test = new MopedRider("Test", 25);
    Test->updateBusyUntil(120.5);
    REQUIRE(Test->getBusyUntil() == 120.5);
    delete Test;
}

TEST_CASE("DeliveryRider busyUntil can be updated multiple times", 
          "[DeliveryRider]")
{
    MopedRider* Test = new MopedRider("Test", 25);
    Test->updateBusyUntil(100);
    Test->updateBusyUntil(200);
    REQUIRE(Test->getBusyUntil() == 200);
    delete Test;
}

TEST_CASE("BicycleRider initial miles travelled is 0 with correct mileLimitReached attribute",
          "[BicycleRider]")
{
    BicycleRider* Test = new BicycleRider("Test", 4, 20);
    REQUIRE(Test->getMilesTravelled() == 0);
    REQUIRE(Test->getMileLimitReached() == false);
    delete Test;
}

TEST_CASE("BicycleRider miles can be added", 
          "[BicycleRider]")
{
    BicycleRider* Test = new BicycleRider("Test", 4, 20);
    Test->addMiles(5.5);
    REQUIRE(Test->getMilesTravelled() == 5.5);
    delete Test;
}

TEST_CASE("BicycleRider multiple miles can be accumulated",
          "[BicycleRider]")
{
    BicycleRider* Test = new BicycleRider("Test", 4, 20);
    Test->addMiles(5);
    Test->addMiles(7.5);
    Test->addMiles(2.5);
    REQUIRE(Test->getMilesTravelled() == 15);
    delete Test;
}

TEST_CASE("BicycleRider mile limit can be reached",
         "[BicycleRider]")
{
    BicycleRider* Test = new BicycleRider("Test", 4, 20);
    Test->addMiles(20);
    Test->updateMileLimit();
    REQUIRE(Test->getMileLimitReached() == true);
    delete Test;
}

TEST_CASE("BicycleRider mile limit is updated properly",
          "[BicycleRider]")
{
    BicycleRider* Test = new BicycleRider("Test", 4, 20);
    Test->addMiles(15);
    REQUIRE(Test->getMileLimitReached() == false);
    Test->addMiles(5);
    Test->updateMileLimit();
    REQUIRE(Test->getMileLimitReached() == true);
    delete Test;
}

TEST_CASE("MopedRider resets correctly for new day", 
          "[DeliveryRider]")
{
    MopedRider* Test = new MopedRider("Test", 30);
    Test->updateBusyUntil(500);
    Test->updateQueueStatus(false);
    Test->resetForNewDay();
    REQUIRE(Test->getBusyUntil() == 0);
    REQUIRE(Test->getInQueue() == true);
    delete Test;
}

TEST_CASE("BicycleRider resets all attributes for new day", 
          "[BicycleRider]")
{
    BicycleRider* Test = new BicycleRider("Test", 4, 20);
    Test->addMiles(15);
    Test->updateBusyUntil(300);
    Test->updateQueueStatus(false);
    Test->updateMileLimit();
    Test->resetForNewDay();
    REQUIRE(Test->getMilesTravelled() == 0);
    REQUIRE(Test->getBusyUntil() == 0);
    REQUIRE(Test->getInQueue() == true);
    REQUIRE(Test->getMileLimitReached() == false);
    delete Test;
}

TEST_CASE("MopedRider has correct vehicle type",
          "[MopedRider]")
{
    MopedRider* Test = new MopedRider("Test", 30);
    REQUIRE(Test->getVehicleType() == "Moped");
}

TEST_CASE("checkDate correctly identifies if a line is a date using my logic",
          "[DeliverySystem]")
{
    DeliverySystem* testSystem = new DeliverySystem();
    REQUIRE(testSystem->checkDate("01/11/2025") == true);
    REQUIRE(testSystem->checkDate("06.09:0.64:Standard") == false);
    delete testSystem;
}

TEST_CASE("convertHours gets hours from line correctly", 
          "[DeliverySystem]")
{
    DeliverySystem* testSystem = new DeliverySystem();
    REQUIRE(testSystem->convertHours("06.09:0.64:Standard") == 6);
    REQUIRE(testSystem->convertHours("07.05:1.79:Standard") == 7);
    delete testSystem;
}

TEST_CASE("convertMinutes gets minutes from line correctly", 
          "[DeliverySystem]")
{
    DeliverySystem* testSystem = new DeliverySystem();
    REQUIRE(testSystem->convertMinutes("06.09:0.64:Standard") == 9);
    REQUIRE(testSystem->convertMinutes("07.05:1.79:Standard") == 5);
    REQUIRE(testSystem->convertMinutes("09.32:1.61:Standard") == 32);
    delete testSystem;
}

TEST_CASE("toMinutes converts to minutes from hours and minutes correctly",
          "[DeliverySystem]")
{
    DeliverySystem* testSystem = new DeliverySystem();
    REQUIRE(testSystem->toMinutes(1, 30) == 90);
    REQUIRE(testSystem->toMinutes(0, 30) == 30);
    REQUIRE(testSystem->toMinutes(1, 0) == 60);
    delete testSystem;
}

TEST_CASE("orderType identifies order types",
          "[DeliverySystem]")
{
    DeliverySystem* testSystem = new DeliverySystem();
    REQUIRE(testSystem->orderType("06.09:0.64:Standard") == "Standard");
    REQUIRE(testSystem->orderType("09.42:1.57:Priority") == "Priority");
    REQUIRE_FALSE(testSystem->orderType("09.32:1.61:Standard") == "Priority");
    delete testSystem;
}

TEST_CASE("convertDistance correctly gets distance from line",
          "[DeliverySystem]")
{
    DeliverySystem* testSystem = new DeliverySystem();
    REQUIRE(testSystem->convertDistance("06.09:0.64:Standard") == 0.64);
    REQUIRE(testSystem->convertDistance("09.42:1.57:Priority") == 1.57);
    REQUIRE_FALSE(testSystem->convertDistance("09.32:1.61:Standard") == 1);
    delete testSystem;
}

TEST_CASE("isMoped identifies moped rider correctly", 
          "[DeliverySystem]")
{
    DeliverySystem* testSystem = new DeliverySystem();
    MopedRider* Test = new MopedRider("Test", 30);
    REQUIRE(testSystem->isMoped(Test) == true);
    REQUIRE_FALSE(testSystem->isBicycle(Test) == true);
    delete Test;
    delete testSystem;
}

TEST_CASE("isBicycle identifies bike rider correctly", 
          "[DeliverySystem]")
{
    DeliverySystem* testSystem = new DeliverySystem();
    BicycleRider* Test = new BicycleRider("Test", 4, 20);
    REQUIRE(testSystem->isBicycle(Test) == true);
    REQUIRE_FALSE(testSystem->isMoped(Test) == true);
    delete Test;
    delete testSystem;
}

TEST_CASE("populateOrder creates correct Standard order struct",
          "[DeliverySystem]")
{
    DeliverySystem* testSystem = new DeliverySystem();
    Order* testOrder = testSystem->populateOrder("06.09:0.64:Standard");
    REQUIRE(testOrder->realTime == 369);
    REQUIRE(testOrder->distance == 0.64);
    REQUIRE(testOrder->orderType == "Standard");
    delete testOrder;
    delete testSystem;
}

TEST_CASE("populateOrder creates correct Priority order struct",
          "[DeliverySystem]")
{
    DeliverySystem* testSystem = new DeliverySystem();
    Order* testOrder = testSystem->populateOrder("08.22:0.64:Priority");
    REQUIRE(testOrder->realTime == 502);
    REQUIRE(testOrder->distance == 0.64);
    REQUIRE(testOrder->orderType == "Priority");
    delete testOrder;
    delete testSystem;
}

TEST_CASE("riderBusy calculates correctly",
          "[DeliverySystem]")
{
    DeliverySystem* testSystem = new DeliverySystem();
    BicycleRider* testB = new BicycleRider("Test", 4, 20);
    MopedRider* testM = new MopedRider("Test", 30);
    Order* testOrder = testSystem->populateOrder("08.22:0.64:Priority");
    testSystem->riderBusy(testB, testOrder);
    testSystem->riderBusy(testM, testOrder);
    REQUIRE(testB->getBusyUntil() == 521.2);
    REQUIRE(testM->getBusyUntil() == 504.56);
    delete testM;
    delete testB;
    delete testOrder;
    delete testSystem;
}

TEST_CASE("updateRiderAvailability makes rider available after busy period",
          "[DeliverySystem]")
{
    DeliverySystem* testSystem = new DeliverySystem();
    std::vector<DeliveryRider*> queue;
    std::vector<DeliveryRider*> unavailable;
    MopedRider* Test = new MopedRider("Test", 30);
    Test->updateBusyUntil(100);
    Test->updateQueueStatus(false);
    unavailable.push_back(Test);
    testSystem->updateRiderAvailability(150, queue, unavailable); 
    REQUIRE(queue.size() == 1);
    REQUIRE(unavailable.size() == 0);
    REQUIRE(Test->getInQueue() == true);
    delete Test;
    delete testSystem;
}

TEST_CASE("processOrder handles standard order with bicycle rider successfully",
          "[DeliverySystem]")
{
    DeliverySystem* testSystem = new DeliverySystem();
    std::vector<DeliveryRider*> queue;
    std::vector<DeliveryRider*> unavailable;
    Day* testDay = new Day {0, 0.0, 0, 0.0, 0, 0.0, 0};
    BicycleRider* Test = new BicycleRider("Test", 4, 20);
    queue.push_back(Test);
    Order* testOrder = new Order {600, 1.5, "Standard"};
    int result = testSystem->processOrder(testOrder, queue,
        unavailable, *testDay);
    REQUIRE(result == 1);
    REQUIRE(testDay->deliveriesCompleted == 1);
    REQUIRE(testDay->bicycleDeliveries == 1);
    REQUIRE(testDay->bicycleMoney == 2.0);
    REQUIRE(testDay->totalMoneyEarned == 2.0);
    REQUIRE(Test->getMilesTravelled() == 3.0);
    REQUIRE(queue.size() == 0);
    REQUIRE(unavailable.size() == 1);
    delete testSystem;
    delete testDay;
    delete testOrder;
    delete Test;
}

TEST_CASE("processOrder handles Priority order with Moped rider successfully",
          "[DeliverySystem]")
{
    DeliverySystem* testSystem = new DeliverySystem();
    std::vector<DeliveryRider*> queue;
    std::vector<DeliveryRider*> unavailable;
    Day* testDay = new Day {0, 0.0, 0, 0.0, 0, 0.0, 0};
    MopedRider* Test = new MopedRider("Test", 30);
    queue.push_back(Test);
    Order* testOrder = new Order {600, 1.5, "Priority"};
    int result = testSystem->processOrder(testOrder, queue,
        unavailable, *testDay);
    REQUIRE(result == 1);
    REQUIRE(testDay->deliveriesCompleted == 1);
    REQUIRE(testDay->mopedDeliveries == 1);
    REQUIRE(testDay->mopedMoney == 3.0);
    REQUIRE(testDay->totalMoneyEarned == 3.0);
    REQUIRE(queue.size() == 0);
    REQUIRE(unavailable.size() == 1);
    delete testSystem;
    delete testDay;
    delete testOrder;
    delete Test;
}

TEST_CASE("processOrder returns 0 for Priority order when Bicycle takes order",
          "[DeliverySystem]")
{
    DeliverySystem* testSystem = new DeliverySystem();
    std::vector<DeliveryRider*> queue;
    std::vector<DeliveryRider*> unavailable;
    Day* testDay = new Day {0, 0.0, 0, 0.0, 0, 0.0, 0};
    BicycleRider* Test = new BicycleRider("Test", 4, 20);
    queue.push_back(Test);
    Order* testOrder = new Order {600, 1.5, "Priority"};
    int result = testSystem->processOrder(testOrder,
        queue, unavailable, *testDay);
    REQUIRE(result == 0); // 0 = missed
    REQUIRE(queue.size() == 1);
    REQUIRE(unavailable.size() == 0);
    delete testSystem;
    delete testDay;
    delete testOrder;
    delete Test;
}

TEST_CASE("processOrder missed order if exceeds 2 miles and is Bicycle",
         "[DeliverySystem]")
{
    DeliverySystem* testSystem = new DeliverySystem();
    std::vector<DeliveryRider*> queue;
    std::vector<DeliveryRider*> unavailable;
    Day* testDay = new Day {0, 0.0, 0, 0.0, 0, 0.0, 0};
    BicycleRider* Test = new BicycleRider("Test", 4, 20);
    queue.push_back(Test);
    Order* testOrder = new Order {600, 2.5, "Standard"};
    int result = testSystem->processOrder(testOrder, queue,
        unavailable, *testDay);
    REQUIRE(result == 0);
    REQUIRE(queue.size() == 1);
    REQUIRE(unavailable.size() == 0);
    delete testSystem;
    delete testDay;
    delete testOrder;
    delete Test;
}

TEST_CASE("writeDaySummary creates file with correct content",
          "[DeliverySystem]")
{
    DeliverySystem* testSystem = new DeliverySystem();
    Day* testDay = new Day {10, 25.0, 4, 8.0, 6, 17.0, 5};
    testSystem->writeDaySummary("01012025", *testDay);
    std::ifstream file("01012025.dat");
    std::string line;
    std::getline(file, line);
    REQUIRE(line == "Total deliveries: 10");
    std::getline(file, line);
    REQUIRE(line == "Total money: 25");
    std::getline(file, line);
    REQUIRE(line == "Bicycle deliveries: 4");
    std::getline(file, line);
    REQUIRE(line == "Bicycle money: 8");
    std::getline(file, line);
    REQUIRE(line == "Moped deliveries: 6");
    std::getline(file, line);
    REQUIRE(line == "Moped money: 17");
    std::getline(file, line);
    REQUIRE(line == "Missed orders: 5");
    std::remove("01012025.dat");
}

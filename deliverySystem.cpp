/*
  deliverySystem.cpp
  Author: Lewis Nixon <ln23aac@herts.ac.uk>
  Created: 20/11/2025
  Updated: 03/01/2025
*/

#include "deliverySystem.h"

DeliverySystem::DeliverySystem()
{
  allRiders = createRiders();
}

void DeliverySystem::writeDaySummary(const std::string& dateDigits, 
const Day& day)
{
  std::string fileName = dateDigits + ".dat";
  std::ofstream out(fileName);
  out << "Total deliveries: " << day.deliveriesCompleted << '\n';
  out << "Total money: " << day.totalMoneyEarned << '\n';
  out << "Bicycle deliveries: " << day.bicycleDeliveries << '\n';
  out << "Bicycle money: " << day.bicycleMoney << '\n';
  out << "Moped deliveries: " << day.mopedDeliveries << '\n';
  out << "Moped money: " << day.mopedMoney << '\n';
  out << "Missed orders: " << day.missedOrders << '\n';
}

//Helper function
bool DeliverySystem::isMoped(DeliveryRider* rider) 
{
  return rider->getVehicleType() == "Moped";
}

//Helper function
bool DeliverySystem::isBicycle(DeliveryRider* rider) 
{
  return rider->getVehicleType() == "Bicycle";
}

//Helper function
bool DeliverySystem::priority(Order* currentOrder) 
{
  return currentOrder->orderType == "Priority";
}

//Checks if the line being read is a date (dates contain /)
bool DeliverySystem::checkDate(const std::string& line) 
{
    return line.find('/') != std::string::npos;
}

//Helper function
double DeliverySystem::convertDistance(std::string line) 
{ 
  double distance;
  if (line[9] == ':')
  {
    distance = std::stod(line.substr(6,3));
    return distance;
  }
  else
  {
    distance = std::stod(line.substr(6,4));
    return distance;
  }
}

//Helper function
int DeliverySystem::convertHours(std::string line) 
{ 
  int hours;
  hours = std::stoi(line.substr(0,2));
  return hours;
}

//Helper function
int DeliverySystem::convertMinutes(std::string line) 
{ 
  int minutes;
  minutes = std::stoi(line.substr(3,2));
  return minutes;
}

//Helper function
int DeliverySystem::toMinutes(int hours, int minutes)
{
  int convertedTime;
  convertedTime = hours * 60 + minutes;
  return convertedTime;
}

//Helper function
std::string DeliverySystem::orderType(std::string line) 
{
  if (line.find('S') != std::string::npos)
    return "Standard";
  else
    return "Priority";
}

//Set rider busy time (delivery time + current time)
void DeliverySystem::riderBusy(DeliveryRider* rider, Order* currentOrder) 
{
  double totalDistance = currentOrder->distance * 2;
  double tripTime = totalDistance / rider->getSpeed();
  double tripMinutes = tripTime * 60;
  double driverAvailableAfter = currentOrder->realTime + tripMinutes;
  rider->updateBusyUntil(driverAvailableAfter);
}

//Populates order struct with current line information
Order* DeliverySystem::populateOrder(const std::string& line) 
{
  Order* currentOrder = new Order();
  int hours = convertHours(line);
  int minutes = convertMinutes(line);
  double distance = convertDistance(line);
  std::string type = orderType(line);
  currentOrder->realTime = toMinutes(hours, minutes);
  currentOrder->distance = distance;
  currentOrder->orderType = type;
  return currentOrder;
}

//Update whether a rider is available just before we check for order
void DeliverySystem::updateRiderAvailability(int currentTime, 
std::vector<DeliveryRider*>& queue,
std::vector<DeliveryRider*>& unavailableRiders) 
{
  unsigned i = 0;
  while(i < unavailableRiders.size())
  {
    DeliveryRider* rider = unavailableRiders[i];
    if(!rider->getInQueue() && !rider->getMileLimitReached() 
    && rider->getBusyUntil() <= currentTime)
    {
      rider->updateQueueStatus(true);
      queue.push_back(rider);
      unavailableRiders.erase(unavailableRiders.begin()+i);
    }
    else
    {
      i++;
    }
  }
}

//Find rider for order and execute correct maths for statistics of Day
int DeliverySystem::processOrder(Order* currentOrder,
std::vector<DeliveryRider*>& queue,
std::vector<DeliveryRider*>& unavailableRiders, Day& day) 
{
  double tripDistance = currentOrder->distance * 2;
  updateRiderAvailability(currentOrder->realTime, queue, unavailableRiders);
  bool isPriority = priority(currentOrder);
  for (unsigned i = 0; i < queue.size(); ++i)
  {
    DeliveryRider* rider = queue[i];
    if (isPriority && isBicycle(rider))
      continue;
    if (isBicycle(rider))
    {
      if(currentOrder->distance > 2)
        continue;
      double checkMileLimit = rider->getMilesTravelled() + tripDistance;
      if (checkMileLimit > rider->getMaxMiles())
        continue;
      rider->addMiles(tripDistance);
      if (rider->getMilesTravelled() == rider->getMaxMiles())
        rider->updateMileLimit();
    }

    double fare;
    if(isPriority)
      fare = 3;
    else
      fare = 2;
    
    if (isBicycle(rider))
    {
      day.bicycleDeliveries++;
      day.bicycleMoney += fare;
    }
    else if (isMoped(rider))
    {
      day.mopedDeliveries++;
      day.mopedMoney += fare;
    }
    day.totalMoneyEarned += fare;
    day.deliveriesCompleted++;
    rider->updateQueueStatus(false);
    riderBusy(rider, currentOrder);
    unavailableRiders.push_back(rider);
    queue.erase(queue.begin() + i);
    return 1;
  }
  return 0;
}

std::vector<DeliveryRider*> DeliverySystem::createRiders()
{
  std::vector<DeliveryRider*> riders;

  riders.push_back(new MopedRider("Anne", 32));
  riders.push_back(new MopedRider("Jim", 28));
  riders.push_back(new BicycleRider("Sue", 4, 23));
  riders.push_back(new BicycleRider("Bill", 5, 17));
  riders.push_back(new MopedRider("James", 25));
  riders.push_back(new MopedRider("Amy", 24));
  riders.push_back(new MopedRider("Bob", 27));
  riders.push_back(new BicycleRider("Steve", 3, 21));

  return riders;
}

void DeliverySystem::newDay(std::vector<DeliveryRider*>& riders,
std::vector<DeliveryRider*>& unavailableRiders,
std::vector<DeliveryRider*>& queue)                               
{
  queue.clear();
  unavailableRiders.clear();

  for(DeliveryRider* rider : riders)
  {
    rider->resetForNewDay();
    queue.push_back(rider);
  }
}



void DeliverySystem::run(std::ifstream& inputFile)
{
  std::string line;
  bool dayPassed = false;
  std::string currentFileDate;
  /*Iterate through file line by line checking for
  if Date line or not and performing function to complete order.*/
  while (std::getline(inputFile, line))
  {
    if (checkDate(line))
    {
      std::string dateDigits;
      for(char c: line)
      {
        if (c != '/')
          dateDigits.push_back(c);
      }
      if (dayPassed)
      {
        writeDaySummary(currentFileDate, currentDay);
      }
      dayPassed = true;
      currentFileDate = dateDigits;
      currentDay = Day{};
      newDay(allRiders, unavailableRiders, queue);
    }
    else
    {
      Order* order = populateOrder(line);
      if(processOrder(order, queue, unavailableRiders, currentDay) == 0)
        //increment missedOrder's is processOrder returns 0 (rider not found)
        currentDay.missedOrders++; 
        //Delete order's structs after use
      delete order; 
    }
  }
  //Last day will not be updated through while loop due to end of file
  if (dayPassed) writeDaySummary(currentFileDate, currentDay); 
  
  for (DeliveryRider* i : allRiders) //Free memory from objects
  {
    delete i;
  }
  allRiders.clear();
}

//testing functions

std::string DeliverySystem::getRiderList()
{
  std::string list = "";
  for (unsigned i = 0; i < allRiders.size(); ++i)
  {
    list += allRiders[i]->getName();
    list += ",";
  }
  return list;
}
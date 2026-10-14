/*
  deliveryRiders.cpp
  Author: Lewis Nixon <ln23aac@herts.ac.uk>
  Created: 20/11/2025
  Updated: 27/11/2025
*/

#include "deliveryRiders.h"
#include <iostream>
#include <string>

DeliveryRider::DeliveryRider (std::string name, int speed)
{
  this -> name = name;
  this -> speed = speed;
  this -> busyUntil = 0;
  this -> inQueue = true;
}

//Getters

bool DeliveryRider::getMileLimitReached()
{
  return mileLimitReached;
}

double DeliveryRider::getBusyUntil()
{
  return busyUntil;
}

std::string DeliveryRider::getName() const
{
  return name;
}

int DeliveryRider::getSpeed() const
{
  return speed;
}

std::string DeliveryRider::getVehicleType() const
{
  return vehicle;
}

double DeliveryRider::getMilesTravelled()
{
  return 0;
}

bool DeliveryRider::getInQueue()
{
  return inQueue;
}

//mutators

void DeliveryRider::updateBusyUntil(double tripTime)
{
  busyUntil = tripTime;
}

void DeliveryRider::addMiles(double miles)
{
  milesTravelled += miles;
}

int DeliveryRider::getMaxMiles() const
{
  return 0;
}

void DeliveryRider::updateMileLimit()
{
  mileLimitReached = true;
}

void DeliveryRider::resetForNewDay()
{
  busyUntil = 0;
  inQueue= true;
  mileLimitReached = false;
  milesTravelled = 0;
}

void DeliveryRider::updateQueueStatus(bool queueStatus)
{
  inQueue = queueStatus;
}

MopedRider::MopedRider (std::string name, int speed) : DeliveryRider(name,speed)
{
  this -> vehicle = "Moped";
}

BicycleRider::BicycleRider (std::string name, int speed, int maxMiles) 
: DeliveryRider(name,speed)
{
  this -> vehicle = "Bicycle";
  this -> maxMiles = maxMiles;
  this -> milesTravelled = 0;
  this -> mileLimitReached = false;
}

int BicycleRider::getMaxMiles() const
{
  return maxMiles;
}

bool BicycleRider::getMileLimitReached()
{
  return mileLimitReached;
}

double BicycleRider::getMilesTravelled()
{
  return milesTravelled;
}
/*
  deliveryRiders.h
  Author: Lewis Nixon <ln23aac@herts.ac.uk>
  Created: 20/11/2025
  Updated: 03/01/2025
*/

#ifndef _RIDERS_H_
#define _RIDERS_H_
#include <string>

class DeliveryRider
{
protected:
  std::string name;
  int speed;
  std::string vehicle;
  double busyUntil;
  bool inQueue;
  bool mileLimitReached;
  double milesTravelled;
public:
  /**
    Constructs a DeliveryRider with the given name and speed
    @param name The name of the delivery rider
    @param speed The speed of the delivery rider
   */
  DeliveryRider(std::string name, int speed);

  /**
    Default destructor
   */
  virtual ~DeliveryRider() = default;

  /**
    Default copy constructor
   */
  DeliveryRider(const DeliveryRider& other) = default;

  /**
    Default move constructor
    @param other The DeliveryRider to move from
   */
  DeliveryRider(DeliveryRider && other) = default;

  /**
    Default copy assignment operator
    @param other The DeliveryRider to copy from
    @return Reference to this DeliveryRider
   */
  DeliveryRider& operator = (const DeliveryRider& other) = default;

  /**
    Default move assignment operator
    @param other The DeliveryRider to move from
    @return Reference to this DeliveryRider
   */
  DeliveryRider& operator = (DeliveryRider& other) = default;

  /**
    Gets the name attribute of DeliveryRider object
    @return String of the name attribute
   */
  std::string getName() const;

  /**
    Gets the speed attribute of DeliveryRider object
    @return Integer of the speed attribute
   */
  int getSpeed() const;

  /**
    Gets the Vehicle Type of DeliveryRider object
    @return String of Vehicle type
   */
  std::string getVehicleType() const;

  /**
    Gets the milesTravelled attribute of DeliveryRider object
    @return Double value of the milesTravelled attribute
   */
  virtual double getMilesTravelled();

  /**
    Gets the busyUntil attribute of DeliveryRider object
    @return Double value of the busyUntil attribute
   */
  double getBusyUntil();

  /**
    Gets the inQueue attribute of DeliveryRider object
    @return boolean value of the inQueue attribute
   */
  bool getInQueue();

  /**
    Gets a boolean value attribute based on whether or not the DeliveryRiders mile limit is reached
    @return boolean value of whether or not mile limit is reached
   */
  virtual bool getMileLimitReached();

  /**
    Adds miles to DeliveryRider objects milesTravelled attribute
    @param miles value of miles which should be added
   */
  void addMiles(double miles);

  /**
    Updates whether or not it's true that DeliveryRider is in the queue
    @param queueStatus boolean value of the queue status
   */
  void updateQueueStatus(bool queueStatus);

  /**
    Resets a riders daily milesTravelled and queue status
   */
  void resetForNewDay();

  /**
    Updates the busyUntil attribute so that we can determine when a Rider is busy until,
    time measured in minutes from midnight
    @param tripTime The minutes from midnight value that the driver is busy until
   */
  void updateBusyUntil(double tripTime);

  /**
    Updates whether or not it's true that DeliveryRider has reached their daily mile limit
   */
  void updateMileLimit();

  /**
    Gets maxMiles attribute of a DeliveryRider, only defined in Bicycle sub-classes but defined here
    for polymorphism
    @return integer value of the maxMiles attribute
   */
  virtual int getMaxMiles() const;

};

class BicycleRider : public DeliveryRider
{
private:
  int maxMiles;
public:
  /**
    Constructs a BicycleRider derives class object
    @param name The name of the BicycleRider
    @param speed The speed of the BicycleRider
    @param maxMiles The maximum miles a BicycleRider can travel in a day
   */
  BicycleRider(std::string name, int speed, int maxMiles);

  /**
    Gets maxMiles attribute of a BicycleRider, how many miles a BicycleRider can travel in 1 day
    @return integer value of the maxMiles attribute
   */
  int getMaxMiles() const;

  /**
    Gets a boolean value attribute based on whether or not the DeliveryRiders mile limit is reached
    @return boolean value of whether or not mile limit is reached
   */
  bool getMileLimitReached();

  /**
    Gets the milesTravelled attribute of DeliveryRider object
    @return Double value of the milesTravelled attribute
   */
  double getMilesTravelled();
};

class MopedRider : public DeliveryRider
{
public:
/**
    Constructs a MopedRider derives class object
    @param name The name of the MopedRider
    @param speed The speed of the MopedRider
   */
  MopedRider(std::string name, int speed);
};

#endif

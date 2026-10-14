/*
  deliverySystem.h
  Author: Lewis Nixon <ln23aac@herts.ac.uk>
  Created: 20/11/2025
  Updated: 03/01/2025
*/

#include "deliveryRiders.h"
#include <string>
#include <vector>
#include <fstream>
#ifndef DELIVERY_SYSTEM_H
#define DELIVERY_SYSTEM_H


/**
    Represents information about a single order
 */
struct Order
{   
    int realTime; 
    double distance; 
    std::string orderType; 
};

/**
    Represents statistics for a single day of deliveries
 */
struct Day
{
    int deliveriesCompleted;
    double totalMoneyEarned; 
    int bicycleDeliveries; 
    double bicycleMoney; 
    int mopedDeliveries; 
    double mopedMoney; 
    int missedOrders; 
};

class DeliverySystem
{
private:
    //attributes
    std::string fileName;
    std::vector<DeliveryRider*> allRiders;
    std::vector<DeliveryRider*> queue;
    std::vector<DeliveryRider*> unavailableRiders;
    Day currentDay;
public:
    //functions used only by deliverySystem

    /**
        Constructor for DeliverySystem object, instantiates DeliveryRider vector
     */
    DeliverySystem();
    
    /**
        Writes the summary of entire day of orders 
        processed and outputs them into a .dat file
        @param dateDigits gets only the digits of the date to create the file name dateDigits.dat
        @param day is a struct of the current day that contains information about statistics of the day
     */
    void writeDaySummary(const std::string& dateDigits, const Day& day);

    /**
        Returns a boolean value based on whether the 
        rider object is a Moped or not
        @param rider The deliveryRider object being checked
        @return a boolean value based on whether the rider object is a Moped or not
     */
    bool isMoped(DeliveryRider* rider);

    /**
        Returns a boolean value based on whether 
        the rider object is a Bicycle or not
        @param rider The deliveryRider object being checked
        @return a boolean value based on whether the rider object is a Bicycle or not
     */
    bool isBicycle(DeliveryRider* rider);

    /**
        Returns a boolean value based on whether 
        the order struct is a Priority order or not
        @param currentOrder The order struct being checked
        @return a boolean value based on whether the order is Priority or Standard
     */
    bool priority(Order* currentOrder);

    /**
        Returns a boolean value based on whether the 
        current line being read is a date or not
        @param line The line being read from orders file
        @return a boolean value based on whether or not the line is a date
     */
    bool checkDate(const std::string& line);

    /**
        Converts the distance given on each line of an
        orders file to a useable value
        @param line The line being read from order file
        @return a double that is converted from the distance value in string format from order file
     */
    double convertDistance(std::string line);

    /**
        Converts the hours of the time given on each line 
        of an orders file to a useable value
        @param line The line being read from order file
        @return an integer of the hours that is converted from the time value in string format from order file
     */
    int convertHours(std::string line);

    /**
        Converts the minutes of the time given on each line 
        of an orders file to a useable value
        @param line The line being read from order file
        @return an integer of the minutes that is converted from the time value in string format from order file
     */
    int convertMinutes(std::string line);

    /**
        Gives a full value of the time only in minutes, 
        multiplying the hours by 60 and adding them to the existing minutes
        @param hours the hour value being converted
        @param minutes the minute value to be added to the converted hour value
        @return an integer of value of the converted time to minutes
     */
    int toMinutes(int hours, int minutes);

    /**
        Checks whether the line being passed has an S or P
        for standard and priority orders and gives a string for the type
        @param line the line being read from order file
        @return a string of "Standard" or "Priority" based on order type
     */
    std::string orderType(std::string line);

    /**
        Updates the DeliveryRiders busyUntil attribute to a new minute value
        based on how long the rider will be busy for after taking the order
        @param rider pointer to DeliveryRider object being checked
        @param Order pointer to order struct to use some of the variables
     */
    void riderBusy(DeliveryRider* rider, Order* currentOrder);

    /**
        Reads the current line, creates an order struct and populates all the attributes
        of an order struct to be used.
        @param line the line being read from order file
        @return an Order struct with fully populated variables from the current line being passed in
     */
    Order* populateOrder(const std::string& line);
    

    /**
        Updates whether the DeliveryRiders are availabe or not by comparing the current time
        of the order we're looking at against the DeliveryRiders busyUntil attribute,
        a vector of all the riders who are unavailable is passed in to iterate through all of them
        if they're available they're added back to the queue
        @param currentTime the time based on the current order we're trying to fulfil
        @param queue a vector of deliveryRiders that are available in queue format
        @param unavailableRiders vector of riders that are currently unavailable
     */
    void updateRiderAvailability(int currentTime,
        std::vector<DeliveryRider*>& queue,
        std::vector<DeliveryRider*>& unavailableRiders);

    /**
        The function to actually process an order, which also will manage rider availability, the queue,
        the eligibity for taking certain types of orders and report information about the statistics of each order
        via popualting our Day struct
        @param currentOrder Order struct to fulfil
        @param queue a vector of deliveryRiders that are available in queue format
        @param unavailableRiders vector of riders that are currently unavailable
        @param day Day struct used to store information about the day to report stats
        @return an integer of 1 or 0 used to evaluate whether an order was missed or not, 0 for missed, 1 for success
     */
    int processOrder(Order* currentOrder,
        std::vector<DeliveryRider*>& queue,
        std::vector<DeliveryRider*>& unavailableRiders,
        Day& day); 

    /**
        Creates a vector of DeliveryRider objects
        @return returns the vector of DeliveryRider objects
     */    
    std::vector<DeliveryRider*> createRiders();

    /**
        Resets the order of the queue and clears unavailable rider list for the next day of orders
        @param riders vector of all riders used to reset queue
        @param queue vector of queue to determine DeliveryRider priority
        @param unavailableRiders vector of unavailableRiders so we can clear it for the new day
     */     
    void newDay(std::vector<DeliveryRider*>& riders,
        std::vector<DeliveryRider*>& unavailableRiders,
        std::vector<DeliveryRider*>& queue);
    /**
        Converts rider vector into string for testing purposes
        @return a string of all riders from the rider vector
     */    
    std::string getRiderList();

    /**
        Most important function that runs the entire orders file using all helper functions,
        runs a while loop to parse through each day checking whether it's an order or date line, manages entire
        deliverySystem logic, rider eligibility, financial, time and reports to Day struct at the end of each day,
        deletes rider objects after the system is run
        @param inputFile file to read and pass through input in the command line by user
     */
    void run(std::ifstream& inputFile);
};
#endif

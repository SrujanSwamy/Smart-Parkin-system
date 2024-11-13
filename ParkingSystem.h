#ifndef PARKINGSYSTEM_H
#define PARKINGSYSTEM_H

#include "Vehicle.h"
#include "DoublyLinkedList.h"
#include <unordered_map>
#include <queue>
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

// Enum for different types of vehicles
enum class VehicleType {
    CAR,
    BIKE,
    TRUCK,
    EV
};

// Vehicle class forward declaration
class Vehicle;

class ParkingSystem {
public:
    ParkingSystem(int carSlots, int bikeSlots, int truckSlots, int evSlots);
    
    // Function to add a vehicle to the parking system
    bool addVehicle(Vehicle* vehicle);
    
    // Function to remove a vehicle from the parking system
    bool removeVehicle(string regNumber);
    
    // Function to show bill of a vehicle
    void showBill(string regNumber);
    
    // Function to show the parking status of a specific vehicle
    void showStatus(string regNumber);
    
    // Function to show status of all parking slots
    void showAllStatus();
    
    // Menu function to display options
    void menu();

public:
    int carSlots, bikeSlots, truckSlots, evSlots;
    
    // Parking slot lists (Doubly Linked Lists)
    DoublyLinkedList* carSlotsList;
    DoublyLinkedList* bikeSlotsList;
    DoublyLinkedList* truckSlotsList;
    DoublyLinkedList* evSlotsList;
    
    // Hashmap to store vehicle details
    unordered_map<string, Vehicle*> vehicleDetails;

    // Helper function to calculate parking bill
    double calculateBill(Vehicle* vehicle, int hours);
    
    // Helper function to get nearest available slot
    int getNearestAvailableSlot(VehicleType type);
};

#endif // PARKINGSYSTEM_H

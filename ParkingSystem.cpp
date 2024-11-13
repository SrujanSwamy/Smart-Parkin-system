#include "ParkingSystem.h"
#include "Vehicle.h"
#include <iostream>
#include <ctime>
#include <cmath>
#include <unordered_map>

// Constructor to initialize parking slots for each vehicle type
ParkingSystem::ParkingSystem(int carSlots, int bikeSlots, int truckSlots, int evSlots) {
    this->carSlots = carSlots;
    this->bikeSlots = bikeSlots;
    this->truckSlots = truckSlots;
    this->evSlots = evSlots;

    // Create doubly linked lists for parking slots
    carSlotsList = new DoublyLinkedList();
    bikeSlotsList = new DoublyLinkedList();
    truckSlotsList = new DoublyLinkedList();
    evSlotsList = new DoublyLinkedList();
    
    // Initialize available slots (Example: 1 to n for each vehicle type)
    for (int i = 1; i <= carSlots; ++i) {
        carSlotsList->addSlot(i);
    }
    for (int i = 1; i <= bikeSlots; ++i) {
        bikeSlotsList->addSlot(i);
    }
    for (int i = 1; i <= truckSlots; ++i) {
        truckSlotsList->addSlot(i);
    }
    for (int i = 1; i <= evSlots; ++i) {
        evSlotsList->addSlot(i);
    }
}

// Function to add a vehicle to the parking system
bool ParkingSystem::addVehicle(Vehicle* vehicle) {
    int slotNumber = getNearestAvailableSlot(vehicle->type);
    if (slotNumber == -1) {
        cout << "No available slots for " << (vehicle->type == VehicleType::EV ? "EV" : 
            (vehicle->type == VehicleType::CAR ? "Car" : 
            (vehicle->type == VehicleType::BIKE ? "Bike" : "Truck"))) << endl;
        return false;
    }
    
    // Add vehicle to the hash map
    vehicleDetails[vehicle->getRegNumber()] = vehicle;
    
    // Mark the parking slot as occupied based on the vehicle type
    switch(vehicle->type) {
        case VehicleType::CAR:
            carSlotsList->markSlotOccupied(slotNumber);
            break;
        case VehicleType::BIKE:
            bikeSlotsList->markSlotOccupied(slotNumber);
            break;
        case VehicleType::TRUCK:
            truckSlotsList->markSlotOccupied(slotNumber);
            break;
        case VehicleType::EV:
            evSlotsList->markSlotOccupied(slotNumber);
            break;
        default:
            return false;
    }

    cout << vehicle->getRegNumber() << " has been parked at slot number: " << slotNumber << endl;
    return true;
}

// Function to remove a vehicle from the parking system
bool ParkingSystem::removeVehicle(string regNumber) {
    if (vehicleDetails.find(regNumber) == vehicleDetails.end()) {
        cout << "Vehicle not found!" << endl;
        return false;
    }

    Vehicle* vehicle = vehicleDetails[regNumber];
    int slotNumber = vehicle->getSlotNumber();

    // Free the slot based on vehicle type
    switch(vehicle->getType()) {
        case VehicleType::CAR:
            carSlotsList->markSlotAvailable(slotNumber);
            break;
        case VehicleType::BIKE:
            bikeSlotsList->markSlotAvailable(slotNumber);
            break;
        case VehicleType::TRUCK:
            truckSlotsList->markSlotAvailable(slotNumber);
            break;
        case VehicleType::EV:
            evSlotsList->markSlotAvailable(slotNumber);
            break;
        default:
            return false;
    }

    // Remove the vehicle from the hash map
    vehicleDetails.erase(regNumber);

    cout << regNumber << " has been removed from the parking lot." << endl;
    
    // Delete the vehicle object to manage memory
    delete vehicle;
    
    return true;
}

// Function to calculate the parking bill
double ParkingSystem::calculateBill(Vehicle* vehicle, int seconds) {
    double rate;
    switch (vehicle->getType()) {
        case VehicleType::CAR:
            rate = 10.0; // Example rate per hour
            break;
        case VehicleType::BIKE:
            rate = 5.0;
            break;
        case VehicleType::TRUCK:
            rate = 15.0;
            break;
        case VehicleType::EV:
            rate = 20.0; // Higher rate for EV stations
            break;
        default:
            rate = 0;
            break;
    }
    return seconds * rate;
}

// Function to show the bill of a vehicle
void ParkingSystem::showBill(string regNumber) {
    if (vehicleDetails.find(regNumber) == vehicleDetails.end()) {
        cout << "Vehicle not found!" << endl;
        return;
    }

    Vehicle* vehicle = vehicleDetails[regNumber];
    auto duration = duration_cast<seconds>(system_clock::now() - vehicle->getEntryTime());
    int seconds = duration.count();
    
    double bill = calculateBill(vehicle, seconds);
    cout << "Bill for vehicle " << regNumber << "Rs." << bill << endl;
}

// Function to show parking status for a specific vehicle
void ParkingSystem::showStatus(string regNumber) {
    if (vehicleDetails.find(regNumber) == vehicleDetails.end()) {
        cout << "Vehicle not found!" << endl;
        return;
    }

    Vehicle* vehicle = vehicleDetails[regNumber];
    cout << "Vehicle " << regNumber << " is parked at slot " << vehicle->getSlotNumber() << endl;
}

// Function to show status of all parking slots
void ParkingSystem::showAllStatus() {
    carSlotsList->displayAllSlots();
    bikeSlotsList->displayAllSlots();
    truckSlotsList->displayAllSlots();
    evSlotsList->displayAllSlots();
}

// Function to get the nearest available parking slot based on vehicle type
int ParkingSystem::getNearestAvailableSlot(VehicleType type) {
    switch (type) {
        case VehicleType::CAR: return carSlotsList->getNearestAvailableSlot();
        case VehicleType::BIKE: return bikeSlotsList->getNearestAvailableSlot();
        case VehicleType::TRUCK: return truckSlotsList->getNearestAvailableSlot();
        case VehicleType::EV: return evSlotsList->getNearestAvailableSlot();
        default: return -1;
    }
}

// Menu-driven function
void ParkingSystem::menu() {
    int choice;
    do {
        cout << "\nParking System Menu:\n";
        cout << "1. Add Vehicle\n";
        cout << "2. Remove Vehicle\n";
        cout << "3. Show Vehicle Status\n";
        cout << "4. Show All Slot Status\n";
        cout << "5. Show Bill\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        string type;
        string regNumber;
        Vehicle* vehicle;
        switch (choice) {
            case 1:
                cout << "Enter vehicle type (CAR, BIKE, TRUCK, EV): ";
                
                cin >> type;
                cout << "Enter registration number: ";
                cin >> regNumber;
                
                // Instantiate the vehicle object based on type
                if (type == "CAR") {
                    vehicle = new Vehicle(regNumber, VehicleType::CAR);
                } else if (type == "BIKE") {
                    vehicle = new Vehicle(regNumber, VehicleType::BIKE);
                } else if (type == "TRUCK") {
                    vehicle = new Vehicle(regNumber, VehicleType::TRUCK);
                } else if (type == "EV") {
                    vehicle = new Vehicle(regNumber, VehicleType::EV);
                }
                addVehicle(vehicle);
                break;
            case 2:
                cout << "Enter registration number: ";
                cin >> regNumber;
                removeVehicle(regNumber);
                break;
            case 3:
                cout << "Enter registration number: ";
                cin >> regNumber;
                showStatus(regNumber);
                break;
            case 4:
                showAllStatus();
                break;
            case 5:
                cout << "Enter registration number: ";
                cin >> regNumber;
                showBill(regNumber);
                break;
            case 6:
                cout << "Exiting the parking system..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 6);
}

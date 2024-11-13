#include "Vehicle.h"

Vehicle::Vehicle(string regNumber, VehicleType type) 
    : regNumber(regNumber), type(type), slotNumber(-1) {
    entryTime = system_clock::now();  // Capture entry time when the vehicle enters
}

string Vehicle::getRegNumber() const {
    return regNumber;
}

VehicleType Vehicle::getType() const {
    return type;
}

int Vehicle::getSlotNumber() const {
    return slotNumber;
}

void Vehicle::setSlotNumber(int slotNumber) {
    this->slotNumber = slotNumber;
}

system_clock::time_point Vehicle::getEntryTime() const {
    return entryTime;
}

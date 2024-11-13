#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <chrono>
using namespace std;
using namespace std::chrono;

enum class VehicleType;

class Vehicle {
public:
    Vehicle(string regNumber, VehicleType type);

    string getRegNumber() const;
    VehicleType getType() const;
    int getSlotNumber() const;
    void setSlotNumber(int slotNumber);
    system_clock::time_point getEntryTime() const;

public:
    string regNumber;
    VehicleType type;
    int slotNumber;
    system_clock::time_point entryTime;
};

#endif // VEHICLE_H

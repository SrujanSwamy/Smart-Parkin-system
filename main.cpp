#include <iostream>
#include "ParkingSystem.h"

int main() {
    ParkingSystem parkingSystem(10, 5, 3, 2);  // Example configuration: 10 Car slots, 5 Bike slots, 3 Truck slots, 2 EV slots

    // Run the menu-driven system
    parkingSystem.menu();

    return 0;
}

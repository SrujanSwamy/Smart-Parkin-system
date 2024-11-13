#include "DoublyLinkedList.h"
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// class DoublyLinkedList {
// public:
//     struct SlotNode {
//         int slotNumber;
//         bool isOccupied;
//         SlotNode* next;
//         SlotNode* prev;

//         SlotNode(int slotNumber);
//     };

//     DoublyLinkedList();
//     ~DoublyLinkedList();
    
//     void addSlot(int slotNumber);
//     void markSlotOccupied(int slotNumber);
//     void markSlotAvailable(int slotNumber);
//     int getNearestAvailableSlot();
//     void displayAllSlots();

// public:
//     SlotNode* head;
//     SlotNode* tail;
//     priority_queue<int, vector<int>, greater<int>> availableSlots;  // Min-heap for available slots
// };

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

DoublyLinkedList::~DoublyLinkedList() {
    SlotNode* current = head;
    while (current) {
        SlotNode* temp = current;
        current = current->next;
        delete temp;
    }
}

void DoublyLinkedList::addSlot(int slotNumber) {
    SlotNode* newNode = new SlotNode(slotNumber);
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    
    // Add the slot to the priority queue
    availableSlots.push(slotNumber);
}

void DoublyLinkedList::markSlotOccupied(int slotNumber) {
    SlotNode* current = head;
    while (current) {
        if (current->slotNumber == slotNumber) {
            current->isOccupied = true;
            break;
        }
        current = current->next;
    }

    // Remove the slot from the priority queue (it is now occupied)
    priority_queue<int, vector<int>, greater<int>> tempQueue;
    while (!availableSlots.empty()) {
        int availableSlot = availableSlots.top();
        availableSlots.pop();
        if (availableSlot != slotNumber) {
            tempQueue.push(availableSlot);
        }
    }
    availableSlots = tempQueue;
}

void DoublyLinkedList::markSlotAvailable(int slotNumber) {
    SlotNode* current = head;
    while (current) {
        if (current->slotNumber == slotNumber) {
            current->isOccupied = false;
            break;
        }
        current = current->next;
    }

    // Add the slot back to the priority queue (it is now available)
    availableSlots.push(slotNumber);
}

int DoublyLinkedList::getNearestAvailableSlot() {
    if (!availableSlots.empty()) {
        return availableSlots.top();  // Return the slot with the smallest number (earliest available)
    }
    return -1;  // No available slot
}

void DoublyLinkedList::displayAllSlots() {
    SlotNode* current = head;
    while (current) {
        cout << "Slot " << current->slotNumber << " is " 
             << (current->isOccupied ? "Occupied" : "Available") << endl;
        current = current->next;
    }
}

DoublyLinkedList::SlotNode::SlotNode(int slotNumber) 
    : slotNumber(slotNumber), isOccupied(false), next(nullptr), prev(nullptr) {}

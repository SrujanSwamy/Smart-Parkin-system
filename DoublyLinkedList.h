#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include <queue>  // Include this header
#include <vector>

class DoublyLinkedList {
public:

    DoublyLinkedList();
    ~DoublyLinkedList();

    void addSlot(int slotNumber);
    void markSlotOccupied(int slotNumber);
    void markSlotAvailable(int slotNumber);
    int getNearestAvailableSlot();
    void displayAllSlots();

public:
    class SlotNode {
    public:
        int slotNumber;
        bool isOccupied;
        SlotNode* next;
        SlotNode* prev;
        
        SlotNode(int slotNumber);
    };
    
    SlotNode* head;
    SlotNode* tail;
    std::priority_queue<int, std::vector<int>, std::greater<int>> availableSlots; 
};

#endif // DOUBLYLINKEDLIST_H

#include <string>
#include "Order.h"

// Pending orders stored as a queue (FIFO) using a linked list
class OrderQueue {
private:
    Order* head;      // front: the oldest order
    Order* tail;      // back: the newest order
    int nextOrderId;  // auto-increment order ID

public:
    OrderQueue();
    ~OrderQueue();

    bool isEmpty() const;

    // Adds a new order at the back. Returns the new order ID.
    int enqueue(const std::string& customerName, const int itemIds[], int itemCount, double total);

    // Prints all pending orders from front to back
    void display() const;
};
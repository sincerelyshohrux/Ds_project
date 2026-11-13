#ifndef ORDERQUEUE_H
#define ORDERQUEUE_H

#include <string>
#include "Order.h"

// Pending orders stored as a queue (FIFO) using a linked list
class OrderQueue {
private:
    Order* head;      // front: the oldest order
    Order* tail;      // back: the newest order
    int count;        // number of pending orders
    int nextOrderId;  // auto-increment order ID

public:
    OrderQueue();
    ~OrderQueue();

    bool isEmpty() const;
    int size() const;

    // Adds a new order at the back. Returns the new order ID.
    int enqueue(const std::string& customerName, const int itemIds[],
                const std::string itemNames[], int itemCount, double total);

    // Removes the order at the front and returns it (nullptr if empty).
    // The caller becomes the owner of the returned node.
    Order* dequeue();

    // Removes a pending order with the given ID (customer cancels it).
    // Returns false if no pending order has this ID.
    bool cancelOrder(int orderId);

    // Linear search by order ID. Returns nullptr if not found.
    const Order* findById(int orderId) const;

    // Prints all pending orders from front to back
    void display() const;
};

#endif

#ifndef ORDERSTACK_H
#define ORDERSTACK_H

#include "Order.h"

// Completed-order history stored as a stack (LIFO) using a linked list.
// The most recently completed order is on top.
class OrderStack {
private:
    Order* top;   // last completed order
    int count;    // number of completed orders

public:
    OrderStack();
    ~OrderStack();

    bool isEmpty() const;
    int size() const;

    // Puts a completed order on top. The stack becomes its owner.
    void push(Order* order);

    // Returns the top order without removing it (nullptr if empty).
    const Order* peek() const;

    // Linear search by order ID. Returns nullptr if not found.
    const Order* findById(int orderId) const;

    // Prints history from newest to oldest
    void display() const;
};

#endif

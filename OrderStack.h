#ifndef ORDERSTACK_H
#define ORDERSTACK_H

#include "Order.h"

// Completed orders: stack (LIFO) made with a linked list
class OrderStack {
private:
    Order* top;   // last completed order
    int count;

public:
    OrderStack();
    ~OrderStack();

    OrderStack(const OrderStack&) = delete;
    OrderStack& operator=(const OrderStack&) = delete;

    bool isEmpty() const;
    int size() const;

    void push(Order* order);
    const Order* peek() const;
    const Order* findById(int orderId) const;
    void display() const;
};

#endif

#ifndef ORDERQUEUE_H
#define ORDERQUEUE_H

#include <string>
#include "Order.h"

// Pending orders: queue (FIFO) made with a linked list
class OrderQueue {
private:
    Order* head;   // front: oldest order
    Order* tail;   // back: newest order
    int count;
    int nextOrderId;

public:
    OrderQueue();
    ~OrderQueue();

    OrderQueue(const OrderQueue&) = delete;
    OrderQueue& operator=(const OrderQueue&) = delete;

    bool isEmpty() const;
    int size() const;

    int enqueue(const std::string& customerName, const int itemIds[],
                const std::string itemNames[], int itemCount, double total);

    Order* dequeue();
    bool cancelOrder(int orderId);

    const Order* findById(int orderId) const;

    void display() const;
};

#endif

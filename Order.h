#ifndef ORDER_H
#define ORDER_H

#include <string>

const int MAX_ORDER_ITEMS = 10;   // max items in one order

// One customer order. It is also a node of the queue and the stack
struct Order {
    int orderId;
    std::string customerName;
    int itemIds[MAX_ORDER_ITEMS];             // array of item IDs
    std::string itemNames[MAX_ORDER_ITEMS];   // array of item names
    int itemCount;
    double total;
    Order* next;
};

void printOrder(const Order* order);

#endif

#ifndef ORDER_H
#define ORDER_H

#include <string>

const int MAX_ORDER_ITEMS = 10;   // max items in one order (array size)

// One customer order. It is also a node: the same Order can sit
// in the pending queue and later move to the completed-history stack.
struct Order {
    int orderId;
    std::string customerName;
    int itemIds[MAX_ORDER_ITEMS];               // array of menu item IDs
    std::string itemNames[MAX_ORDER_ITEMS];     // names saved at order time (menu may change later)
    int itemCount;
    double total;
    Order* next;
};

// Prints one order on one line. Time: O(k), k = items in the order
void printOrder(const Order* order);

#endif

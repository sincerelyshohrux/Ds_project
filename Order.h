#include <string>

const int MAX_ORDER_ITEMS = 10;   // max items in one order

// One customer order (also a node of the queue)
struct Order {
    int orderId;
    std::string customerName;
    int itemIds[MAX_ORDER_ITEMS];   // array of menu item IDs
    int itemCount;
    double total;
    Order* next;
};
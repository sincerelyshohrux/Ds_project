#include "Order.h"
#include <iostream>
#include <iomanip>
using namespace std;

// Prints order ID, customer, items (from the array) and total
void printOrder(const Order* order) {
    cout << "Order ID: " << order->orderId
         << " | Customer: " << order->customerName
         << " | Items: ";
    for (int i = 0; i < order->itemCount; i++) {
        cout << order->itemNames[i] << " (#" << order->itemIds[i] << ")";
        if (i < order->itemCount - 1) cout << ", ";
    }
    cout << " | Total: " << fixed << setprecision(2) << order->total << "\n";
}

#include "OrderStack.h"
#include <iostream>
using namespace std;

OrderStack::OrderStack() {
    top = nullptr;
    count = 0;
}

// Frees all nodes
OrderStack::~OrderStack() {
    while (top != nullptr) {
        Order* temp = top;
        top = top->next;
        delete temp;
    }
}

bool OrderStack::isEmpty() const {
    return top == nullptr;
}

int OrderStack::size() const {
    return count;
}

// Adds an order on top. Time: O(1)
void OrderStack::push(Order* order) {
    if (order == nullptr) return;
    order->next = top;
    top = order;
    count++;
}

// Looks at the top order. Time: O(1)
const Order* OrderStack::peek() const {
    return top;
}

// Linear search from top to bottom. Time: O(n)
const Order* OrderStack::findById(int orderId) const {
    Order* current = top;
    while (current != nullptr) {
        if (current->orderId == orderId) return current;
        current = current->next;
    }
    return nullptr;
}

// Prints history, newest first. Time: O(n)
void OrderStack::display() const {
    if (isEmpty()) {
        cout << "No completed orders yet.\n";
        return;
    }
    cout << "\n--- COMPLETED ORDERS (" << count << ", newest first) ---\n";
    Order* current = top;
    while (current != nullptr) {
        printOrder(current);
        current = current->next;
    }
}

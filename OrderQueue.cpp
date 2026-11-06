#include "OrderQueue.h"
#include <iostream>
using namespace std;

OrderQueue::OrderQueue() {
    head = nullptr;
    tail = nullptr;
    nextOrderId = 1001;
}

// Frees all nodes
OrderQueue::~OrderQueue() {
    while (head != nullptr) {
        Order* temp = head;
        head = head->next;
        delete temp;
    }
}

bool OrderQueue::isEmpty() const {
    return head == nullptr;
}

// Adds an order at the back of the queue. Time: O(1)
int OrderQueue::enqueue(const string& customerName, const int itemIds[], int itemCount, double total) {
    Order* newOrder = new Order;
    newOrder->orderId = nextOrderId++;
    newOrder->customerName = customerName;
    newOrder->itemCount = itemCount;
    newOrder->total = total;
    newOrder->next = nullptr;

    for (int i = 0; i < itemCount; i++) {
        newOrder->itemIds[i] = itemIds[i];
    }

    if (tail == nullptr) {      // queue was empty
        head = newOrder;
        tail = newOrder;
    } else {
        tail->next = newOrder;
        tail = newOrder;
    }
    return newOrder->orderId;
}

// Prints pending orders, the oldest first. Time: O(n)
void OrderQueue::display() const {
    if (isEmpty()) {
        cout << "No pending orders.\n";
        return;
    }
    cout << "\n--- PENDING ORDERS (first = next to process) ---\n";
    Order* current = head;
    while (current != nullptr) {
        cout << "Order ID: " << current->orderId
             << " | Customer: " << current->customerName
             << " | Items: ";
        for (int i = 0; i < current->itemCount; i++) {
            cout << current->itemIds[i] << " ";
        }
        cout << "| Total: " << current->total << "\n";
        current = current->next;
    }
}
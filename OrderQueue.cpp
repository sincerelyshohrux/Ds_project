#include "OrderQueue.h"
#include <iostream>
using namespace std;

OrderQueue::OrderQueue() {
    head = nullptr;
    tail = nullptr;
    count = 0;
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

int OrderQueue::size() const {
    return count;
}

// Adds an order at the back of the queue. Time: O(1)
int OrderQueue::enqueue(const string& customerName, const int itemIds[],
                        const string itemNames[], int itemCount, double total) {
    Order* newOrder = new Order;
    newOrder->orderId = nextOrderId++;
    newOrder->customerName = customerName;
    newOrder->itemCount = itemCount;
    newOrder->total = total;
    newOrder->next = nullptr;

    for (int i = 0; i < itemCount; i++) {
        newOrder->itemIds[i] = itemIds[i];
        newOrder->itemNames[i] = itemNames[i];
    }

    if (tail == nullptr) {      // queue was empty
        head = newOrder;
        tail = newOrder;
    } else {
        tail->next = newOrder;
        tail = newOrder;
    }
    count++;
    return newOrder->orderId;
}

// Removes the oldest order (front). Time: O(1)
Order* OrderQueue::dequeue() {
    if (isEmpty()) return nullptr;   // underflow

    Order* front = head;
    head = head->next;
    if (head == nullptr) {           // queue became empty
        tail = nullptr;
    }
    front->next = nullptr;           // detach the node
    count--;
    return front;
}

// Removes an order from any position of the queue. Time: O(n)
bool OrderQueue::cancelOrder(int orderId) {
    if (isEmpty()) return false;

    // Case 1: the order is at the front
    if (head->orderId == orderId) {
        delete dequeue();
        return true;
    }

    // Case 2: find the node BEFORE the one we want to remove
    Order* current = head;
    while (current->next != nullptr && current->next->orderId != orderId) {
        current = current->next;
    }
    if (current->next == nullptr) return false;   // not found

    Order* temp = current->next;
    current->next = temp->next;
    if (temp == tail) {        // removed the last node -> move tail back
        tail = current;
    }
    delete temp;
    count--;
    return true;
}

// Linear search from front to back. Time: O(n)
const Order* OrderQueue::findById(int orderId) const {
    Order* current = head;
    while (current != nullptr) {
        if (current->orderId == orderId) return current;
        current = current->next;
    }
    return nullptr;
}

// Prints pending orders, the oldest first. Time: O(n)
void OrderQueue::display() const {
    if (isEmpty()) {
        cout << "No pending orders.\n";
        return;
    }
    cout << "\n--- PENDING ORDERS (" << count << ", first = next to process) ---\n";
    Order* current = head;
    while (current != nullptr) {
        printOrder(current);
        current = current->next;
    }
}

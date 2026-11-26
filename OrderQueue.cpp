#include "OrderQueue.h"
#include <iostream>
using namespace std;

OrderQueue::OrderQueue() {
    head = nullptr;
    tail = nullptr;
    count = 0;
    nextOrderId = 1001;
}

// Deletes all nodes when the program ends
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

// Adds an order at the back. Time: O(1)
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

    if (tail == nullptr) {
        head = newOrder;
        tail = newOrder;
    } else {
        tail->next = newOrder;
        tail = newOrder;
    }
    count++;
    return newOrder->orderId;
}

// Removes the order from the front. Time: O(1)
Order* OrderQueue::dequeue() {
    if (isEmpty()) return nullptr;

    Order* front = head;
    head = head->next;
    if (head == nullptr) {   // queue became empty
        tail = nullptr;
    }
    front->next = nullptr;
    count--;
    return front;
}

// Removes an order by ID from any place. Time: O(n)
bool OrderQueue::cancelOrder(int orderId) {
    if (isEmpty()) return false;

    if (head->orderId == orderId) {
        delete dequeue();
        return true;
    }

    Order* current = head;
    while (current->next != nullptr && current->next->orderId != orderId) {
        current = current->next;
    }
    if (current->next == nullptr) return false;

    Order* temp = current->next;
    current->next = temp->next;
    if (temp == tail) {   // last node removed -> move tail back
        tail = current;
    }
    delete temp;
    count--;
    return true;
}

// Linear search by order ID. Time: O(n)
const Order* OrderQueue::findById(int orderId) const {
    Order* current = head;
    while (current != nullptr) {
        if (current->orderId == orderId) return current;
        current = current->next;
    }
    return nullptr;
}

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

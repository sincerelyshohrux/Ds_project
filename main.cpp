// ============================================================
// Online Food Ordering and Order Processing System
// Team name: GalaxyE
// Section: 4
// Members:
//   1. Shohruxbek Maxamatjonov (U2510135)
//   2. Suxrobbek Muminov       (U2510138)
//   3. Asliddin Xazratqulov    (U2510142)
//   4. TODO: Name 4           (ID)
//
// Data structures used:
//   - Singly linked list : menu items            (MenuList)
//   - Queue (linked list): pending orders, FIFO  (OrderQueue)
//   - Stack (linked list): completed history     (OrderStack)
//   - Arrays             : items inside one order (Order)
// Algorithms:
//   - Linear search : find menu item / order by ID   O(n)
//   - Selection sort: sort menu by price or name     O(n^2)
// ============================================================

#include <iostream>
#include <iomanip>
#include "Utils.h"
#include "MenuList.h"
#include "OrderQueue.h"
#include "OrderStack.h"
using namespace std;

void showMainMenu() {
    cout << "\n===== FOOD ORDERING SYSTEM =====\n";
    cout << "1. Add menu item\n";
    cout << "2. Display menu\n";
    cout << "3. Update menu item\n";
    cout << "4. Delete menu item\n";
    cout << "5. Sort menu by price\n";
    cout << "6. Sort menu by name\n";
    cout << "7. Place order\n";
    cout << "8. Display pending orders\n";
    cout << "9. Process next order (FIFO)\n";
    cout << "10. Cancel an order\n";
    cout << "11. Display completed-order history\n";
    cout << "12. Search order by ID\n";
    cout << "13. Show last completed order\n";
    cout << "0. Exit\n";
}

// Asks the customer for items and adds the order to the queue
void placeOrder(MenuList& menu, OrderQueue& pending) {
    if (menu.isEmpty()) {
        cout << "Menu is empty. Cannot place an order.\n";
        return;
    }

    string customer = readText("Enter customer name: ");
    menu.display();

    int itemIds[MAX_ORDER_ITEMS];          // array: chosen item IDs
    string itemNames[MAX_ORDER_ITEMS];     // array: chosen item names
    int count = 0;
    double total = 0;

    cout << "Enter item IDs one by one. Enter 0 to finish.\n";
    // The loop always ends with 0, even when the order is full. Otherwise the
    // user's "0 to finish" would be read by the main menu as "Exit".
    while (true) {
        int id = readInt("Item ID (0 to finish): ");
        if (id == 0) break;

        if (count == MAX_ORDER_ITEMS) {   // array is full: ignore extra items
            cout << "Order is full (max " << MAX_ORDER_ITEMS << " items). Enter 0 to finish.\n";
            continue;
        }

        string name;
        double price;
        if (!menu.getItem(id, name, price)) {
            cout << "Item with ID " << id << " not found.\n";
            continue;
        }

        itemIds[count] = id;
        itemNames[count] = name;
        count++;
        total += price;
        cout << "Added: " << name << " (" << price << ")\n";
        if (count == MAX_ORDER_ITEMS) {
            cout << "Order is now full (max " << MAX_ORDER_ITEMS << " items). Enter 0 to finish.\n";
        }
    }

    if (count == 0) {
        cout << "No items selected. Order was not placed.\n";
        return;
    }

    int orderId = pending.enqueue(customer, itemIds, itemNames, count, total);
    cout << "Order placed! Order ID: " << orderId << ", Total: " << fixed << setprecision(2) << total << "\n";
}

// Takes the oldest pending order (dequeue) and pushes it to history (stack)
void processNextOrder(OrderQueue& pending, OrderStack& completed) {
    if (pending.isEmpty()) {
        cout << "No pending orders to process.\n";
        return;
    }
    Order* order = pending.dequeue();   // O(1)
    completed.push(order);              // O(1)
    cout << "Processed: ";
    printOrder(order);
    cout << "Remaining pending orders: " << pending.size() << "\n";
}

// Cancels a pending order. Completed orders cannot be cancelled.
void cancelOrder(OrderQueue& pending, const OrderStack& completed) {
    if (pending.isEmpty()) {
        cout << "No pending orders to cancel.\n";
        return;
    }
    pending.display();
    int id = readInt("Enter order ID to cancel: ");
    if (pending.cancelOrder(id)) {
        cout << "Order " << id << " cancelled.\n";
    } else if (completed.findById(id) != nullptr) {
        cout << "Order " << id << " is already completed and cannot be cancelled.\n";
    } else {
        cout << "Order with ID " << id << " not found.\n";
    }
}

// Searches pending queue first, then completed history
void searchOrder(const OrderQueue& pending, const OrderStack& completed) {
    if (pending.isEmpty() && completed.isEmpty()) {
        cout << "There are no orders yet.\n";
        return;
    }
    int id = readInt("Enter order ID to search: ");

    const Order* order = pending.findById(id);
    if (order != nullptr) {
        cout << "Status: PENDING\n";
        printOrder(order);
        return;
    }
    order = completed.findById(id);
    if (order != nullptr) {
        cout << "Status: COMPLETED\n";
        printOrder(order);
        return;
    }
    cout << "Order with ID " << id << " not found (it may have been cancelled).\n";
}

int main() {
    MenuList menu;
    OrderQueue pending;      // queue: orders waiting to be processed
    OrderStack completed;    // stack: history of processed orders
    int choice;

    do {
        showMainMenu();
        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1: {
                string name = readText("Enter item name: ");
                if (menu.nameTaken(name, 0)) {
                    cout << "An item named \"" << name << "\" already exists.\n";
                    break;
                }
                double price = readPrice("Enter item price: ");
                menu.addItem(name, price);
                break;
            }
            case 2:
                menu.display();
                break;
            case 3: {
                if (menu.isEmpty()) {
                    cout << "Menu is empty. Nothing to update.\n";
                    break;
                }
                menu.display();
                int id = readInt("Enter ID of the item to update: ");
                if (!menu.exists(id)) {
                    cout << "Item with ID " << id << " not found.\n";
                    break;
                }
                string name = readText("Enter new name: ");
                if (menu.nameTaken(name, id)) {
                    cout << "Another item named \"" << name << "\" already exists.\n";
                    break;
                }
                double price = readPrice("Enter new price: ");
                menu.updateItem(id, name, price);
                cout << "Item updated.\n";
                break;
            }
            case 4: {
                if (menu.isEmpty()) {
                    cout << "Menu is empty. Nothing to delete.\n";
                    break;
                }
                menu.display();
                int id = readInt("Enter ID of the item to delete: ");
                if (menu.deleteItem(id)) {
                    cout << "Item deleted.\n";
                } else {
                    cout << "Item with ID " << id << " not found.\n";
                }
                break;
            }
            case 5:
                if (menu.isEmpty()) {
                    cout << "Menu is empty. Nothing to sort.\n";
                    break;
                }
                menu.sortMenu(true);
                cout << "Menu sorted by price.\n";
                menu.display();
                break;
            case 6:
                if (menu.isEmpty()) {
                    cout << "Menu is empty. Nothing to sort.\n";
                    break;
                }
                menu.sortMenu(false);
                cout << "Menu sorted by name.\n";
                menu.display();
                break;
            case 7:
                placeOrder(menu, pending);
                break;
            case 8:
                pending.display();
                break;
            case 9:
                processNextOrder(pending, completed);
                break;
            case 10:
                cancelOrder(pending, completed);
                break;
            case 11:
                completed.display();
                break;
            case 12:
                searchOrder(pending, completed);
                break;
            case 13: {
                const Order* last = completed.peek();   // top of the stack, O(1)
                if (last == nullptr) {
                    cout << "No completed orders yet.\n";
                } else {
                    cout << "Last completed order: ";
                    printOrder(last);
                }
                break;
            }
            case 0:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}

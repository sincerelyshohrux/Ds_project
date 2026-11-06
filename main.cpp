// ============================================================
// Online Food Ordering and Order Processing System
// Team name: <GalaxyE>
// Section: 4
// Members: <Shohruxbek Maxamatjonov (U2510135)>, <Suxrobbek Muminov (U2510138)>, <Asliddin Xazratqulov (U2510142)>, <Name 4 (ID)>
// ============================================================

#include <iostream>
#include "Utils.h"
#include "MenuList.h"
#include "OrderQueue.h"
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

    int itemIds[MAX_ORDER_ITEMS];
    int count = 0;
    double total = 0;

    cout << "Enter item IDs one by one. Enter 0 to finish.\n";
    while (count < MAX_ORDER_ITEMS) {
        int id = readInt("Item ID (0 to finish): ");
        if (id == 0) break;

        string name;
        double price;
        if (!menu.getItem(id, name, price)) {
            cout << "Item with ID " << id << " not found.\n";
            continue;
        }

        itemIds[count] = id;
        count++;
        total += price;
        cout << "Added: " << name << " (" << price << ")\n";
    }

    if (count == MAX_ORDER_ITEMS) {
        cout << "Order is full (max " << MAX_ORDER_ITEMS << " items).\n";
    }
    if (count == 0) {
        cout << "No items selected. Order was not placed.\n";
        return;
    }

    int orderId = pending.enqueue(customer, itemIds, count, total);
    cout << "Order placed! Order ID: " << orderId << ", Total: " << total << "\n";
}

int main() {
    MenuList menu;
    OrderQueue pending;
    int choice;

    do {
        showMainMenu();
        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1: {
                string name = readText("Enter item name: ");
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
            case 0:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
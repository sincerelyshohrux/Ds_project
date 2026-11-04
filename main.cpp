// ============================================================
// Online Food Ordering and Order Processing System
// Team name: <GalaxyE>
// Section: 4
// Members: <Shohruxbek Maxamatjonov (U2510135)>, <Suxrobbek Muminov (U2510138)>, <Asliddin Xazratqulov (U2510142)>, <Name 4 (ID)>
// ============================================================

#include <iostream>
#include "Utils.h"
#include "MenuList.h"
using namespace std;

void showMainMenu() {
    cout << "\n===== FOOD ORDERING SYSTEM =====\n";
    cout << "1. Add menu item\n";
    cout << "2. Display menu\n";
    cout << "0. Exit\n";
}

int main() {
    MenuList menu;
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
            case 0:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
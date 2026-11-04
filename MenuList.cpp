#include "MenuList.h"
#include <iostream>
using namespace std;

MenuList::MenuList() {
    head = nullptr;
    nextId = 1;
}

// Frees all nodes
MenuList::~MenuList() {
    while (head != nullptr) {
        MenuItem* temp = head;
        head = head->next;
        delete temp;
    }
}

bool MenuList::isEmpty() const {
    return head == nullptr;
}

// Adds a new item at the end of the list. Time: O(n)
void MenuList::addItem(const string& name, double price) {
    MenuItem* newItem = new MenuItem;
    newItem->id = nextId++;
    newItem->name = name;
    newItem->price = price;
    newItem->next = nullptr;

    if (head == nullptr) {
        head = newItem;
    } else {
        MenuItem* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newItem;
    }
    cout << "Item added with ID " << newItem->id << ".\n";
}

// Prints all menu items. Time: O(n)
void MenuList::display() const {
    if (isEmpty()) {
        cout << "Menu is empty.\n";
        return;
    }
    cout << "\n--- MENU ---\n";
    cout << "ID\tPrice\tName\n";
    MenuItem* current = head;
    while (current != nullptr) {
        cout << current->id << "\t" << current->price << "\t" << current->name << "\n";
        current = current->next;
    }
}
#include "MenuList.h"
#include <iostream>
#include <iomanip>
#include <utility>
using namespace std;

MenuList::MenuList() {
    head = nullptr;
    nextId = 1;
}

// Deletes all nodes when the program ends
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

// Linear search by ID. Time: O(n)
MenuItem* MenuList::findById(int id) const {
    MenuItem* current = head;
    while (current != nullptr) {
        if (current->id == id) return current;
        current = current->next;
    }
    return nullptr;
}

bool MenuList::exists(int id) const {
    return findById(id) != nullptr;
}

static string toLower(const string& text) {
    string result = text;
    for (size_t i = 0; i < result.size(); i++) {
        if (result[i] >= 'A' && result[i] <= 'Z') {
            result[i] = result[i] - 'A' + 'a';
        }
    }
    return result;
}

// Checks if another item already has this name. Time: O(n)
bool MenuList::nameTaken(const string& name, int skipId) const {
    MenuItem* current = head;
    while (current != nullptr) {
        if (current->id != skipId && toLower(current->name) == toLower(name)) {
            return true;
        }
        current = current->next;
    }
    return false;
}

bool MenuList::getItem(int id, string& name, double& price) const {
    MenuItem* item = findById(id);
    if (item == nullptr) return false;

    name = item->name;
    price = item->price;
    return true;
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

void MenuList::display() const {
    if (isEmpty()) {
        cout << "Menu is empty.\n";
        return;
    }
    cout << "\n--- MENU ---\n";
    cout << "ID\tPrice\tName\n";
    MenuItem* current = head;
    while (current != nullptr) {
        cout << current->id << "\t" << fixed << setprecision(2) << current->price << "\t" << current->name << "\n";
        current = current->next;
    }
}

bool MenuList::updateItem(int id, const string& newName, double newPrice) {
    MenuItem* item = findById(id);
    if (item == nullptr) return false;

    item->name = newName;
    item->price = newPrice;
    return true;
}

// Deletes an item by ID. Time: O(n)
bool MenuList::deleteItem(int id) {
    if (head == nullptr) return false;

    // Case 1: the item is the first node
    if (head->id == id) {
        MenuItem* temp = head;
        head = head->next;
        delete temp;
        return true;
    }
    // Case 2: find the node before the one we delete
    MenuItem* current = head;
    while (current->next != nullptr && current->next->id != id) {
        current = current->next;
    }

    if (current->next == nullptr) return false;

    MenuItem* temp = current->next;
    current->next = temp->next;
    delete temp;
    return true;
}

// Swaps the data of two nodes (links stay the same)
void MenuList::swapData(MenuItem* a, MenuItem* b) {
    swap(a->id, b->id);
    swap(a->name, b->name);
    swap(a->price, b->price);
}

bool MenuList::isLess(MenuItem* a, MenuItem* b, bool byPrice) const {
    if (byPrice) {
        return a->price < b->price;
    }
    return toLower(a->name) < toLower(b->name);
}

// Selection sort: by price or by name. Time: O(n^2)
void MenuList::sortMenu(bool byPrice) {
    if (head == nullptr || head->next == nullptr) return;

    for (MenuItem* i = head; i->next != nullptr; i = i->next) {
        MenuItem* smallest = i;
        // find the smallest item in the rest of the list

        for (MenuItem* j = i->next; j != nullptr; j = j->next) {
            if (isLess(j, smallest, byPrice)) {
                smallest = j;
            }
        }

        if (smallest != i) {
            swapData(i, smallest);
        }
    }
}

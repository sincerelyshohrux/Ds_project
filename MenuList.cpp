#include "MenuList.h"
#include <iostream>
#include <iomanip>
#include <utility>   // std::swap
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

// Returns a lowercase copy of the text (so "Pizza" and "pizza" are treated the same)
static string toLower(const string& text) {
    string result = text;
    for (size_t i = 0; i < result.size(); i++) {
        if (result[i] >= 'A' && result[i] <= 'Z') {
            result[i] = result[i] - 'A' + 'a';
        }
    }
    return result;
}

// Linear search by name. Time: O(n)
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

// Copies name and price of the item with the given ID. Time: O(n)
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
        cout << current->id << "\t" << fixed << setprecision(2) << current->price << "\t" << current->name << "\n";
        current = current->next;
    }
}

// Changes name and price of an existing item. Time: O(n)
bool MenuList::updateItem(int id, const string& newName, double newPrice) {
    MenuItem* item = findById(id);
    if (item == nullptr) return false;

    item->name = newName;
    item->price = newPrice;
    return true;
}

// Removes an item from the list. Time: O(n)
bool MenuList::deleteItem(int id) {
    if (head == nullptr) return false;

    // Case 1: the item to delete is the first node
    if (head->id == id) {
        MenuItem* temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    // Case 2: find the node BEFORE the one we want to delete
    MenuItem* current = head;
    while (current->next != nullptr && current->next->id != id) {
        current = current->next;
    }

    if (current->next == nullptr) return false;   // not found

    MenuItem* temp = current->next;
    current->next = temp->next;
    delete temp;
    return true;
}

// Swaps id, name and price of two nodes (the links stay the same)
void MenuList::swapData(MenuItem* a, MenuItem* b) {
    swap(a->id, b->id);
    swap(a->name, b->name);
    swap(a->price, b->price);
}

// Returns true if a should come before b
bool MenuList::isLess(MenuItem* a, MenuItem* b, bool byPrice) const {
    if (byPrice) {
        return a->price < b->price;
    }
    return toLower(a->name) < toLower(b->name);   // alphabetical, ignores upper/lower case
}

// Selection sort on the linked list. Time: O(n^2)
void MenuList::sortMenu(bool byPrice) {
    if (head == nullptr || head->next == nullptr) return;   // 0 or 1 item

    for (MenuItem* i = head; i->next != nullptr; i = i->next) {
        MenuItem* smallest = i;

        // find the smallest item in the remaining part
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

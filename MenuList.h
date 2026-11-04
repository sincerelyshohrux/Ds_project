#ifndef MENULIST_H
#define MENULIST_H

#include <string>

// One node of the menu linked list
struct MenuItem {
    int id;
    std::string name;
    double price;
    MenuItem* next;
};

// Menu stored as a singly linked list
class MenuList {
private:
    MenuItem* head;
    int nextId;   // auto-increment ID for new items

public:
    MenuList();
    ~MenuList();

    bool isEmpty() const;
    void addItem(const std::string& name, double price);
    void display() const;
};

#endif
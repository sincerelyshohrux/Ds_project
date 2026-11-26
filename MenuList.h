#ifndef MENULIST_H
#define MENULIST_H

#include <string>

// One menu item = one node of the linked list
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
    int nextId;

    MenuItem* findById(int id) const;
    void swapData(MenuItem* a, MenuItem* b);
    bool isLess(MenuItem* a, MenuItem* b, bool byPrice) const;

public:
    MenuList();
    ~MenuList();

    // Copying is not allowed (two lists would share the same nodes)
    MenuList(const MenuList&) = delete;
    MenuList& operator=(const MenuList&) = delete;

    bool isEmpty() const;
    void addItem(const std::string& name, double price);
    void display() const;
    bool updateItem(int id, const std::string& newName, double newPrice);
    bool deleteItem(int id);
    bool exists(int id) const;

    bool nameTaken(const std::string& name, int skipId) const;
    bool getItem(int id, std::string& name, double& price) const;
    void sortMenu(bool byPrice);
};

#endif

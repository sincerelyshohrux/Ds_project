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

    MenuItem* findById(int id) const;   // helper: returns nullptr if not found
    void swapData(MenuItem* a, MenuItem* b);   // helper: swaps the data of two nodes
    bool isLess(MenuItem* a, MenuItem* b, bool byPrice) const;   // helper: compares two nodes

public:
    MenuList();
    ~MenuList();

    bool isEmpty() const;
    void addItem(const std::string& name, double price);
    void display() const;
    bool updateItem(int id, const std::string& newName, double newPrice);
    bool deleteItem(int id);
    bool exists(int id) const;

    // Gets name and price of an item. Returns false if the ID does not exist.
    bool getItem(int id, std::string& name, double& price) const;

    // Sorts the menu. byPrice = true -> by price, false -> by name
    void sortMenu(bool byPrice);
};

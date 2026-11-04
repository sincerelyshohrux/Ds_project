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

public:
    MenuList();
    ~MenuList();

    bool isEmpty() const;
    void addItem(const std::string& name, double price);
    void display() const;
    bool updateItem(int id, const std::string& newName, double newPrice);
    bool deleteItem(int id);
    bool exists(int id) const;
};


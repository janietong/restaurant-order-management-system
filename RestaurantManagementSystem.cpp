#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// Structure to hold the details of an item in the menu
struct MenuItem {
    string name;
    double price;
};

// Structure to hold an order placed at a table
struct Order {
    string itemName;
    double price;
    int quantity;
};

// Class representing a restaurant table
class Table {
private:
    vector<Order> orders;
    bool isOccupied;

public:
    Table() : isOccupied(false) {}

    void addOrder(const string& itemName, double price, int quantity) {
        orders.push_back({itemName, price, quantity});
        isOccupied = true;
    }

    void removeOrder(const string& itemName) {
        for (auto it = orders.begin(); it != orders.end(); ++it) {
            if (it->itemName == itemName) {
                orders.erase(it);
                break;
            }
        }
        if (orders.empty()) {
            isOccupied = false;
        }
    }

    double calculateBill() const {
        double total = 0.0;
        for (const auto& order : orders) {
            total += order.price * order.quantity;
        }
        return total;
    }

    void clearOrders() {
        orders.clear();
        isOccupied = false;
    }

    bool getOccupiedStatus() const {
        return isOccupied;
    }

    void printOrders() const {
        if (orders.empty()) {
            cout << "No orders placed.\n";
            return;
        }

        cout << "Current Orders:\n";
        for (const auto& order : orders) {
            cout << order.quantity << " x " << order.itemName << " - $" << order.price << " each\n";
        }
        cout << "Total Bill: $" << calculateBill() << endl;
    }
};

// Class representing the restaurant management system
class Restaurant {
private:
    map<int, Table> tables;
    vector<MenuItem> menu;

public:
    Restaurant(int tableCount) {
        // Initialize tables
        for (int i = 1; i <= tableCount; ++i) {
            tables[i] = Table();
        }

        // Initialize menu
        menu.push_back({"Burger", 5.99});
        menu.push_back({"Pizza", 8.99});
        menu.push_back({"Pasta", 7.99});
        menu.push_back({"Salad", 4.99});
        menu.push_back({"Soda", 1.99});
    }

    void showMenu() const {
        cout << "\nMenu:\n";
        for (const auto& item : menu) {
            cout << item.name << " - $" << item.price << endl;
        }
    }

    void addOrder(int tableNumber, const string& itemName, int quantity) {
        auto it = find_if(menu.begin(), menu.end(), [&](const MenuItem& item) {
            return item.name == itemName;
        });

        if (it != menu.end()) {
            tables[tableNumber].addOrder(itemName, it->price, quantity);
            cout << "Order added to table " << tableNumber << endl;
        } else {
            cout << "Item not found on the menu.\n";
        }
    }

    void removeOrder(int tableNumber, const string& itemName) {
        tables[tableNumber].removeOrder(itemName);
        cout << "Order removed from table " << tableNumber << endl;
    }

    void calculateBill(int tableNumber) {
        double bill = tables[tableNumber].calculateBill();
        cout << "Total bill for table " << tableNumber << " is $" << bill << endl;
    }

    void printOrders(int tableNumber) const {
        cout << "Orders for table " << tableNumber << ":\n";
        tables.at(tableNumber).printOrders();
    }

    void clearTable(int tableNumber) {
        tables[tableNumber].clearOrders();
        cout << "Table " << tableNumber << " is now cleared and ready for new customers.\n";
    }

    void showOccupiedTables() const {
        cout << "Occupied Tables:\n";
        for (const auto& table : tables) {
            if (table.second.getOccupiedStatus()) {
                cout << "Table " << table.first << " is occupied.\n";
            }
        }
    }
};

int main() {
    Restaurant myRestaurant(5); // Create a restaurant with 5 tables

    int choice, tableNumber, quantity;
    string itemName;

    do {
        cout << "\nRestaurant Management System\n";
        cout << "1. Show Menu\n";
        cout << "2. Add Order\n";
        cout << "3. Remove Order\n";
        cout << "4. Show Orders for a Table\n";
        cout << "5. Calculate Bill for a Table\n";
        cout << "6. Clear Table\n";
        cout << "7. Show Occupied Tables\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                myRestaurant.showMenu();
                break;

            case 2:
                cout << "Enter table number: ";
                cin >> tableNumber;
                cout << "Enter item name: ";
                cin >> ws; // To consume the newline left in the buffer
                getline(cin, itemName);
                cout << "Enter quantity: ";
                cin >> quantity;
                myRestaurant.addOrder(tableNumber, itemName, quantity);
                break;

            case 3:
                cout << "Enter table number: ";
                cin >> tableNumber;
                cout << "Enter item name to remove: ";
                cin >> ws;
                getline(cin, itemName);
                myRestaurant.removeOrder(tableNumber, itemName);
                break;

            case 4:
                cout << "Enter table number: ";
                cin >> tableNumber;
                myRestaurant.printOrders(tableNumber);
                break;

            case 5:
                cout << "Enter table number: ";
                cin >> tableNumber;
                myRestaurant.calculateBill(tableNumber);
                break;

            case 6:
                cout << "Enter table number: ";
                cin >> tableNumber;
                myRestaurant.clearTable(tableNumber);
                break;

            case 7:
                myRestaurant.showOccupiedTables();
                break;

            case 0:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
                break;
        }
    } while (choice != 0);

    return 0;
}

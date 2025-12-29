#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>

using namespace std;
// Represents a single product in the inventory.
// Uses Encapsulation: Data members are private and accessed via public methods.
class Item {
private:
    int id;
    string name;
    string brand;
    int quantity;
    double price;

public:
    // Getters
    Item(int id, string name, string brand, int quantity, double price);
    int getId() const;
    string getName() const;
    string getBrand() const;
    int getQuantity() const;
    double getPrice() const;
    // Setters
    void setQuantity(int q);
    void setPrice(double p);
    // Displays item details in a formatted table row
    void display() const;
    // Prepares the item string for file saving (CSV format)
    string toFileString() const;
};

#endif
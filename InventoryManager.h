#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include "Item.h"
#include <vector>
#include <string>

using namespace std;

// Manages the collection of items.
// Handles business logic (Add, Delete, Search) and File I/O operations.
class InventoryManager {
private:
    vector<Item> items; // Using vector for dynamic storage
    string filename;
    void loadFromFile(); // Helper function for file persistence

public:
    InventoryManager();
    void addItem(int id, string name, string brand, int quantity, double price);
    void deleteItem(int id);
    void searchItem(string name);
    void updateItem(int id); 
    void displayAll();
    void saveToFile();
    // Extented Features
    void sortByName();
    void lowStockReport(int threshold);
};

#endif
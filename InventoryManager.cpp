#include "InventoryManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

InventoryManager::InventoryManager() {
    filename = "inventory_data.txt";
    loadFromFile(); // Automatically load data when program starts
}

void InventoryManager::addItem(int id, string name, string brand, int quantity, double price) {
    // Check for unique ID to prevent duplicates
    for(const auto& item : items) {
        if(item.getId() == id) {
            cout << "Hata: Bu ID zaten mevcut!\n";
            return;
        }
    }
    items.push_back(Item(id, name, brand, quantity, price));
    cout << "Urun eklendi.\n";
}

void InventoryManager::deleteItem(int id) {
    auto it = remove_if(items.begin(), items.end(), [id](const Item& item){
        return item.getId() == id;
    });

    if (it != items.end()) {
        items.erase(it, items.end());
        cout << "Urun silindi.\n";
    } else {
        cout << "Urun bulunamadi.\n";
    }
}

void InventoryManager::searchItem(string name) {
    bool found = false;
    cout << "\n--- ARAMA SONUCLARI ---\n";
    cout << left << setw(5) << "ID" << setw(20) << "Urun Adi" << setw(15) << "Marka" << setw(10) << "Adet" << setw(10) << "Fiyat" << endl;
    cout << "-----------------------------------------------------------------\n";
    for (const auto& item : items) {
        if (item.getName() == name) {
            item.display();
            found = true;
        }
    }
    if (!found) cout << "Kayit bulunamadi.\n";
}

void InventoryManager::updateItem(int id) {
    bool found = false;
    for (auto& item : items) {
        if (item.getId() == id) {
            int newQty;
            double newPrice;
            cout << "Yeni Adet: "; cin >> newQty;
            cout << "Yeni Fiyat: "; cin >> newPrice;
            item.setQuantity(newQty);
            item.setPrice(newPrice);
            cout << "Urun guncellendi.\n";
            found = true;
            break;
        }
    }
    if (!found) cout << "Urun bulunamadi.\n";
}

void InventoryManager::displayAll() {
    if (items.empty()) {
        cout << "Envanter bos.\n";
        return;
    }
    cout << "\n--- TUM URUNLER ---\n";
    cout << left << setw(5) << "ID" << setw(20) << "Urun Adi" << setw(15) << "Marka" << setw(10) << "Adet" << setw(10) << "Fiyat" << endl;
    cout << "-----------------------------------------------------------------\n";
    for (const auto& item : items) {
        item.display();
    }
}

void InventoryManager::saveToFile() {
    ofstream outFile(filename);
    if (!outFile) return;
    for (const auto& item : items) {
        outFile << item.toFileString() << endl;
    }
    outFile.close();
}

void InventoryManager::loadFromFile() {
    ifstream inFile(filename);
    if (!inFile.is_open()) return;

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string segment;
        vector<string> data;
        // Parse CSV format (comma separated values)
        while(getline(ss, segment, ',')) data.push_back(segment);

        if(data.size() == 5) {
            try {
                items.push_back(Item(stoi(data[0]), data[1], data[2], stoi(data[3]), stod(data[4])));
            } catch (...) { continue; }
        }
    }
    inFile.close();
}

void InventoryManager::sortByName() {
    if (items.empty()) { cout << "Veri yok.\n"; return; }
    // Using a Lambda function for custom sorting logic
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.getName() < b.getName();  // Alphabetical order
    });
    cout << "Isme gore siralandi.\n";
    displayAll();
}

void InventoryManager::lowStockReport(int threshold) {
    bool found = false;
    cout << "\n--- KRITIK STOK RAPORU (Limit: " << threshold << ") ---\n";
    cout << left << setw(5) << "ID" << setw(20) << "Urun Adi" << setw(15) << "Marka" << setw(10) << "Adet" << endl;
    cout << "------------------------------------------------------\n";
    for (const auto& item : items) {
        if (item.getQuantity() < threshold) {
            cout << left << setw(5) << item.getId() 
                 << setw(20) << item.getName() 
                 << setw(15) << item.getBrand()
                 << setw(10) << item.getQuantity() << endl;
            found = true;
        }
    }
    if (!found) cout << "Kritik seviyede urun yok.\n";
}
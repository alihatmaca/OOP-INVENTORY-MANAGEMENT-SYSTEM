#include <iostream>
#include <limits>
#include "InventoryManager.h"

using namespace std;

int main() {
    InventoryManager manager;
    int choice;

    while (true) {
        cout << "\n=== PROFESYONEL ENVANTER SISTEMI ===\n";
        cout << "1. Urun Ekle\n2. Urunleri Listele\n3. Urun Ara\n4. Urun Sil\n5. Urun Guncelle\n6. Kaydet ve Cik\n7. Sirala (A-Z)\n8. Kritik Stok Raporu\nSecim: ";
        
        if (!(cin >> choice)) {
            cout << "Sayi giriniz.\n"; 
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            continue;
        }

        if (choice == 1) {
            int id, qty; 
            string name, brand; 
            double price;
            
            cout << "ID: "; cin >> id;
            // Clear input buffer to handle getline properly after cin >>
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            
            cout << "Isim: "; 
            getline(cin, name); // Allows names with spaces
            
            cout << "Marka: "; 
            getline(cin, brand);

            cout << "Adet: "; cin >> qty;
            cout << "Fiyat: "; cin >> price;
            
            manager.addItem(id, name, brand, qty, price);
        }
        else if (choice == 2) {
            manager.displayAll();
        }
        else if (choice == 3) {
            string name;
            // Clear buffer before taking string input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Aranacak isim: "; 
            getline(cin, name);
            manager.searchItem(name);
        }
        else if (choice == 4) {
            int id; cout << "ID: "; cin >> id;
            manager.deleteItem(id);
        }
        else if (choice == 5) {
            int id; cout << "ID: "; cin >> id;
            manager.updateItem(id);
        }
        else if (choice == 6) {
            manager.saveToFile();
            break;
        }
        else if (choice == 7) manager.sortByName();
        else if (choice == 8) {
            int l; cout << "Limit: "; cin >> l;
            manager.lowStockReport(l);
        }
        else cout << "Gecersiz.\n";
    }
    return 0;
}
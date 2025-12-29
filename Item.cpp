#include "Item.h"
#include <iomanip>
#include <sstream> 

Item::Item(int id, string name, string brand, int quantity, double price) 
    : id(id), name(name), brand(brand), quantity(quantity), price(price) {}

int Item::getId() const { return id; }
string Item::getName() const { return name; }
string Item::getBrand() const { return brand; }
int Item::getQuantity() const { return quantity; }
double Item::getPrice() const { return price; }

void Item::setQuantity(int q) { quantity = q; }
void Item::setPrice(double p) { price = p; }

void Item::display() const {
    cout << left << setw(5) << id 
         << setw(20) << name 
         << setw(15) << brand 
         << setw(10) << quantity 
         << setw(10) << fixed << setprecision(2) << price << " TL" << endl;
}

string Item::toFileString() const {
    stringstream ss;
    // Format: ID,Name,Brand,Quantity,Price
    // Appending " TL" for readability in the text file
    ss << id << "," << name << "," << brand << "," << quantity << "," << fixed << setprecision(2) << price << " TL";
    return ss.str();
}
#include "../include/ConsoleHelper.h"
#include "../include/CART.h"
#include "../include/UI_config.h"
#include "../include/PRODUCT.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
using std::find_if;

using namespace std;

void CART::printMenu()
{
    cout << "[1] ➕ Add Item" << endl;
cout << "[2] ➖ Remove Item" << endl;
cout << "[3] ✏️ Update Quantity" << endl;
    cout << "[4] 📋 View Cart" << endl;
cout << "[5] 💰 Calculate Total" << endl;
    cout << "[0] ❌ Exit" << endl;
}

void CART::CartMenu()
{
    int choice;
    while (true) {
        ConsoleHelper::ClearScreen();
        ConsoleHelper::SetColor(11);
        cout << string(44, '=') << endl;
        cout << "             🛍️ CART MENU" << endl;
        cout << string(44, '=') << endl;
        ConsoleHelper::PrintDivider();
        ConsoleHelper::ResetColor();
        printMenu();
        cout << string(44, '-') << endl;
        cout << "Enter your choice: ";
        // Input validation
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            ConsoleHelper::PrintError();
            cout << "Invalid input. Press Enter to continue...";
            cin.ignore(10000, '\n');
            continue;
        }
        cin.ignore(10000, '\n');
        switch(choice)
        {
            case 1:
                {
                    string cat, name;
                    double price;
                    int qty;
                    ConsoleHelper::ClearScreen();
                    ConsoleHelper::SetColor(11);
                    cout << "Enter category: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, cat);
                    cout << "Enter product name: ";
                    getline(cin, name);
                    cout << "Enter price: ";
                    cin >> price;
                    cout << "Enter quantity: ";
                    cin >> qty;
                    PRODUCT p(cat, name, price, qty);
                    addItem(p);
                }
                break;
            case 2:
                {
                    string name;
                    ConsoleHelper::ClearScreen();
                    ConsoleHelper::SetColor(11);
                    cout << "Enter product name to remove: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, name);
                    removeItem(name);
                }
                break;
            case 3:
                {
                    string name;
                    int qty;
                    ConsoleHelper::ClearScreen();
                    ConsoleHelper::SetColor(11);
                    cout << "Enter product name to update: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, name);
                    cout << "Enter new quantity: ";
                    cin >> qty;
                    updateQuantity(name, qty);
                }
                break;
            case 4:
                viewCart();
                break;
            case 5:
                calculateTotal();
                break;
            case 0:
                cout << "Exiting cart menu." << endl;
                return;
            default:
                ConsoleHelper::PrintError();
                cout << "Invalid choice. Press Enter to continue...";
                cin.ignore(10000, '\n');
        }
        cout << "Press Enter to continue...";
        cin.ignore(10000, '\n');
    }
}

void CART::addItem(const PRODUCT product)
{
    cart_items.push_back(product);
    total_amount += product.getPrice() * product.getQuantity();
    ConsoleHelper::ClearScreen();
    ConsoleHelper::SetColor(10);
    ConsoleHelper::PrintHeader("ITEM ADDED SUCCESSFULLY");
    ConsoleHelper::PrintDivider();
    cout << "Product: " << product.getName() << " | Qty: " << product.getQuantity() << " | Price: Rs" << fixed << setprecision(2) << product.getPrice() << endl;
    ConsoleHelper::ResetColor();
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void CART::removeItem(const std::string product_name )
{
    auto it = find_if(cart_items.begin(), cart_items.end(), [&product_name](const PRODUCT& p) { return p.getName() == product_name; });
    if (it != cart_items.end()) {
        total_amount -= it->getPrice() * it->getQuantity();
        cart_items.erase(it);
        ConsoleHelper::ClearScreen();
        ConsoleHelper::SetColor(10);
        ConsoleHelper::PrintHeader("ITEM REMOVED SUCCESSFULLY");
        ConsoleHelper::PrintDivider();
        cout << product_name << " removed from cart!" << endl;
        ConsoleHelper::ResetColor();
    } else {
        ConsoleHelper::PrintError();
        cout << "Product not found!" << endl;
    }
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void CART::updateQuantity(const std::string product_name, int qnt)
{
    auto it = find_if(cart_items.begin(), cart_items.end(), [&product_name](const PRODUCT& p) { return p.getName() == product_name; });
    if (it != cart_items.end()) {
        total_amount -= it->getPrice() * it->getQuantity();
        it->setQuantity(qnt);
        total_amount += it->getPrice() * qnt;
        ConsoleHelper::ClearScreen();
        ConsoleHelper::SetColor(10);
        ConsoleHelper::PrintHeader("QUANTITY UPDATED SUCCESSFULLY");
        ConsoleHelper::PrintDivider();
        cout << product_name << " quantity updated to " << qnt << endl;
        ConsoleHelper::ResetColor();
    } else {
        ConsoleHelper::PrintError();
        cout << "Product not found!" << endl;
    }
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void CART::viewCart()
{
    ConsoleHelper::ClearScreen();
    ConsoleHelper::PrintDivider();
    cout << endl;
    ConsoleHelper::PrintDivider();
    cout << endl;
    ConsoleHelper::SetColor(11);
    cout << string(62, '=') << endl;
    cout << "             🛒 YOUR CART" << endl;
    cout << string(62, '=') << endl;
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
    if (cart_items.empty()) {
        cout << "Your cart is empty. Add items to view contents." << endl;
    } else {
        cout << left << setw(20) << "Product Name" << setw(10) << "Quantity" << setw(12) << "Price" << setw(15) << "Category" << endl;
        ConsoleHelper::PrintDivider();
        int total_qty = 0;
        for (const auto& p : cart_items) {
            cout << left << setw(20) << p.getName() << setw(10) << p.getQuantity() << setw(12) << fixed << setprecision(2) << p.getPrice() << setw(15) << p.getCategory() << endl;
            total_qty += p.getQuantity();
        }
        ConsoleHelper::PrintDivider();
        cout << endl;
        cout << left << setw(30) << "TOTAL ITEMS: " << total_qty << endl;
        cout << left << setw(30) << "TOTAL AMOUNT: Rs" << fixed << setprecision(2) << total_amount << endl;
    }
    ConsoleHelper::PrintDivider();
    cout << endl;
    cout << "Press Enter to continue...";
    cin.ignore(10000, '\n');
}

double CART::calculateTotal()
{
    ConsoleHelper::ClearScreen();
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("CART TOTAL");
    ConsoleHelper::PrintDivider();
    ConsoleHelper::ResetColor();
cout << fixed << setprecision(2);
    cout << "Total amount: Rs" << total_amount << endl;
    cout << "Press Enter to continue...";
    cin.ignore(10000, '\n');
    return total_amount;
}


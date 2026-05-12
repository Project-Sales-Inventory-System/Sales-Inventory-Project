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

int CART::getItemCount() const {
    return static_cast<int>(cart_items.size());
}

void CART::printMenu() {
    ConsoleHelper::SetColor(15);
    ConsoleHelper::PrintDivider();
    ConsoleHelper::SetColor(10);
    std::cout << "[1] Add Item" << std::endl;
    std::cout << "[2] Remove Item" << std::endl;
    std::cout << "[3] Update Quantity" << std::endl;
    std::cout << "[4] View Cart" << std::endl;
    std::cout << "[5] Calculate Total" << std::endl;
    std::cout << "[0] Exit" << std::endl;
    ConsoleHelper::SetColor(15);
    ConsoleHelper::PrintDivider();
}

void CART::CartMenu() {
    int choice;
    while (true) {
        ConsoleHelper::ClearScreen();
        ConsoleHelper::Header();
    const int terminalWidth = 80;
    std::string line = std::string(44, '=');
    std::string message = "    CART MENU";

    int padding = (terminalWidth - line.length()) / 2;
    
    ConsoleHelper::SetColor(15);
    std::cout << std::string(padding, ' ') << line << std::endl;
    ConsoleHelper::SetColor(10);
    std::cout << std::string(padding, ' ') << message << std::endl;
    ConsoleHelper::SetColor(15);
    std::cout << std::string(padding, ' ') << line << std::endl;

    ConsoleHelper::ResetColor();
        printMenu();
        std::cout << std::string(44, '-') << std::endl;
        std::cout << "Enter your choice: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            ConsoleHelper::SetColor(12);
            std::cout << "⚠️ Invalid input!!!" << std::endl;
            ConsoleHelper::SetColor(13);
            std::cout << "Press Enter to continue...";
            std::cin.ignore(10000, '\n');
            continue;
        }
        std::cin.ignore(10000, '\n');

        switch (choice) {
            case 1: {
                std::string cat, name;
                double price;
                int qty;
                ConsoleHelper::ClearScreen();
                ConsoleHelper::SetColor(7);
                std::cout << "Enter category: ";
                std::getline(std::cin >> std::ws, cat);
                std::cout << "Enter product name: ";
                std::getline(std::cin, name);
                std::cout << "Enter price: ";
                std::cin >> price;
                std::cout << "Enter quantity: ";
                std::cin >> qty;
                PRODUCT p(cat, name, price, qty);
                addItem(p);
                ConsoleHelper::ResetColor();
                break;
            }
            case 2: {
                std::string name;
                ConsoleHelper::ClearScreen();
                ConsoleHelper::SetColor(7);
                std::cout << "Enter product name to remove: ";
                std::getline(std::cin >> std::ws, name);
                removeItem(name);
                ConsoleHelper::ResetColor();
                break;
            }
            case 3: {
                std::string name;
                int qty;
                ConsoleHelper::ClearScreen();
                ConsoleHelper::ResetColor();
                std::cout << "Enter product name to update: ";
                std::getline(std::cin, name);
                std::cout << "Enter new quantity: ";
                std::cin >> qty;
                updateQuantity(name, qty);
                break;
            }
            case 4:
                viewCart();
                break;
            case 5:
                calculateTotal();
                break;
            case 0:
                std::cout << "Exiting cart menu." << std::endl;
                ConsoleHelper::ResetColor();
                return;
            default:
                ConsoleHelper::SetColor(12);
                std::cout << "⚠️ Invalid choice!!! " << std::endl;
                ConsoleHelper::SetColor(13);
                std::cout << " Press Enter to continue...";
                std::cin.ignore(10000, '\n');
                ConsoleHelper::ResetColor();
        }
        ConsoleHelper::SetColor(13);
        std::cout << "Press Enter to continue...";
        std::cin.ignore(10000, '\n');
    }
}

void CART::addItem(const PRODUCT product) {
    cart_items.push_back(product);
    total_amount += product.getPrice() * product.getQuantity();
    ConsoleHelper::ClearScreen();
    ConsoleHelper::SetColor(10);
    ConsoleHelper::PrintHeader("ITEM ADDED SUCCESSFULLY");
    ConsoleHelper::SetColor(7);
    std::cout << std::left << std::setfill(' ') << std::setw(20) << "Product" << "|" << std::setw(10) << "Qty" << "|" << std::setw(15) << "Price (Rs)" << std::endl;
    ConsoleHelper::ResetColor();

    std::cout << std::string(20, '-') << "+" << std::string(10, '-') << "+" << std::string(15, '-') << std::endl;
    
    for (const auto& item : cart_items) {
        std::cout << std::left << std::setfill(' ') << std::setw(20) << item.getName() << "|" 
                  << std::setw(10) << item.getQuantity() << "|" 
                  << std::setw(15) << std::fixed << std::setprecision(2) << item.getPrice() << std::endl;
    }

    std::cout << std::string(20, '-') << "+" << std::string(10, '-') << "+" << std::string(15, '-') << std::endl;
}

void CART::removeItem(const std::string product_name) {
    auto it = std::find_if(cart_items.begin(), cart_items.end(), 
        [&product_name](const PRODUCT& p) { return p.getName() == product_name; });
    
    if (it != cart_items.end()) {
        total_amount -= it->getPrice() * it->getQuantity();
        cart_items.erase(it);
        ConsoleHelper::ClearScreen();
        ConsoleHelper::SetColor(10);
        ConsoleHelper::PrintHeader("ITEM REMOVED SUCCESSFULLY");
        ConsoleHelper::SetColor(13);
        std::cout << product_name << " ➖ removed from cart!" << std::endl;
    } else {
        ConsoleHelper::PrintError();
        ConsoleHelper::SetColor(12);
        std::cout << "⚠️ Product not found!" << std::endl;
    }
}

void CART::updateQuantity(const std::string product_name, int qnt) {
    auto it = std::find_if(cart_items.begin(), cart_items.end(), 
        [&product_name](const PRODUCT& p) { return p.getName() == product_name; });
    
    if (it != cart_items.end()) {
        total_amount -= it->getPrice() * it->getQuantity();
        it->setQuantity(qnt);
        total_amount += it->getPrice() * qnt;
        ConsoleHelper::ClearScreen();
        ConsoleHelper::SetColor(10);
        ConsoleHelper::PrintHeader("QUANTITY UPDATED SUCCESSFULLY");
        ConsoleHelper::PrintDivider();
        std::cout << product_name << " quantity updated to " << qnt << std::endl;
        ConsoleHelper::ResetColor();
    } else {
        ConsoleHelper::SetColor(12);
        std::cout << "⚠️ Product not found!" << std::endl;
        ConsoleHelper::SetColor(7);
    }
}
void CART::viewCart() {
    ConsoleHelper::SetColor(10);
    ConsoleHelper::PrintHeader("CART ITEMS");
    ConsoleHelper::SetColor(15);
    ConsoleHelper::PrintDivider();
    
    if (cart_items.empty()) {
        ConsoleHelper::SetColor(12);
        std::cout << "⚠️ Cart is empty!" << std::endl;
        ConsoleHelper::ResetColor();
        return;
    }

    ConsoleHelper::SetColor(10);
    std::cout << std::left << std::setfill(' ') << std::setw(20) << "Product" << "|" 
              << std::setw(10) << "Qty" << "|" 
              << std::setw(15) << "Price (Rs)" << std::endl;
    ConsoleHelper::ResetColor();
    std::cout << std::string(20, '-') << "+" << std::string(10, '-') << "+" << std::string(15, '-') << std::endl;

    for (const auto& item : cart_items) {
        std::cout << std::left << std::setfill(' ') << std::setw(20) << item.getName() << "|"
                  << std::setw(10) << item.getQuantity() << "|"
                  << std::setw(15) << std::fixed << std::setprecision(2) << item.getPrice() << std::endl;
    }

    std::cout << std::string(20, '-') << "+" << std::string(10, '-') << "+" << std::string(15, '-') << std::endl;
    std::cout << "Total: Rs" << std::fixed << std::setprecision(2) << total_amount << std::endl;
    ConsoleHelper::ResetColor();
}
double CART::calculateTotal() {
    ConsoleHelper::ClearScreen();
    ConsoleHelper::SetColor(10);
    ConsoleHelper::PrintHeader("CART TOTAL");
    ConsoleHelper::ResetColor();
    ConsoleHelper::SetColor(15);
    ConsoleHelper::PrintDivider();
    ConsoleHelper::SetColor(7);
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Total amount: Rs" << total_amount << std::endl;
    ConsoleHelper::SetColor(15);
    ConsoleHelper::PrintDivider();
    ConsoleHelper::SetColor(7);
    return total_amount;
}

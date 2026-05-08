#pragma once
#include <string>
#include <vector>
#include "PRODUCT.h"

class CART {
    friend class BILL;
private:
    std::vector<PRODUCT> cart_items;
    double total_amount;

public:
    CART() : total_amount(0.0) {}
    
    void printMenu(); 
    void CartMenu();

    int getItemCount() const;
    void addItem(const PRODUCT product);
    void removeItem(const std::string product_name);
    void updateQuantity(const std::string product_name, int qnt);
    void viewCart();
    double calculateTotal();
    const std::vector<PRODUCT>& getItems() const { return cart_items; }
};
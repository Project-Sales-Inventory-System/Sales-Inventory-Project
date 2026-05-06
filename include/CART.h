#pragma once
#include<string>
#include "../include/PRODUCT.h"
#include <vector>
class CART
{
    friend class BILL;
    private:
    std::vector<PRODUCT> cart_items;
    double total_amount;
    public:
    int getItemCount() const;
    void printMenu();
    void CartMenu();
    void addItem(const PRODUCT product);
    void removeItem(const std::string product_name);
    void updateQuantity(const std::string product_name, int qnt);
    void viewCart();
    double calculateTotal();
};
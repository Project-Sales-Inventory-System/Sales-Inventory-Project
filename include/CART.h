/*

CART class represents a shopping cart used by customers to store products before purchasing.

STANDARD LIBRARIES USED:
-vector:Used for storing collections of data.
-string:Used for text handling.

FRIEND CLASS:
-BILL:Allows BILL class to directly access private members of CART.

PRIVATE DATA MEMBERS:
-cart_items:Vector storing all products added to the cart.
-total_amount:Stores total price of all items in the cart.

PUBLIC FUNCTIONS:
-CART():Default constructor initializing total amount to 0.0.
-printMenu():Displays cart-related menu options.
-CartMenu():Handles cart menu operations.
-getItemCount() const:Returns total number of items in the cart.
-addItem(const PRODUCT product):Adds a product to the cart.
-removeItem(const std::string product_name):Removes a product from the cart using product name.
-updateQuantity(const std::string product_name, int qnt):Updates quantity of a specific product in the cart.
-viewCart():Displays all products currently in the cart.
-calculateTotal():Calculates and returns total cart amount.
-getItems() const:Returns all cart items.

*/

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
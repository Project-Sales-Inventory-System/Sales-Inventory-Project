#include<cassert>
#include<iostream>
#include<sstream>
#include<string>
#include<iomanip>
#include"../include/CART.h"
#include"../include/PRODUCT.h"

int main(){

    CART cart;

    // Test initial state
    assert(cart.getItemCount() == 0);

    // Test addItem
    PRODUCT p1("Clothes", "Shirt", 1000.0, 2);
    cart.addItem(p1);
    assert(cart.getItemCount() == 1);

    // Test add another item
    PRODUCT p2("Electronics", "Phone", 20000.0, 1);
    cart.addItem(p2);
    assert(cart.getItemCount() == 2);
     
    // test add non-existing item
    PRODUCT p3("nonExisting", "nonExistingItem", 500.0, 5);
    cart.addItem(p3);
    assert(cart.getItemCount() == 2);

    // Test removeItem
    cart.removeItem("Shirt");
    assert(cart.getItemCount() == 1);

    // Test remove non-existing
    cart.removeItem("Shirt");
    assert(cart.getItemCount() == 1);

    // Test updateQuantity
    cart.updateQuantity("Phone", 3);
    assert(p2.getQuantity() == 3);

    // Test update non-existing
    cart.updateQuantity("Shirt", 5);
    assert(p1.getQuantity() == 0);

    // Test viewCart
    {
        std::ostringstream buffer;
        std::streambuf* old_cout = std::cout.rdbuf(buffer.rdbuf());
        cart.viewCart();
        std::cout.rdbuf(old_cout);
        assert(!buffer.str().empty());
        assert(buffer.str().find("Phone") != std::string::npos);
        assert(buffer.str().find("Shirt") == std::string::npos);
    }

    // Test calculateTotal
    {
        std::ostringstream buffer;
        std::streambuf* old_cout = std::cout.rdbuf(buffer.rdbuf());
        double total = cart.calculateTotal();
        std::cout.rdbuf(old_cout);
        assert(total == 60000.0); // 20000 * 3
        assert(!buffer.str().empty());
        assert(buffer.str().find("60000.00") != std::string::npos);
    }
    
    std::cout << "All CART tests passed!" << std::endl;
    return 0;
}
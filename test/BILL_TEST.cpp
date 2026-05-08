#include<cassert>
#include<iostream>
#include<sstream>
#include<cmath>
#include"../include/BILL.h"
#include"../include/PRODUCT.h"
#include"../include/CART.h"

using namespace std;

int main(){
    //generateBill with Empty Cart
    {
        CART cart;
        BILL bill(104, 20, cart);
        bill.generateBill();
    
        assert(bill.getItemCount() == 0);
        assert(bill.getTotalAmount() == 0.0f);
    }

    //generateBill with Multiple Items
    {
        CART cart;
        PRODUCT p1("Electronics", "Mouse", 1500.0, 2);
        PRODUCT p2("Electronics", "Keyboard", 3000.0, 1);
        PRODUCT p3("Accessories", "USB Cable", 200.0, 5);
    
        cart.addItem(p1);
        cart.addItem(p2);
        cart.addItem(p3);
    
        BILL bill(103, 15, cart);
        bill.generateBill();
    
        assert(bill.getItemCount() == 8);  // 2 + 1 + 5
        assert(std::abs(bill.getTotalAmount() - 7000.0)< 0.01);  // (1500*2) + (3000*1) + (200*5)
    }

    //getCurrentDate Format
    {
        CART cart;
        BILL bill(105, 25, cart);
    
        bill.generateBill();
    
        assert(!bill.getDate().empty());
        assert(bill.getDate().length() == 10);  // Format: YYYY-MM-DD
        assert(bill.getDate()[4] == '-');
        assert(bill.getDate()[7] == '-');
    }

    //displayBill Execution (Ensure it doesn't crash)
    {
        CART cart;
        PRODUCT p1("Electronics", "Phone", 30000.0, 1);
        PRODUCT p2("Electronics", "Charger", 500.0, 2);
    
        cart.addItem(p1);
        cart.addItem(p2);
    
        BILL bill(110, 50, cart);
        bill.generateBill();
    
        stringstream buffer;
        streambuf* old = cout.rdbuf(buffer.rdbuf());
    
        bill.displayBill();
    
        cout.rdbuf(old);
    
        assert(bill.getItemCount() == 3);
        assert(std::abs(bill.getTotalAmount() - 31000.0)<0.01);
        assert(bill.getPaymentStatus() == "⚠️ UNPAID");
    }   
    
    std::cout <<"All BILL tests passed sucssfully!" << std::endl;

    return 0;
}
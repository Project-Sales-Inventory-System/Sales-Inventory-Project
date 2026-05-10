#include<cassert>
#include<iostream>
#include<sstream>
#include<cmath>
#include"../include/BILL.h"
#include"../include/PRODUCT.h"
#include"../include/CART.h"

using namespace std;

int main(){

    // test default constructor
    {
        BILL bill;
        assert(bill.getBillId() == 0);
        assert(bill.getUserId() == 0);
        assert(bill.getItemCount() == 0);
        assert(bill.getTotalAmount() == 0.0);
        assert(bill.getPaymentStatus() == "UNPAID");
    }

    // test generateBill with empty cart
    {
        CART cart;
        BILL bill(104, 20, cart);
        bill.generateBill();

        assert(bill.getItemCount() == 0);
        assert(bill.getTotalAmount() == 0.0);
    }

    // test generateBill with multiple items
    {
        CART cart;
        PRODUCT p1("Electronics", "Mouse", 1500.0, 2);    // 3000
        PRODUCT p2("Electronics", "Keyboard", 3000.0, 1); // 3000
        PRODUCT p3("Accessories", "USB Cable", 200.0, 5); // 1000

        cart.addItem(p1);
        cart.addItem(p2);
        cart.addItem(p3);

        BILL bill(103, 15, cart);
        bill.generateBill();

        assert(bill.getItemCount() == 8);  // 2+1+5
        assert(std::abs(bill.getTotalAmount() - 7000.0) < 0.01);
    }

    // test getBillId and getUserId
    {
        CART cart;
        BILL bill(42, 99, cart);

        assert(bill.getBillId() == 42);
        assert(bill.getUserId() == 99);
    }

    // test setBillId and setCustomerId
    {
        CART cart;
        BILL bill(1, 1, cart);

        bill.setBillId(100);
        bill.setCustomerId(200);

        assert(bill.getBillId() == 100);
        assert(bill.getUserId() == 200);
    }

    // test confirmPayment
    {
        CART cart;
        BILL bill(101, 10, cart);
        bill.generateBill();

        assert(bill.getPaymentStatus() == "UNPAID");
        bill.confirmPayment();
        assert(bill.getPaymentStatus() == "PAID");
    }

    // test setPaymentStatus
    {
        CART cart;
        BILL bill(102, 11, cart);

        bill.setPaymentStatus("PAID");
        assert(bill.getPaymentStatus() == "PAID");

        bill.setPaymentStatus("UNPAID");
        assert(bill.getPaymentStatus() == "UNPAID");
    }


    // test9: addItem multiple
    {
        BILL bill;
        PRODUCT p1("Electronics", "Laptop", 50000.0, 1); // 50000
        PRODUCT p2("Clothes", "Shirt", 500.0, 3);         // 1500

        bill.addItem(p1);
        bill.addItem(p2);

        assert(bill.getItemCount() == 4);          // 1+3
        assert(bill.getTotalAmount() == 51500.0);
        assert(bill.getItems().size() == 2);
    }

    // test getDate after generateBill
    {
        CART cart;
        BILL bill(105, 25, cart);
        bill.generateBill();

        assert(!bill.getDate().empty());
        assert(bill.getDate().length() == 10); // YYYY-MM-DD
        assert(bill.getDate()[4] == '-');
        assert(bill.getDate()[7] == '-');
        
    }

    // test displayBill output
    {
        CART cart;
        PRODUCT p1("Electronics", "Phone", 30000.0, 1);
        PRODUCT p2("Electronics", "Charger", 500.0, 2);

        cart.addItem(p1);
        cart.addItem(p2);

        BILL bill(110, 50, cart);
        bill.generateBill();

        stringstream input("\n");  
        streambuf* oldCin = cin.rdbuf(input.rdbuf());
        stringstream buffer;
        streambuf* oldCout = cout.rdbuf(buffer.rdbuf());

        bill.displayBill();

        cin.rdbuf(oldCin);
        cout.rdbuf(oldCout);

        assert(buffer.str().find("Phone") != string::npos);
        assert(buffer.str().find("Charger") != string::npos);
        assert(buffer.str().find("31000.00") != string::npos);
        assert(buffer.str().find("110") != string::npos); 
    }

    // test getItems returns correct products
    {
        CART cart;
        PRODUCT p("Electronics", "Laptop", 50000.0, 2);
        cart.addItem(p);

        BILL bill(1, 1, cart);
        const auto& items = bill.getItems();

        assert(items.size() == 1);
        assert(items[0].getName() == "Laptop");
        assert(items[0].getPrice() == 50000.0);
    }

    std::cout << "All BILL tests passed successfully!" << std::endl;
    return 0;
}
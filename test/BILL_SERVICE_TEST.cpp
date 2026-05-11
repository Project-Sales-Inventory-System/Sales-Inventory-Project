#include<cassert>
#include<iostream>
#include<sstream>
#include<cstdio>
#include<fstream>
#include"../include/BILL_SERVICE.h"
#include"../include/BILL.h"
#include"../include/CART.h"
#include"../include/PRODUCT.h"
#include"../include/PRODUCT_REPO.h"

using namespace std;

int main()
{
    

    // test createBILL - empty cart
    {
        remove("sales_history.csv");
        BILL_SERVICE bs;
        CART cart;

        BILL bill = bs.createBILL(cart, 1);

        assert(bill.getBillId() == 1);
        assert(bill.getUserId() == 1);
        assert(bill.getItemCount() == 0);
        assert(bill.getTotalAmount() == 0.0);
        assert(bill.getPaymentStatus() == "UNPAID");
    }

    // test createBILL - with items
    {
        BILL_SERVICE bs;
        CART cart;

        PRODUCT p1("Electronics", "Laptop", 50000.0, 1);
        PRODUCT p2("Clothes", "Shirt", 500.0, 2);
        cart.addItem(p1);
        cart.addItem(p2);

        BILL bill = bs.createBILL(cart, 5);

        assert(bill.getBillId() == 2);
        assert(bill.getUserId() == 5);
        assert(bill.getItemCount() == 3);        // 1+2
        assert(bill.getTotalAmount() == 51000.0); // 50000+1000
        assert(bill.getPaymentStatus() == "UNPAID");
        
    }

    //createBILL - bill_count increments
    {
        BILL_SERVICE bs;
        CART cart;

        BILL bill1 = bs.createBILL(cart, 1);
        BILL bill2 = bs.createBILL(cart, 2);
        BILL bill3 = bs.createBILL(cart, 3);

        assert(bill1.getBillId() == 3);
        assert(bill2.getBillId() == 4);
        assert(bill3.getBillId() == 5);
    }

    // test autoGenerateBill - empty cart
    {
        BILL_SERVICE bs;
        CART cart;

        BILL bill = bs.autoGenerateBill(cart);

        assert(bill.getBillId() == 6);
        assert(bill.getUserId() == 0);
        assert(bill.getItemCount() == 0);
        assert(bill.getTotalAmount() == 0.0);
    }

    // test6: autoGenerateBill - with items
    {
        BILL_SERVICE bs;
        CART cart;

        PRODUCT p("Electronics", "Laptop", 50000.0, 2);
        cart.addItem(p);

        BILL bill = bs.autoGenerateBill(cart);

        assert(bill.getItemCount() == 2);
        assert(bill.getTotalAmount() == 100000.0);
        assert(bill.getUserId() == 0); // auto generated, no user
    }

    // test autoConfirmSale - valid bill
    {
        remove("my_file.csv");
        BILL_SERVICE bs;
        PRODUCT_REPO repo;

        PRODUCT p("Electronics", "Laptop", 50000.0, 2);
        repo.addProduct(p);

        CART cart;
        cart.addItem(p);

        BILL bill = bs.createBILL(cart, 1);
        assert(bill.getPaymentStatus() == "UNPAID");

        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
        bs.autoConfirmSale(bill.getBillId(), repo);
        std::cout.rdbuf(oldCout);

        assert(output.str().find("Sale confirmed") != string::npos);
    }

    // test autoConfirmSale - invalid bill id
    {
        BILL_SERVICE bs;
        PRODUCT_REPO repo;

        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
        bs.autoConfirmSale(999, repo); 
        std::cout.rdbuf(oldCout);
        assert(output.str().find("Bill ID #999⚠️ not found.") != string::npos);
    }

    
    // test getSaleReport - no bills
    {
        remove("sales_history.csv");
        BILL_SERVICE bs;

        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
        bs.getSaleReport();
        std::cout.rdbuf(oldCout);

        assert(output.str().find("No sales recorded.") != string::npos);
    }

    // test getSaleReport - with paid bills
    {
        remove("sales_history.csv");
        remove("my_file.csv");
        BILL_SERVICE bs;
        PRODUCT_REPO repo;

        PRODUCT p("Electronics", "Laptop", 50000.0, 1);
        repo.addProduct(p);

        CART cart;
        cart.addItem(p);

        BILL bill = bs.createBILL(cart, 1);
        bs.autoConfirmSale(bill.getBillId(), repo);

        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
        bs.getSaleReport();
        std::cout.rdbuf(oldCout);

        assert(output.str().find("SALES REPORT") != string::npos);
        assert(output.str().find("PAID") != string::npos);
        assert(output.str().find("50000.00") != string::npos);
        assert(output.str().find("Total Sales: 1") != string::npos);
    }

    // test getSaleReport - unpaid bills not shown
    {
        remove("sales_history.csv");
        remove("my_file.csv");
        BILL_SERVICE bs;

        CART cart;
        PRODUCT p("Electronics", "Laptop", 50000.0, 1);
        cart.addItem(p);

        bs.createBILL(cart, 1); // unpaid bill

        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
        bs.getSaleReport();
        std::cout.rdbuf(oldCout);

        assert(output.str().find("Total Sales: 0") != string::npos);
        
    }

    std::cout << "All BILL_SERVICE tests passed!" << std::endl;
    return 0;
}
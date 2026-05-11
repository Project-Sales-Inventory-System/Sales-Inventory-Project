#include <cassert>
#include <iostream>
#include <sstream>
#include <cstdio>
#include "../include/BUYER.h"
#include "../include/PRODUCT_REPO.h"
#include "../include/BILL_SERVICE.h"
#include "../include/USER_ACCOUNT.h"
#include "../include/PRODUCT.h"
#include "../include/CART.h"

using namespace std;

int main() {
    PRODUCT_REPO repo;
    BILL_SERVICE bs;
    USER_ACCOUNT acc("Rakhi Sah", "rakhiiiii64", "1234", "9800000000", 19, "biratnagar", "abc@gmail.com", ClientBUYER);
    BUYER buyer(acc, repo, bs);

    //getUsername
    {
        assert(buyer.getUsername() == "rakhiiiii64");
    }

    //getCartItemCount - empty cart initially
    {
        assert(buyer.getCartItemCount() == 0);
    }

    //getCartTotal - empty cart
    {
        assert(buyer.getCartTotal() == 0.0);
    }

    //getCartItemCount - after adding item via LOCAL repo (not shared)
    {
        PRODUCT_REPO localRepo;
        BUYER localBuyer(acc, localRepo, bs);
        PRODUCT p("Electronics", "Laptop", 50000.0, 3);
        localRepo.addProduct(p);
        assert(localBuyer.getCartItemCount() == 0);
    }

    //two buyers have independent carts
    {
        USER_ACCOUNT account1("Pranali Rathod", "pranali123", "efg123", "9812983450", 40, "delhi", "efg@gmail.com", ClientBUYER);
        USER_ACCOUNT account2("Shraddha Kapoor", "shraddha123", "efg123", "9856712340", 40, "mumbai", "xyz@gmail.com", ClientSELLER);

        BUYER buyer1(account1, repo, bs);
        BUYER buyer2(account2, repo, bs);

        assert(buyer1.getCartItemCount() == 0);
        assert(buyer2.getCartItemCount() == 0);
        assert(buyer1.getUsername() != buyer2.getUsername());
    }

    //performAction
    {
        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
        buyer.performAction();
        std::cout.rdbuf(oldCout);

        assert(output.str().find("Buyer interacting") != string::npos);
    }

    //viewProduct - does not crash with empty repo
    {
        remove("my_file.csv");
        PRODUCT_REPO freshRepo;
        BUYER Buyer(acc, freshRepo, bs);

        stringstream input("\n");
        streambuf* oldCin = cin.rdbuf(input.rdbuf());
        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

        Buyer.viewProduct("");

        std::cout.rdbuf(oldCout);
        cin.rdbuf(oldCin);

        assert(output.str().find("Laptop") == string::npos);
        assert(output.str().find("Shirt") == string::npos);
    }

    //viewProduct - with products in repo
    {
        remove("my_file.csv");
        PRODUCT_REPO freshRepo;
        BUYER Buyer(acc, freshRepo, bs);

        PRODUCT p("Clothes", "Shirt", 500.0, 5);
        freshRepo.addProduct(p);

        stringstream input("\n");
        streambuf* oldCin = cin.rdbuf(input.rdbuf());
        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

        Buyer.viewProduct("");

        std::cout.rdbuf(oldCout);
        cin.rdbuf(oldCin);

        assert(output.str().find("Shirt") != string::npos);
        assert(output.str().find("500") != string::npos);
    }

    // searchProduct tests
    {
        remove("my_file.csv");
        PRODUCT_REPO freshRepo;
        PRODUCT p1("Electronics", "Laptop", 50000.0, 5);
        PRODUCT p2("Clothes", "Shirt", 500.0, 20);
        PRODUCT p3("Books", "C++ Programming", 1500.0, 10);
        freshRepo.addProduct(p1);
        freshRepo.addProduct(p2);
        freshRepo.addProduct(p3);

        BUYER Buyer(acc, freshRepo, bs);

        //search by category first, then by name, add to cart, view cart, exit
        {
            stringstream input(
                "2\n"        // search by category first
                "Clothes\n"  // category → Shirt appears here
                "S\n"        // search again
                "1\n"        // search by name
                "Laptop\n"   // product name
                "1A\n"       // add index 1 to cart
                "2\n"        // quantity
                "V\n"        // view cart
                "0\n"        // exit
            );

            streambuf* oldCin = cin.rdbuf(input.rdbuf());
            stringstream output;
            streambuf* oldCout = cout.rdbuf(output.rdbuf());

            Buyer.searchProduct("");

            cin.rdbuf(oldCin);
            cout.rdbuf(oldCout);

            string result = output.str();

            assert(result.find("SEARCH PRODUCTS") != string::npos);
            assert(result.find("Enter product category to search:") != string::npos);
            assert(result.find("Shirt") != string::npos);
            assert(result.find("Enter product name to search:") != string::npos);
            assert(result.find("Laptop") != string::npos);
            assert(result.find("added to Cart") != string::npos);
        }

        //empty name and empty category give error messages
        {
            stringstream input(
                "1\n"    // search by name
                "\n"     // empty name → error → falls to "No result found" → cin.get() eats this
                "2\n"    // searchChoice = 2 (category)
                "\n"     // empty category → error → falls to "No result found" → cin.get() eats this  
                "3\n"    // exit
            );

            streambuf* oldCin = cin.rdbuf(input.rdbuf());
            stringstream output;
            streambuf* oldCout = cout.rdbuf(output.rdbuf());

            Buyer.searchProduct("");

            cin.rdbuf(oldCin);
            cout.rdbuf(oldCout);

            string result = output.str();

            assert(result.find("SEARCH PRODUCTS") != string::npos);
            assert(result.find("Error: Product name cannot be empty!") != string::npos);
            assert(result.find("No result found. Press Enter...") != string::npos);
        }

        //search non-existing product and category
        {
            stringstream input(
                "1\n"      // search by name
                "Mouse\n"  // non-existing product
                "\n"
                "2\n"      // search by category
                "Food\n"   // non-existing category
                "\n"
                "3\n"      // exit
            );

            streambuf* oldCin = cin.rdbuf(input.rdbuf());
            stringstream output;
            streambuf* oldCout = cout.rdbuf(output.rdbuf());

            Buyer.searchProduct("");

            cin.rdbuf(oldCin);
            cout.rdbuf(oldCout);

            string result = output.str();

            assert(result.find("SEARCH PRODUCTS") != string::npos);
            assert(result.find("No result found") != string::npos);
        }

        //invalid menu choice then exit
        {
            stringstream input(
                "5\n"  // invalid choice
                "3\n"  // exit
            );

            streambuf* oldCin = cin.rdbuf(input.rdbuf());
            stringstream output;
            streambuf* oldCout = cout.rdbuf(output.rdbuf());

            Buyer.searchProduct("");

            cin.rdbuf(oldCin);
            cout.rdbuf(oldCout);

            string result = output.str();

            assert(result.find("Invalid choice!") != string::npos);
        }

        //add quantity exceeding stock
        {
            stringstream input(
                "1\n"       // search by name
                "Laptop\n"  // product name (stock = 5)
                "1A\n"      // add index 1
                "99\n"      // quantity > stock
                "0\n"       // exit
            );

            streambuf* oldCin = cin.rdbuf(input.rdbuf());
            stringstream output;
            streambuf* oldCout = cout.rdbuf(output.rdbuf());

            Buyer.searchProduct("");

            cin.rdbuf(oldCin);
            cout.rdbuf(oldCout);

            string result = output.str();

            assert(result.find("Only") != string::npos);
            assert(result.find("available in stock") != string::npos);
        }

        //invalid index when adding to cart
        {
            stringstream input(
                "1\n"       // search by name
                "Laptop\n"  // product name
                "99A\n"     // invalid index
                "0\n"       // exit
            );

            streambuf* oldCin = cin.rdbuf(input.rdbuf());
            stringstream output;
            streambuf* oldCout = cout.rdbuf(output.rdbuf());

            Buyer.searchProduct("");

            cin.rdbuf(oldCin);
            cout.rdbuf(oldCout);

            string result = output.str();

            assert(result.find("Invalid index") != string::npos);
        }

        //invalid quantity (zero or negative)
        {
            stringstream input(
                "1\n"       // search by name
                "Laptop\n"  // product name
                "1A\n"      // valid index
                "0\n"       // invalid quantity
                "0\n"       // exit
            );

            streambuf* oldCin = cin.rdbuf(input.rdbuf());
            stringstream output;
            streambuf* oldCout = cout.rdbuf(output.rdbuf());

            Buyer.searchProduct("");

            cin.rdbuf(oldCin);
            cout.rdbuf(oldCout);

            string result = output.str();

            assert(result.find("Invalid quantity!") != string::npos);
        }

        //invalid inner loop input
        {
            stringstream input(
                "1\n"       // search by name
                "Laptop\n"  // product name
                "XYZ\n"     // invalid inner choice
                "0\n"       // exit
            );

            streambuf* oldCin = cin.rdbuf(input.rdbuf());
            stringstream output;
            streambuf* oldCout = cout.rdbuf(output.rdbuf());

            Buyer.searchProduct("");

            cin.rdbuf(oldCin);
            cout.rdbuf(oldCout);

            string result = output.str();

            assert(result.find("Invalid input") != string::npos);
        }
            
    }

    std::cout << "\nAll BUYER tests passed!" << endl;
    return 0;
}
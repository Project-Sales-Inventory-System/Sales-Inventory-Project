#include<cassert>
#include<iostream>
#include<sstream>
#include"../include/SELLER.h"
#include"../include/USER.h"
#include"../include/PRODUCT.h"
#include"../include/AUTHORITY_SERVICE.h"
#include"../include/USER_ACCOUNT.h"
#include"../include/PRODUCT_REPO.h"
using namespace std;

int main(){

    PRODUCT_REPO repo;
    USER_ACCOUNT account("Rakhi Sah", "rakhi123", "abc123", "9812345670", 30, "ktm", "abc@email.com", ClientSELLER);
    SELLER seller(account, repo);

    // getUsername test
    {
        assert(seller.getUsername() == "rakhi123");
    }

    //test perform Action
    {
        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

        seller.performAction();  

        std::cout.rdbuf(oldCout);

        assert(output.str().find("Seller interacting") != string::npos);
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
        SELLER Seller(account, freshRepo);

        //search by name, found result
        {
            stringstream input(
                "1\n"       // search by name
                "Laptop\n"  // product name → found
                "0\n"       // back to menu (consumed by getline)
                "3\n"       // exit
            );

            streambuf* oldCin = std::cin.rdbuf(input.rdbuf());
            stringstream output;
            streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
            Seller.searchProduct("");
            std::cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            string result = output.str();
            assert(result.find("SEARCH PRODUCTS") != string::npos);
            assert(result.find("Enter product name to search:") != string::npos);
            assert(result.find("Laptop") != string::npos);
        }

        //search by category, found result
        {
            stringstream input(
                "2\n"           // search by category
                "Electronics\n" // category → found
                "0\n"           // back to menu (consumed by getline)
                "3\n"           // exit
            );

            streambuf* oldCin = std::cin.rdbuf(input.rdbuf());
            stringstream output;
            streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
            Seller.searchProduct("");
            std::cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            string result = output.str();
            assert(result.find("SEARCH PRODUCTS") != string::npos);
            assert(result.find("Enter product category to search:") != string::npos);
            assert(result.find("Laptop") != string::npos);
        }

        //empty product name error
        {
            stringstream input(
                "1\n"   // search by name
                "\n"    // empty name → error
                "0\n"   // back to menu (consumed by getline)
                "3\n"   // exit
            );

            streambuf* oldCin = std::cin.rdbuf(input.rdbuf());
            stringstream output;
            streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
            Seller.searchProduct("");
            std::cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            string result = output.str();
            assert(result.find("SEARCH PRODUCTS") != string::npos);
            assert(result.find("Product name cannot be empty") != string::npos);
        }

        //empty category error
        {
            stringstream input(
                "2\n"   // search by category
                "\n"    // empty category → error
                "0\n"   // back to menu (consumed by getline)
                "3\n"   // exit
            );

            streambuf* oldCin = std::cin.rdbuf(input.rdbuf());
            stringstream output;
            streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
            Seller.searchProduct("");
            std::cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            string result = output.str();
            assert(result.find("SEARCH PRODUCTS") != string::npos);
            assert(result.find("Category cannot be empty") != string::npos);
        }

        //non-existing product name
        {
            stringstream input(
                "1\n"    // search by name
                "abc\n"  // non-existing
                "0\n"    // back to menu (consumed by getline)
                "3\n"    // exit
            );

            streambuf* oldCin = std::cin.rdbuf(input.rdbuf());
            stringstream output;
            streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
            Seller.searchProduct("");
            std::cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            string result = output.str();
            assert(result.find("SEARCH PRODUCTS") != string::npos);
            assert(result.find("No products found") != string::npos);
        }

        //non-existing category
        {
            stringstream input(
                "2\n"    // search by category
                "abc\n"  // non-existing
                "0\n"    // back to menu (consumed by getline)
                "3\n"    // exit
            );

            streambuf* oldCin = std::cin.rdbuf(input.rdbuf());
            stringstream output;
            streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
            Seller.searchProduct("");
            std::cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            string result = output.str();
            assert(result.find("SEARCH PRODUCTS") != string::npos);
            assert(result.find("No products found") != string::npos);
        }

        //invalid menu choice
        {
            stringstream input(
                "5\n"   // invalid choice
                "3\n"   // exit
            );

            streambuf* oldCin = std::cin.rdbuf(input.rdbuf());
            stringstream output;
            streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
            Seller.searchProduct("");
            std::cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            string result = output.str();
            assert(result.find("Invalid choice") != string::npos);
        }
    }


    //addProduct test
    {
        PRODUCT p("Stationary", "pen", 50.0, 5);
        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

        seller.addProduct(p);

        std::cout.rdbuf(oldCout);

        assert(output.str().find("--------PRODUCT ADDED SUCCESSFULLY-------") != string::npos);
        
    }

    std::cout <<"All SELLER Tests Passed!" << std::endl;
    return 0;
}
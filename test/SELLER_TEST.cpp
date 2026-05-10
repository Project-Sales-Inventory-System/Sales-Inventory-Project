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

    //Authentication test
    {
       // AUTHORITY_SERVICE auth;
        //auth.registerUser(account) ;
       // assert (seller.authenticate(auth) == true);

    }
    
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

    //startSession test
        {
        PRODUCT_REPO repo2;
        PRODUCT p1("Electronics", "Laptop", 50000.0, 5);
        repo2.addProduct(p1);

        stringstream input(
        "abc\n"     // invalid input
        "99\n"      // invalid menu choice
        "4\n"       // logout
    );

        streambuf* oldCin  = std::cin.rdbuf(input.rdbuf());
        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

        seller.startSession();

        std::cin.rdbuf(oldCin);   
        std::cout.rdbuf(oldCout); 

        assert(output.str().find("Invalid input. Try again.") != string::npos);
        assert(output.str().find("Invalid choice") != string::npos);
        assert(output.str().find("Logging out...") != string::npos);
        std::cout<<"test7 passed"<<std::endl;
    }
    
    //searchProduct test
    {
        PRODUCT p1("Electronics", "Laptop", 50000.0, 5);
        PRODUCT p2("Clothes", "Shirt", 500.0, 20);
        PRODUCT p3("Books", "C++ Programming", 1500.0, 10);

        repo.addProduct(p1);
        repo.addProduct(p2);
        repo.addProduct(p3);

        {
            stringstream input(
            "1\n"           //search by name
            "Laptop\n"      //product name
            "3\n"           //Exit
            );

            streambuf* oldCin = std::cin.rdbuf(input.rdbuf());

            stringstream output;
            streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

            seller.searchProduct("");

            std::cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            string result = output.str();

            assert(result.find("SEARCH PRODUCTS") != string::npos);
            assert(result.find("Enter product name to search: ") != string::npos);
        } 
        
        {
            stringstream input(
            "2\n"               //search by category
            "Electronics\n"     //product category
            "3\n"               //Exit
            );

            streambuf* oldCin = std::cin.rdbuf(input.rdbuf());

            stringstream output;
            streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

            seller.searchProduct("");

            std::cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            string result = output.str();

            assert(result.find("SEARCH PRODUCTS") != string::npos);
            assert(result.find("Enter product category to search: ") != string::npos);
        } 

        {
            stringstream input(
            "1\n"   // search by name
            "\n"    // empty product name 
            "\n"    // "No result found. Press Enter..." 
        );

            streambuf* oldCin = std::cin.rdbuf(input.rdbuf());

            stringstream output;
            streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

            seller.searchProduct("");

            std::cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            string result = output.str();

            assert(result.find("SEARCH PRODUCTS") != string::npos);
            assert(result.find("Enter product name to search: ") != string::npos);
            assert(result.find("⚠️ Product name cannot be empty!") != string::npos);
        }  
        
        {
            stringstream input(
            "2\n"   // search by category
            "\n"    // empty product category
            "\n"    // "No result found. Press Enter..." 
        );

            streambuf* oldCin = std::cin.rdbuf(input.rdbuf());

            stringstream output;
            streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

            seller.searchProduct("");

            std::cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            string result = output.str();

            assert(result.find("SEARCH PRODUCTS") != string::npos);
            assert(result.find("Enter product category to search: ") != string::npos);
            assert(result.find("⚠️ Category cannot be empty!") != string::npos);
           
        }  

        {
            stringstream input(
            "1\n"        // search by name
            "abc\n"    // non existing product name 
            "\n"         // "No result found. Press Enter..." 
        );

            streambuf* oldCin = std::cin.rdbuf(input.rdbuf());

            stringstream output;
            streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

            seller.searchProduct("");

            std::cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            string result = output.str();

            assert(result.find("SEARCH PRODUCTS") != string::npos);
            assert(result.find("Enter product name to search: ") != string::npos);
            assert(result.find("⚠️ No products found.") != string::npos);
        }    

        {
            stringstream input(
            "2\n"        // search by category
            "abc\n"    // non existing product category 
            "\n"         // "No result found. Press Enter..." 
        );

            streambuf* oldCin = std::cin.rdbuf(input.rdbuf());

            stringstream output;
            streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

            seller.searchProduct("");

            std::cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            string result = output.str();

            assert(result.find("SEARCH PRODUCTS") != string::npos);
            assert(result.find("Enter product category to search: ") != string::npos);
            assert(result.find("⚠️ No products found.") != string::npos);
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

    std::cout <<"All Tests Passed!" << std::endl;
    return 0;
}
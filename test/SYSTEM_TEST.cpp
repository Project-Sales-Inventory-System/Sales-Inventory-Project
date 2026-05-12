#include<cassert>
#include<iostream>
#include<sstream>
#include<cstdio>
#include"../include/USER.h"
#include"../include/PRODUCT.h"
#include"../include/AUTHORITY_SERVICE.h"
#include"../include/USER_ACCOUNT.h"
#include"../include/PRODUCT_REPO.h"
#include"../include/BILL_SERVICE.h"
#include"../include/SYSTEM.h"

using namespace std;

int main()
{
    //registerAccount
    {
        remove("users.csv");
        SYSTEM sys;

        USER_ACCOUNT account("Pranali Rathod", "pranali123", "efg123", "9812983450", 40, "delhi", "efg@gmail.com", ClientBUYER);
        assert(sys.registerAccount(account) == true);
        assert(sys.registerAccount(account) == false);
        
    }

    //loginAccount - valid credentials
    {
        
        SYSTEM sys;

        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

        USER* user = sys.loginAccount("pranali123", "efg123");

        std::cout.rdbuf(oldCout);

        assert(output.str().find("Login Successful") != string::npos);
        
    }

    //loginAccount - invalid credentials
    {
        
        SYSTEM sys;

        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

        USER* user = sys.loginAccount("pranali123", "wrongpass");

        std::cout.rdbuf(oldCout);

        assert(output.str().find("Password incorrect") != string::npos);
    }

    //adminLogin - wrong passcode
    {
        remove("my_file.csv");
        SYSTEM sys;

        bool result = sys.adminLogin("wrongpass");

        assert(result == false);
    }

    //getAllUsers
    {
        
        SYSTEM sys;

        USER_ACCOUNT account1("Rakhi Sah", "rakhi123", "abc123", "9812345670", 30, "ktm", "abc@gmail.com", ClientBUYER);
        USER_ACCOUNT account2("Shraddha Kapoor", "shraddha123", "efg123", "9856712340", 40, "mumbai", "xyz@gmail.com", ClientSELLER);

        sys.registerAccount(account1);
        sys.registerAccount(account2);

        auto users = sys.getAllUsers();

        assert(users.size() == 3);
        
    }

    //deleteUser - existing user
    {
        
        SYSTEM sys;

        USER_ACCOUNT account("Rakhi Sah", "rakhi123", "abc123", "9812345670", 30, "ktm", "abc@gmail.com", ClientBUYER);
        sys.registerAccount(account);

        bool result = sys.deleteUser("rakhi123");

        assert(result == true);
        assert(sys.getAllUsers().size() == 2);
        
    }
    //deleteUser - non-existing user
    {
        SYSTEM sys;

        bool result = sys.deleteUser("nobody");

        assert(result == false);
        assert(sys.getAllUsers().size() == 2);
    }

    


    //addProduct - no user logged in
    {
        remove("my_file.csv");
        SYSTEM sys;

        PRODUCT p("Electronics", "Laptop", 50000.0, 5);

        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
        sys.addProduct(p);
        std::cout.rdbuf(oldCout);

        assert(output.str().find("No user logged in.") != string::npos);
        std::cout << "test11 passed - addProduct no user" << std::endl;
    }

    //addProduct - admin logged in
    {
        remove("my_file.csv");
        SYSTEM sys;

        sys.adminLogin("admin1234"); 

        PRODUCT p("Electronics", "Laptop", 50000.0, 5);
        sys.addProduct(p);

        auto results = sys.getRepo()->searchByName("Laptop");
        assert(results.size() == 1);
        std::cout << "test12 passed - addProduct admin" << std::endl;
    }

    //searchProduct - by name
    {
        SYSTEM sys;

        PRODUCT p("Electronics", "Laptop", 50000.0, 5);
        sys.getRepo()->addProduct(p);

        stringstream input(
            "1\n"       // search by name
            "Laptop\n"  // search term
            "\n"        // Press Enter
        );
        streambuf* oldCin  = std::cin.rdbuf(input.rdbuf());
        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

        sys.searchProduct();

        std::cin.rdbuf(oldCin);
        std::cout.rdbuf(oldCout);

        assert(output.str().find("Laptop") != string::npos);
        
    }

    //searchProduct - by category
    {
        SYSTEM sys;

        PRODUCT p("Electronics", "Laptop", 50000.0, 5);
        sys.getRepo()->addProduct(p);

        stringstream input(
            "2\n"           // search by category
            "Electronics\n" // search term
            "\n"            // Press Enter
        );
        streambuf* oldCin  = std::cin.rdbuf(input.rdbuf());
        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

        sys.searchProduct();

        std::cin.rdbuf(oldCin);
        std::cout.rdbuf(oldCout);

        assert(output.str().find("Laptop") != string::npos);
        
    }

    //searchProduct - empty query
    {
        SYSTEM sys;

        stringstream input(
            "1\n"   // search by name
            "\n"    // empty search term
        );
        streambuf* oldCin  = std::cin.rdbuf(input.rdbuf());
        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

        sys.searchProduct();

        std::cin.rdbuf(oldCin);
        std::cout.rdbuf(oldCout);

        assert(output.str().find("Error: Search term cannot be empty!") != string::npos);
        
    }

    //searchProduct - no results
    {
        SYSTEM sys;

        stringstream input(
            "1\n"       // search by name
            "Mouse\n"   // non-existing product
            "\n"        // Press Enter
        );
        streambuf* oldCin  = std::cin.rdbuf(input.rdbuf());
        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

        sys.searchProduct();

        std::cin.rdbuf(oldCin);
        std::cout.rdbuf(oldCout);

        assert(output.str().find("No products found matching:") != string::npos);
        
    }

    //removeProduct - not admin
    {
        SYSTEM sys;

        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
        sys.removeProduct();
        std::cout.rdbuf(oldCout);

        assert(output.str().find("Access not granted!") != string::npos);
        
    }

    // updateProduct
    {
        SYSTEM sys;

        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
        sys.updateProduct();
        std::cout.rdbuf(oldCout);

        assert(output.str().find("Access not granted!") != string::npos);
        
    }

    // getAllProducts - no user logged in
    {
        SYSTEM sys;

        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
        sys.getAllProducts();
        std::cout.rdbuf(oldCout);

        assert(output.str().find("Please log in to view the full catalog.") != string::npos);
        
    }

    std::cout << "All SYSTEM Tests Passed!" << std::endl;
    return 0;
}
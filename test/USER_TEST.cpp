#include<cassert>
#include<iostream>
#include<sstream>
#include<cstdio>
#include"../include/USER.h"
#include"../include/PRODUCT.h"
#include"../include/AUTHORITY_SERVICE.h"
#include"../include/USER_ACCOUNT.h"
#include"../include/PRODUCT_REPO.h"
#include"../include/CART.h"
#include"../include/BUYER.h"
#include"../include/SELLER.h"
#include"../include/BILL_SERVICE.h"
#include"../include/ConsoleHelper.h"

using namespace std;

int main()
{
    ConsoleHelper::testMode = true; // enable test mode for getPassword()
    AUTHORITY_SERVICE auth;
        USER* user ;      
      

    // test1: valid registration
    {
        
        ConsoleHelper::testPassword = "pass123";

        stringstream input(
            "\n"                 // cin.ignore at start
            "Rakhi Sah\n"        // full name
            "rakhi@123\n"        // username
            // password comes from ConsoleHelper::testPassword
            "9812345678\n"       // contact
            "25\n"               // age
            "Kathmandu\n"        // location
            "rakhi@gmail.com\n"  // email
            "\n"                 // cin.get()
        );
        streambuf* oldCin  = std::cin.rdbuf(input.rdbuf());
        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

        bool result = user->handleUserRegistrationUI(auth); // instance call

        std::cin.rdbuf(oldCin);
        std::cout.rdbuf(oldCout);

        assert(result == true);
        assert(output.str().find("Registration successful!") != string::npos);
            }

    // test2: invalid full name (single word), then valid
    {
        
        ConsoleHelper::testPassword = "pass123";

        stringstream input(
            "\n"
            "Rakhi\n"            // invalid - single word
            "Rakhi Sah\n"        // valid
            "rakhi@456\n"        // different username from test1
            // password from testPassword
            "9812345678\n"
            "25\n"
            "Kathmandu\n"
            "rakhi@gmail.com\n"
            "\n"
        );
        streambuf* oldCin  = std::cin.rdbuf(input.rdbuf());
        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

        bool result = user->handleUserRegistrationUI(auth);

        std::cin.rdbuf(oldCin);
        std::cout.rdbuf(oldCout);

        assert(output.str().find("Error: Please enter at least first and last name!") != string::npos);
        assert(result == true);
        std::cout << "test2 passed - invalid name retry" << std::endl;
    }

    // test3: username too short, then no special char, then valid
    {
        ConsoleHelper::testPassword = "pass123";

        stringstream input(
            "\n"
            "Rakhi Sah\n"
            "ra@1\n"             // too short
            "rakhi123\n"         // no special char
            "rakhi@789\n"        // valid, unique username
            // password from testPassword
            "9812345678\n"
            "25\n"
            "Kathmandu\n"
            "rakhi@gmail.com\n"
            "\n"
        );
        streambuf* oldCin  = std::cin.rdbuf(input.rdbuf());
        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

        bool result = user->handleUserRegistrationUI(auth);

        std::cin.rdbuf(oldCin);
        std::cout.rdbuf(oldCout);

        assert(output.str().find("Error: Username must be at least 5 characters long!") != string::npos);
        assert(output.str().find("Error: Username must contain at least one special character") != string::npos);
        assert(result == true);

    }

    // invalid contact, then valid
    {
        

        ConsoleHelper::testPassword = "pass123";

        stringstream input(
            "\n"
            "Rakhi Sah\n"
            "contact@1\n"        // unique username
            // password from testPassword
            "12345\n"            // too short
            "1234567890\n"       // wrong prefix
            "9812345678\n"       // valid
            "25\n"
            "Kathmandu\n"
            "rakhi@gmail.com\n"
            "\n"
        );
        streambuf* oldCin  = std::cin.rdbuf(input.rdbuf());
        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

        bool result = user->handleUserRegistrationUI(auth);

        std::cin.rdbuf(oldCin);
        std::cout.rdbuf(oldCout);

        assert(output.str().find("Enter the correct contact number!") != string::npos);
        assert(result == true);
        std::cout << "test4 passed - invalid contact retry" << std::endl;
    }

    // test5: invalid email, then valid
    {
        ConsoleHelper::testPassword = "pass123";

        stringstream input(
            "\n"
            "Rakhi Sah\n"
            "email@user1\n"       // unique username
            // password from testPassword
            "9812345678\n"
            "25\n"
            "Kathmandu\n"
            "rakhi@hotmail.com\n" // invalid
            "rakhi@gmail.com\n"   // valid
            "\n"
        );
        streambuf* oldCin  = std::cin.rdbuf(input.rdbuf());
        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

        bool result = user->handleUserRegistrationUI(auth);

        std::cin.rdbuf(oldCin);
        std::cout.rdbuf(oldCout);

        assert(output.str().find("Incorrect email format") != string::npos);
        assert(result == true);
        std::cout << "test5 passed - invalid email retry" << std::endl;
    }

    // test6: duplicate username
    {
        ConsoleHelper::testPassword = "pass123";

        USER_ACCOUNT existing("Rakhi Sah", "rakhi@123", "pass123",
                              "9812345678", 25, "ktm",
                              "rakhi@gmail.com", ClientBUYER);
        auth.registerUser(existing);

        stringstream input(
            "\n"
            "Rakhi Sah\n"
            "rakhi@123\n"        // duplicate
            "newrakhi@1\n"       // unique, valid
            // password from testPassword
            "9812345678\n"
            "25\n"
            "Kathmandu\n"
            "rakhi@gmail.com\n"
            "\n"
        );
        streambuf* oldCin  = std::cin.rdbuf(input.rdbuf());
        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

        bool result = user->handleUserRegistrationUI(auth);

        std::cin.rdbuf(oldCin);
        std::cout.rdbuf(oldCout);

        assert(output.str().find("Username already exists!") != string::npos);
        assert(result == true);
        std::cout << "test6 passed - duplicate username" << std::endl;
    }

    // test7: handleUserLoginUI - invalid mode choice
    {
        remove("my_file.csv");
        AUTHORITY_SERVICE auth;
        PRODUCT_REPO repo;
        BILL_SERVICE bs;
        USER* user;

        ConsoleHelper::testPassword = "pass123";

        USER_ACCOUNT account("Rakhi Sah", "rakhi@123", "pass123",
                            "9812345678", 25, "ktm",
                            "rakhi@gmail.com", ClientBUYER);
        auth.registerUser(account);

        stringstream input(
            "99\n"        // invalid mode
            "rakhi@123\n" // username
            // password from testPassword
            "\n"          // press enter
        );
        streambuf* oldCin  = std::cin.rdbuf(input.rdbuf());
        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

        user->handleUserLoginUI(auth, repo, bs);

        std::cin.rdbuf(oldCin);
        std::cout.rdbuf(oldCout);

        assert(output.str().find("Invalid Choice") != string::npos);
        std::cout << "test7 passed - invalid mode choice" << std::endl;
    }

    // test8: handleUserLoginUI - empty username
    {
        remove("my_file.csv");
        AUTHORITY_SERVICE auth;
        PRODUCT_REPO repo;
        BILL_SERVICE bs;
        USER* user;

        ConsoleHelper::testPassword = "pass123";

        stringstream input(
            "1\n"  // buyer
            "\n"   // empty username
        );
        streambuf* oldCin  = std::cin.rdbuf(input.rdbuf());
        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

        user->handleUserLoginUI(auth, repo, bs);

        std::cin.rdbuf(oldCin);
        std::cout.rdbuf(oldCout);

        assert(output.str().find("Username and password cann't be empty") != string::npos);
        std::cout << "test8 passed - empty username" << std::endl;
    }

    // test9: handleUserLoginUI - wrong credentials
    {
        remove("my_file.csv");
        AUTHORITY_SERVICE auth;
        PRODUCT_REPO repo;
        BILL_SERVICE bs;
        USER* user;

        ConsoleHelper::testPassword = "wrongpass"; // wrong password

        USER_ACCOUNT account("Rakhi Sah", "rakhi@123", "pass123",
                            "9812345678", 25, "ktm",
                            "rakhi@gmail.com", ClientBUYER);
        auth.registerUser(account);

        stringstream input(
            "1\n"         // buyer
            "rakhi@123\n" // username
            // wrong password from testPassword
        );
        streambuf* oldCin  = std::cin.rdbuf(input.rdbuf());
        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

        user->handleUserLoginUI(auth, repo, bs);

        std::cin.rdbuf(oldCin);
        std::cout.rdbuf(oldCout);

        assert(output.str().find("Login failed. Invalid credentials.") != string::npos);
        std::cout << "test9 passed - wrong credentials" << std::endl;
    }

    // test10: handleUserLoginUI - successful buyer login
    {
        remove("my_file.csv");
        AUTHORITY_SERVICE auth;
        PRODUCT_REPO repo;
        BILL_SERVICE bs;
        USER* user;

        ConsoleHelper::testPassword = "pass123";

        USER_ACCOUNT account("Rakhi Sah", "rakhi@123", "pass123",
                            "9812345678", 25, "ktm",
                            "rakhi@gmail.com", ClientBUYER);
        auth.registerUser(account);

        stringstream input(
            "1\n"         // buyer
            "rakhi@123\n" // username
            // password from testPassword
            "5\n"         // logout from buyer menu
            "\n"          // press enter
        );
        streambuf* oldCin  = std::cin.rdbuf(input.rdbuf());
        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

        user->handleUserLoginUI(auth, repo, bs);

        std::cin.rdbuf(oldCin);
        std::cout.rdbuf(oldCout);

        assert(output.str().find("Welcome") != string::npos);
        assert(output.str().find("rakhi@123") != string::npos);
        std::cout << "test10 passed - successful buyer login" << std::endl;
    }

    // test11: handleUserLoginUI - successful seller login
    {
        remove("my_file.csv");
        AUTHORITY_SERVICE auth;
        PRODUCT_REPO repo;
        BILL_SERVICE bs;
        USER* user;

        ConsoleHelper::testPassword = "pass123";

        USER_ACCOUNT account("Rakhi Sah", "seller@123", "pass123",
                            "9812345678", 25, "ktm",
                            "seller@gmail.com", ClientSELLER);
        auth.registerUser(account);

        stringstream input(
            "2\n"          // seller
            "seller@123\n" // username
            // password from testPassword
            "4\n"          // logout from seller menu
            "\n"           // press enter
        );
        streambuf* oldCin  = std::cin.rdbuf(input.rdbuf());
        stringstream output;
        streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

        user->handleUserLoginUI(auth, repo, bs);

        std::cin.rdbuf(oldCin);
        std::cout.rdbuf(oldCout);

        assert(output.str().find("Welcome") != string::npos);
        assert(output.str().find("seller@123") != string::npos);
        std::cout << "test11 passed - successful seller login" << std::endl;
    }

    ConsoleHelper::testMode = false;
    std::cout << "\nAll USER tests passed!" << std::endl;
    return 0;
}
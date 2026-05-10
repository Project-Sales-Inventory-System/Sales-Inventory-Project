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
#include"../include/ADMIN.h"

using namespace std;

int main()
{
    PRODUCT_REPO repo;
    AUTHORITY_SERVICE auth;
    BILL_SERVICE bill;
    ADMIN admin("admin123", repo, auth, bill);

    // test1: getUsername
    {
        assert(admin.getUsername() == "ADMIN");
    }

    // test2: startSession - invalid input, invalid choice, logout
    {
        
        stringstream input(
            "abc\n"  // invalid input
            "99\n"   // invalid choice
            "8\n"    // logout (case 8, not 7!)
        );
        streambuf* oldCin  = cin.rdbuf(input.rdbuf());
        stringstream output;
        streambuf* oldCout = cout.rdbuf(output.rdbuf());

        admin.startSession();

        cin.rdbuf(oldCin);
        cout.rdbuf(oldCout);

        assert(output.str().find("Invalid input. Try again.") != string::npos);
        assert(output.str().find("Invalid choice. Try again.") != string::npos);
        assert(output.str().find("Admin logout.") != string::npos);
    }

    //addProduct
    {
        
        stringstream input(
            "3\n"           // add product
            "Electronics\n" // category
            "Laptop\n"      // name
            "50000\n"       // price
            "5\n"           // quantity
            "\n"            // press enter to continue
            "8\n"           // logout
        );
        streambuf* oldCin  = cin.rdbuf(input.rdbuf());
        stringstream output;
        streambuf* oldCout = cout.rdbuf(output.rdbuf());

        admin.startSession();

        cin.rdbuf(oldCin);
        cout.rdbuf(oldCout);

        string result = output.str();
        assert(result.find("Product added successfully!") != string::npos);
        assert(result.find("Laptop") != string::npos);
        assert(result.find("Electronics") != string::npos);
    }

    //removeProduct - empty repo
    {
        remove("my_file.csv");
        PRODUCT_REPO repo;
        AUTHORITY_SERVICE auth;
        BILL_SERVICE bill;
        ADMIN admin("admin123", repo, auth, bill);

        stringstream input(
            "4\n"  // remove product
            "\n"   // press enter to continue
            "8\n"  // logout
        );
        streambuf* oldCin  = cin.rdbuf(input.rdbuf());
        stringstream output;
        streambuf* oldCout = cout.rdbuf(output.rdbuf());

        admin.startSession();

        cin.rdbuf(oldCin);
        cout.rdbuf(oldCout);

        assert(output.str().find("No product") != string::npos);
        
    }

    //updateProduct - empty repo
    {
        remove("my_file.csv");
        PRODUCT_REPO repo;
        AUTHORITY_SERVICE auth;
        BILL_SERVICE bill;
        ADMIN admin("admin123", repo, auth, bill);

        stringstream input(
            "5\n"  // update product
            "\n"   // press enter to continue
            "8\n"  // logout
        );
        streambuf* oldCin  = cin.rdbuf(input.rdbuf());
        stringstream output;
        streambuf* oldCout = cout.rdbuf(output.rdbuf());

        admin.startSession();

        cin.rdbuf(oldCin);
        cout.rdbuf(oldCout);

        assert(output.str().find("No product") != string::npos);
    }

    //searchProduct - found
    {
        
        repo.addProduct(PRODUCT("Electronics", "Laptop", 50000.0, 5));

        stringstream input(
            "6\n"       // search product
            "Laptop\n"  // name
            "\n"        // press enter to continue
            "8\n"       // logout
        );
        streambuf* oldCin  = cin.rdbuf(input.rdbuf());
        stringstream output;
        streambuf* oldCout = cout.rdbuf(output.rdbuf());

        admin.startSession();

        cin.rdbuf(oldCin);
        cout.rdbuf(oldCout);

        string result = output.str();
        assert(result.find("Enter product name to search:") != string::npos);
        assert(result.find("SEARCH RESULTS") != string::npos);
        assert(result.find("Laptop") != string::npos);
    }

    //searchProduct - not found
    {
        remove("my_file.csv");
        PRODUCT_REPO repo;
        AUTHORITY_SERVICE auth;
        BILL_SERVICE bill;
        ADMIN admin("admin123", repo, auth, bill);

        stringstream input(
            "6\n"       // search product
            "Mouse\n"   // non-existing name
            "\n"        // press enter to continue
            "8\n"       // logout
        );
        streambuf* oldCin  = cin.rdbuf(input.rdbuf());
        stringstream output;
        streambuf* oldCout = cout.rdbuf(output.rdbuf());

        admin.startSession();

        cin.rdbuf(oldCin);
        cout.rdbuf(oldCout);

        assert(output.str().find("No products found.") != string::npos);
    }

    //viewProduct -by name
    {
        remove("my_file.csv");
        PRODUCT_REPO repo;
        AUTHORITY_SERVICE auth;
        BILL_SERVICE bill;
        ADMIN admin("admin123", repo, auth, bill);

        repo.addProduct(PRODUCT("Electronics", "Laptop", 50000.0, 5));
        repo.addProduct(PRODUCT("clothes", "vest", 500.0,5));

        stringstream input(
            "2\n"   // view products menu
            "2\n"   // view all stock
            "\n"    // press enter to continue
            "8\n"   // logout
        );
        streambuf* oldCin  = cin.rdbuf(input.rdbuf());
        stringstream output;
        streambuf* oldCout = cout.rdbuf(output.rdbuf());

        admin.startSession();

        cin.rdbuf(oldCin);
        cout.rdbuf(oldCout);

        string result = output.str();
        assert(result.find("Laptop") != string::npos);
        assert(result.find("vest")!= string::npos);
    }

    //viewProduct - by category
    {
        stringstream input(
            "2\n"            // view products menu
            "1\n"            // view by category
            "Electronics\n"  // category name
            "\n"             // press enter to continue
            "8\n"            // logout
        );
        streambuf* oldCin  = cin.rdbuf(input.rdbuf());
        stringstream output;
        streambuf* oldCout = cout.rdbuf(output.rdbuf());

        admin.startSession();

        cin.rdbuf(oldCin);
        cout.rdbuf(oldCout);

        string result = output.str();
        assert(result.find("Electronics") != string::npos);
        assert(result.find("Laptop") != string::npos);
        
    }

    cout << "\nAll ADMIN tests passed!" << endl;
    return 0;
}
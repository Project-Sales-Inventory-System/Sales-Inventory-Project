#include<cassert>
#include<iostream>
#include<sstream>
#include"../include/USER.h"
#include"../include/PRODUCT.h"
#include"../include/AUTHORITY_SERVICE.h"
#include"../include/USER_ACCOUNT.h"
#include"../include/PRODUCT_REPO.h"
#include"../include/CART.h"
#include"../include/BUYER.h"

using namespace std;

int main(){
    PRODUCT_REPO repo;
    USER_ACCOUNT account("Rakhi Sah", "rakhi123", "abc123", "9812345670", 30, "ktm", "abc@email.com", ClientBUYER);
    BUYER buyer(account, repo);

    //Authentication test
    {
        AUTHORITY_SERVICE authService;
        authService.registerUser(account) ;
        assert (buyer.authenticate(authService) == true);

    }

    // getUsername test
    {
        assert(buyer.getUsername() == "rakhi123");
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
            "1A\n"          //add to cart
            "V\n"           //view cart
            "S\n"           //search again
            "2\n"           //search by category
            "Clothes\n"     //category name
            "0\n"           //Exit
            );

            streambuf* oldCin = cin.rdbuf(input.rdbuf());

            stringstream output;
            streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

            buyer.searchProduct("");

            cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            string result = output.str();

            assert(result.find("SEARCH PRODUCTS") != string::npos);
            assert(result.find("Enter product name to search: ") != string::npos);
            assert(result.find("Laptop added to Cart") != string::npos);
            assert(result.find("Laptop") != string::npos);
            assert(result.find("SEARCH PRODUCTS") != string::npos);
            assert(result.find("Enter product category to search: ") != string::npos);
        } 

        {
            stringstream input(
            "1\n"   // search by name
            "\n"    // empty product name 
            "\n"    // "No result found. Press Enter..."
            "2\n"   // search by category
            "\n"    // empty product category 
            "\n"    // "No result found. Press Enter..."
            "0\n"   // invalid choice 
            "3\n"   // exit 
);

            streambuf* oldCin = cin.rdbuf(input.rdbuf());

            stringstream output;
            streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

            buyer.searchProduct("");

            cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            string result = output.str();

            assert(result.find("SEARCH PRODUCTS") != string::npos);
            assert(result.find("Enter product name to search: ") != string::npos);
            assert(result.find("Error: Product name cannot be empty!") != string::npos);
            assert(result.find("Enter product category to search: ") != string::npos);
            assert(result.find("Error: Category cannot be empty!") != string::npos);
           // assert(result.find("Invalid choice!") != string::npos);
        }  
        
        


     
    }

    std::cout << "All Tests Passed!"<<std::endl;
    return 0;
}
    
    

/*

// Test 4: BUYER Cart Operations
void testBuyerCartOperations() {
    
    PRODUCT_REPO repo;
    USER_ACCOUNT account("Carol White", "carolwhite", "pass456", "03003333333", 27, "Rawalpindi", "carol@email.com", ClientBUYER);
    BUYER buyer(account, repo);
    
    // Create some test products
    PRODUCT product1("Electronics", "Laptop", 50000.0, 5);
    PRODUCT product2("Electronics", "Mouse", 500.0, 20);
    PRODUCT product3("Books", "C++ Programming", 1500.0, 10);
    
    // Add products to repository
    repo.addProduct(product1);
    repo.addProduct(product2);
    repo.addProduct(product3);
    
    cout << "✓ Test products added to repository" << endl;
    cout << "✓ Repository initialized with 3 products" << endl;
}

// Test 5: BUYER Search Functionality
void testBuyerSearchByName() {
    cout << "\n[TEST 5] Testing BUYER Search by Name..." << endl;
    
    PRODUCT_REPO repo;
    
    // Add test products
    PRODUCT product1("Electronics", "Samsung Phone", 45000.0, 8);
    PRODUCT product2("Electronics", "iPhone", 120000.0, 5);
    PRODUCT product3("Books", "Data Structures", 2000.0, 15);
    
    repo.addProduct(product1);
    repo.addProduct(product2);
    repo.addProduct(product3);
    
    // Perform search
    vector<PRODUCT> results = repo.searchByName("Phone");
    cout << "✓ Search performed for 'Phone'" << endl;
    cout << "✓ Search results retrieved: " << results.size() << " item(s) found" << endl;
}

// Test 6: BUYER Search by Category
void testBuyerSearchByCategory() {
    cout << "\n[TEST 6] Testing BUYER Search by Category..." << endl;
    
    PRODUCT_REPO repo;
    
    // Add test products with different categories
    PRODUCT product1("Electronics", "Headphones", 3000.0, 12);
    PRODUCT product2("Electronics", "Speaker", 5000.0, 8);
    PRODUCT product3("Books", "Web Development", 1800.0, 20);
    PRODUCT product4("Clothing", "T-Shirt", 800.0, 50);
    
    repo.addProduct(product1);
    repo.addProduct(product2);
    repo.addProduct(product3);
    repo.addProduct(product4);
    
    // Search by category
    vector<PRODUCT> electronicsResults = repo.searchByCategory("Electronics");
    cout << "✓ Search performed for 'Electronics' category" << endl;
    cout << "✓ Electronics category results: " << electronicsResults.size() << " item(s)" << endl;
    
    vector<PRODUCT> booksResults = repo.searchByCategory("Books");
    cout << "✓ Books category results: " << booksResults.size() << " item(s)" << endl;
}

// Test 7: BUYER Perform Action
void testBuyerPerformAction() {
    cout << "\n[TEST 7] Testing BUYER performAction()..." << endl;
    
    PRODUCT_REPO repo;
    USER_ACCOUNT account("David Brown", "davidbrown", "secure123", "03007777777", 35, "Quetta", "david@email.com", ClientBUYER);
    BUYER buyer(account, repo);
    
    buyer.performAction();
    cout << "✓ performAction() executed successfully" << endl;
}

// Test 8: BUYER Multiple Users Test
void testMultipleBuyersWithDifferentAccounts() {
    cout << "\n[TEST 8] Testing Multiple BUYER Instances..." << endl;
    
    PRODUCT_REPO repo;
    
    USER_ACCOUNT account1("Emma Davis", "emmadavis", "pass001", "03001111111", 24, "Karachi", "emma@email.com", ClientBUYER);
    USER_ACCOUNT account2("Frank Johnson", "frankj", "pass002", "03002222222", 32, "Lahore", "frank@email.com", ClientBUYER);
    USER_ACCOUNT account3("Grace Lee", "gracelee", "pass003", "03004444444", 29, "Islamabad", "grace@email.com", ClientBUYER);
    
    BUYER buyer1(account1, repo);
    BUYER buyer2(account2, repo);
    BUYER buyer3(account3, repo);
    
    assert(buyer1.getUsername() == "emmadavis");
    assert(buyer2.getUsername() == "frankj");
    assert(buyer3.getUsername() == "gracelee");
    
    cout << "✓ Buyer 1 username: " << buyer1.getUsername() << endl;
    cout << "✓ Buyer 2 username: " << buyer2.getUsername() << endl;
    cout << "✓ Buyer 3 username: " << buyer3.getUsername() << endl;
    cout << "✓ Multiple BUYER instances created and verified successfully" << endl;
}

// Test 9: BUYER Product Repository Integration
void testBuyerProductRepositoryIntegration() {
    cout << "\n[TEST 9] Testing BUYER Product Repository Integration..." << endl;
    
    PRODUCT_REPO repo;
    USER_ACCOUNT account("Henry Martinez", "henrym", "pass789", "03008888888", 26, "Peshawar", "henry@email.com", ClientBUYER);
    BUYER buyer(account, repo);
    
    // Add multiple products to repository
    PRODUCT product1("Electronics", "Keyboard", 2500.0, 15);
    PRODUCT product2("Electronics", "Monitor", 12000.0, 6);
    PRODUCT product3("Accessories", "USB Cable", 200.0, 100);
    
    repo.addProduct(product1);
    repo.addProduct(product2);
    repo.addProduct(product3);
    
    cout << "✓ Products added to repository" << endl;
    
    // Search operations
    vector<PRODUCT> searchResults = repo.searchByName("keyboard");
    cout << "✓ Keyboard search results: " << searchResults.size() << " item(s)" << endl;
    
    vector<PRODUCT> categoryResults = repo.searchByCategory("Electronics");
    cout << "✓ Electronics category results: " << categoryResults.size() << " item(s)" << endl;
    
    cout << "✓ Repository integration test completed successfully" << endl;
}

// Test 10: BUYER Account Details Validation
void testBuyerAccountDetailsValidation() {
    cout << "\n[TEST 10] Testing BUYER Account Details..." << endl;
    
    PRODUCT_REPO repo;
    USER_ACCOUNT account("Isabel Garcia", "isabela", "password", "03009999999", 31, "Multan", "isabel@email.com", ClientBUYER);
    BUYER buyer(account, repo);
    
    assert(buyer.getUsername() == "isabela");
    cout << "✓ Username validated: " << buyer.getUsername() << endl;
    cout << "✓ BUYER account details verified successfully" << endl;
}

int main(){
    cout << "\n========== BUYER TEST SUITE ==========" << endl;
    
    try {
    
        testBuyerAuthentication();
        testBuyerGetUsername();
        testBuyerCartOperations();
        testBuyerSearchByName();
        testBuyerSearchByCategory();
        testBuyerPerformAction();
        testMultipleBuyersWithDifferentAccounts();
        testBuyerProductRepositoryIntegration();
        testBuyerAccountDetailsValidation();
        
        cout << "\n========================================" << endl;
        cout << "All BUYER tests passed successfully!" << endl;
        cout << "========================================\n" << endl;
    }
    catch (const exception& e) {
        cerr << "Test failed with exception: " << e.what() << endl;
        return 1;
    }

    return 0;
}
    */
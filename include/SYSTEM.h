/*
SYSTEM class acts as the main controller of the application.

STANDARD LIBRARIES USED:
-vector:Used for storing collections of data.
-string:Used for text handling.
-iostream:Used for console input/output.
-limits:Used for input validation and stream handling.

PRIVATE DATA MEMBERS:
-current_user:Pointer to currently logged-in user.
-auth:Pointer to AUTHORITY_SERVICE object.
-repo:Pointer to PRODUCT_REPO object.
-isAdminLoggedin:Tracks administrator login status.
-bill_service:Pointer to BILL_SERVICE object.
-isRegistered:Tracks user registration status.

PUBLIC FUNCTIONS:
-SYSTEM():Constructor that initializes the system.
-~SYSTEM():Destructor responsible for cleanup operations.
-run():Starts and runs the complete system.
-guestMenu():Displays guest menu options.
-registerAccount(const USER_ACCOUNT& account):Registers a new user account.
-loginAccount(const std::string& username,const std::string& password):Authenticates and logs in a user.
-adminLogin(const std::string& passcode):Verifies administrator login.
-getAllUsers() const:Returns all registered users.
-deleteUser(const std::string& username):Deletes a user account.
-process(bool isLogin, USER_ACCOUNT account):Processes user login or registration operations.
-addProduct(PRODUCT product):Adds a product to the repository.
-removeProduct():Removes a product from the repository.
-updateProduct():Updates existing product information.
-searchProduct():Searches products in the repository.
-getAllProducts():Displays all available products.
-saveToFile():Saves system/product data to files.
-displayMainMenu():Displays the main system menu.
-displayGuestMenu():Displays menu for guest users.
-handleRegistration():Handles user registration process.
-handleUserLogin():Handles user login process.
-handleAdminLogin():Handles administrator login process.
-viewProductList():Displays list of products.

GETTER FUNCTIONS:
-getRepo():Returns pointer to PRODUCT_REPO object.
-getAuthService():Returns pointer to AUTHORITY_SERVICE object.

===============================================================================
*/
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <limits>
#include "PRODUCT_REPO.h"
#include "USER.h"
#include "AUTHORITY_SERVICE.h"
#include "USER_ACCOUNT.h"
#include "CART.h"
#include "BILL_SERVICE.h"

class SYSTEM {
private:
    USER* current_user;
    AUTHORITY_SERVICE* auth; 
    PRODUCT_REPO* repo;    
    bool isAdminLoggedin;
    BILL_SERVICE* bill_service;
    bool isRegistered;

public:
    
    SYSTEM();
    ~SYSTEM(); 

   
    void run();
    void guestMenu();
    
   
    bool registerAccount(const USER_ACCOUNT& account);
    USER* loginAccount(const std::string& username, const std::string& password);
    bool adminLogin(const std::string& passcode);
    std::vector<USER_ACCOUNT> getAllUsers() const;
    bool deleteUser(const std::string& username);
    USER* process(bool isLogin, USER_ACCOUNT account);

    
    void addProduct(PRODUCT product);
    void removeProduct();
    void updateProduct();
    void searchProduct(); // Unified search (no redundancy)
    void getAllProducts();
    void saveToFile();

   
    void displayMainMenu();
    void displayGuestMenu();
    void handleRegistration();
    void handleUserLogin();
    void handleAdminLogin();
    void viewProductList();

    
    PRODUCT_REPO* getRepo();
    AUTHORITY_SERVICE* getAuthService();
};

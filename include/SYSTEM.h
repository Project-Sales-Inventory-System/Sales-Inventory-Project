
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

#pragma once
#include<string>
#include<vector>
#include"BILL_SERVICE.h"
#include"PRODUCT_REPO.h"
#include"USER.h"
#include"AUTHORITY_SERVICE.h"
#include"USER_ACCOUNT.h"
#include"CART.h"
class SYSTEM
{
    private:
    USER* current_user;
    AUTHORITY_SERVICE auth;
    PRODUCT_REPO repo;
    BILL_SERVICE bill_service;
    bool isAdminLoggedin;
    bool isRegistered;
    
    public:
    void displayMainMenu();
    void displayGuestMenu();
    void handleRegistration();
    void handleUserLogin();
    void handleAdminLogin();
    SYSTEM();
    bool registerAccount(const USER_ACCOUNT& account);
    USER* loginAccount(const std::string& username, const std::string& password);
    bool adminLogin(const std::string& passcode);
    std::vector<USER_ACCOUNT> getAllUsers() const;
    bool deleteUser(const std::string& username);
    USER* process(bool isLogin, USER_ACCOUNT account);
    void addProduct(PRODUCT product);
    void removeProduct();
    void updateProduct();
    void searchByName(std:: string name);
    void getAllProducts();
    void saveToFile();
    PRODUCT_REPO& getRepo();
    AUTHORITY_SERVICE& getAuthService();
    BILL_SERVICE& getBillService();
    void run();
    void guestMenu();
};


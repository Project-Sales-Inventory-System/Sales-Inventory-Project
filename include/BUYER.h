#pragma once
#include"../include/USER.h"
//#include"../include/BILL.h"
#include"../include/PRODUCT.h"
#include"AUTHORITY_SERVICE.h"
#include<string>
#include"USER_ACCOUNT.h"
#include"PRODUCT_REPO.h"

class BUYER: public USER
{
    private:
    PRODUCT_REPO* repo;
    void BuyerMenu();
    void handleSearch();
    
    public:
    BUYER(USER_ACCOUNT Bdetails, PRODUCT_REPO& repository);

    bool authenticate(AUTHORITY_SERVICE& auth);
    void performAction();
    std:: string getUsername() const;
    void viewProduct(std:: string);
    void searchProduct(std:: string);
    // void myProducts();
    // void placeOrder();
    // void viewCart();
    // void editCart();
    // void requestBill();
    void startSession();
};
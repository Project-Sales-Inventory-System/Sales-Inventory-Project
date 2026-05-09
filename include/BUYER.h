#pragma once
#include"../include/USER.h"
#include"../include/PRODUCT.h"
#include"../include/AUTHORITY_SERVICE.h"
#include<string>
#include"../include/USER_ACCOUNT.h"
#include"../include/PRODUCT_REPO.h"
#include"../include/CART.h"
#include"../include/BILL_SERVICE.h"

class BUYER: public USER
{
    private:
    PRODUCT_REPO* repo;
    BILL_SERVICE* bill_service;
    CART cart;
    void BuyerMenu();
    void handleSearch();
    
    public:
    BUYER(USER_ACCOUNT Bdetails, PRODUCT_REPO& repository, BILL_SERVICE& bill_svc);

    bool authenticate(AUTHORITY_SERVICE& auth);
    void performAction();
    std:: string getUsername() const;
    void viewProduct(std:: string);
    void searchProduct(std:: string);
    void myProducts();
    void placeOrder();
    void viewCart();
    void editCart();
    void requestBill();
    void startSession();
};
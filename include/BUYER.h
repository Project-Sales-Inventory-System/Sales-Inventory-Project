#pragma once
#include"USER.h"
#include"BILL.h"
#include"BILL_SERVICE.h"
#include"PRODUCT.h"
#include"AUTHORITY_SERVICE.h"
#include<string>
#include"USER_ACCOUNT.h"
#include"PRODUCT_REPO.h"
#include"CART.h"


class BUYER: public USER
{
    private:
    PRODUCT_REPO* repo;
    BILL_SERVICE* bill_service;
    CART cart;
    BILL bill;
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
    void checkout();
    void startSession();
};
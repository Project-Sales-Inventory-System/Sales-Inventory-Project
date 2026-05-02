#pragma once
#include"../include/USER.h"
//#include"../include/BILL.h"
#include"../include/PRODUCT.h"
#include"AUTHORITY_SERVICE.h"
#include<string>
#include"USER_ACCOUNT.h"
#include"PRODUCT_REPO.h"

class SELLER: public USER
{
    private:
    PRODUCT_REPO* repo;
    void SellerMenu();
    
    public:
    SELLER(USER_ACCOUNT sDetails, PRODUCT_REPO& repository);
    bool  authenticate(AUTHORITY_SERVICE& auth);
    std:: string getUsername() const;
    void  performAction();
    void viewProduct(std:: string);
    void searchProduct(std::string);
    void addProduct(PRODUCT product);
    void startSession();
};
#pragma once
#include "../include/USER_ACCOUNT.h"
//#include "CART.h"
class AUTHORITY_SERVICE;
class PRODUCT_REPO;

#include<string>
class USER
{
   protected:
   USER_ACCOUNT user_acc;
   private:
   //CART* cart;
   public:
    USER();
    virtual bool authenticate(AUTHORITY_SERVICE& auth)=0;
    virtual void performAction()=0;
    virtual std:: string getUsername() const=0;
    virtual ~USER()=default;
    virtual void viewProduct(std:: string)=0;
    virtual void searchProduct(std:: string)=0;
   
    USER_ACCOUNT getAccount() const;
    Authority getAuthority() const;
    
    // UI Handler Methods - Separated for easier UI modification
    static void handleUserRegistrationUI(AUTHORITY_SERVICE& auth_service);
    static void handleUserLoginUI(AUTHORITY_SERVICE& auth_service, PRODUCT_REPO& repo);

};
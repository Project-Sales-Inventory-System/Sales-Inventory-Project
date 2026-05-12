/*
USER class is an abstract base class representing a generic user in the system.

STANDARD LIBRARIES USED:
-string:Used for text handling.

FORWARD DECLARATIONS:
-AUTHORITY_SERVICE:Handles authentication and user management.
-PRODUCT_REPO:Manages product repository operations.
-BILL_SERVICE:Handles billing services.

PROTECTED DATA MEMBERS:
-user_acc:Stores account information of the user.

PUBLIC FUNCTIONS:
-USER():Default constructor.

PURE VIRTUAL FUNCTIONS:
-authenticate(AUTHORITY_SERVICE& auth):Authenticates the user.
-performAction():Performs user-specific actions.
-getUsername() const:Returns username of the user.
-viewProduct(std::string):Displays product details.
-searchProduct(std::string):Searches for products.
~USER() = default,Ensures proper cleanup in derived classes.

GENERAL MEMBER FUNCTIONS:
-getAccount() const:Returns USER_ACCOUNT information.
-getAuthority() const:Returns user authority level.

STATIC FUNCTIONS:
-handleUserRegistrationUI(AUTHORITY_SERVICE& auth_service):Handles user registration interface and process.
-handleUserLoginUI(AUTHORITY_SERVICE& auth_service,PRODUCT_REPO& repo, BILL_SERVICE& bill_svc):Handles user login interface and session initialization.
*/
#pragma once
#include "../include/USER_ACCOUNT.h"
class AUTHORITY_SERVICE;
class PRODUCT_REPO;
class BILL_SERVICE;

#include<string>
class USER
{
   protected:
   USER_ACCOUNT user_acc;
   private:
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
    
    static bool handleUserRegistrationUI(AUTHORITY_SERVICE& auth_service);
    static void handleUserLoginUI(AUTHORITY_SERVICE& auth_service, PRODUCT_REPO& repo, BILL_SERVICE& bill_svc);

};
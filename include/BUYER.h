/*

DESCRIPTION:
BUYER class : represents a buyer in the system.

STANDARD LIBRARIES USED:
-string:Used for text handling.

BUYER : public USER-inheritance

PRIVATE DATA MEMBERS:
-repo:Pointer to PRODUCT_REPO object used for product access.
-bill_service:Pointer to BILL_SERVICE object used for billing operations.
cart:Shopping cart belonging to the buyer.

PRIVATE FUNCTIONS:
-BuyerMenu():Displays buyer menu options.
-handleSearch():Handles product search functionality.

PUBLIC FUNCTIONS:
-BUYER(USER_ACCOUNT Bdetails,PRODUCT_REPO& repository,BILL_SERVICE& bill_svc):Constructor that initializes buyer details and services.
-authenticate(AUTHORITY_SERVICE& auth):Authenticates buyer using authority service.
-performAction():Performs buyer-selected operations.
-getUsername() const:Returns buyer username.
-viewProduct(std::string):Displays details of a specific product.
-searchProduct(std::string):Searches for products using keywords or names.
-getCartItemCount() const:Returns total number of items in cart.
-getCartTotal():Returns total cart amount.
-myProducts():Displays products associated with buyer/cart.
-placeOrder():Places order for products in cart.
-viewCart():Displays cart contents.
-editCart():Allows modification of cart items.
-requestBill():Generates or requests bill for placed order.
-startSession():Starts buyer interaction session.
*/
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
    int getCartItemCount() const ;
    double getCartTotal(); 
    void myProducts();
    void placeOrder();
    void viewCart();
    void editCart();
    void requestBill();
    void startSession();
};
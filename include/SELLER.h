/*
SELLER class represents a seller or vendor in the system.

SELLER : public USER-inheritance

PRIVATE FUNCTIONS:
-SellerMenu():Displays seller menu options.
-displayResults(const std::vector<PRODUCT>& results):Displays product search results.

PUBLIC FUNCTIONS:
-SELLER(USER_ACCOUNT sDetails,:PRODUCT_REPO& repository):Constructor that initializes seller details and repository.
-authenticate(AUTHORITY_SERVICE& auth):Authenticates seller using authority service.
-getUsername() const:Returns seller username.
-performAction():Performs seller-selected operations.
-viewProduct(std::string):Displays details of a specific product.
-searchProduct(std::string):Searches products using product name or keyword.
-addProduct(PRODUCT product):Adds a new product to the repository.
-startSession():Starts seller interaction session.

*/
#pragma once
#include"../include/USER.h"
#include"../include/PRODUCT.h"
#include"../include/AUTHORITY_SERVICE.h"
#include<string>
#include "../include/ConsoleHelper.h"
#include"../include/USER_ACCOUNT.h"
#include"../include/PRODUCT_REPO.h"

class SELLER: public USER
{
    private:
    PRODUCT_REPO* repo;
    void SellerMenu();
    void displayResults(const std::vector<PRODUCT>& results); // add this
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
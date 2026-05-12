/*
PRODUCT_SERVICE class : provides services like displayProduct and searchProduct

PRIVATE DATA MEMBERS:
-repository:Pointer to PRODUCT_REPO object used for accessing product data and operations.

PUBLIC FUNCTIONS:
-PRODUCT_SERVICE(PRODUCT_REPO& repo):Constructor that initializes the product repository reference.
-displayProducts():Displays all available products from the repository.
-searchProducts(std::string):Searches products using a product name or keyword.

*/
#pragma once
#include<string>
#include"../include/PRODUCT_REPO.h"
class PRODUCT_SERVICE
{
    private: 
    PRODUCT_REPO* repository;
    public:
    PRODUCT_SERVICE(PRODUCT_REPO& repo);
    void displayProducts();
    void searchProducts(std::string);

};
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
#include "../include/PRODUCT_SERVICE.h"
#include<iostream>
using namespace std;

PRODUCT_SERVICE::PRODUCT_SERVICE(PRODUCT_REPO& repo)
{
    repository = &repo;
}

void PRODUCT_SERVICE::displayProducts()
{
    if (repository)
    {
        repository->getAllProducts(true);
    }
}

void PRODUCT_SERVICE::searchProducts(std::string keyword)
{
    if (repository)
    {
        repository->searchByName(keyword);
    }
}
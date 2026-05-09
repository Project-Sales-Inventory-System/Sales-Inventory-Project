#pragma once
#include <string>
#include <vector>
#include "../include/BILL.h"
#include "../include/CART.h"
#include "PRODUCT_REPO.h" // Include this to use PRODUCT_REPO in parameters

class BILL_SERVICE
{
private:
    std::vector<BILL> allBills;
    int bill_count;
    
    void saveSalesFromFile();
    void loadSalesFromFile();

public:
    BILL_SERVICE();
    ~BILL_SERVICE();
    
    BILL createBILL(CART cart, int user_ID);
    BILL autoGenerateBill(CART cart);
    
    void autoConfirmSale(int bill_id, PRODUCT_REPO& repo); 
    
    void getSaleReport();
};
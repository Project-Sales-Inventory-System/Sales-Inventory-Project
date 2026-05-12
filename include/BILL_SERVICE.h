/*
class BILL_SERVICE:manages billing and sales operations in the system.

STANDARD LIBRARIES USED:
-vector:Used for storing collections of data.
-string:Used for text handling.

PRIVATE DATA MEMBERS:
-allBills:Stores all generated bills in the system.
-bill_count:Maintains total number of generated bills.

PRIVATE FUNCTIONS:
-saveSalesFromFile():Saves all sales/billing data to file storage.
-loadSalesFromFile():Loads existing sales/billing data from file storage.

PUBLIC FUNCTIONS:
-BILL_SERVICE():Constructor that initializes the billing service.
-~BILL_SERVICE():Destructor responsible for cleanup operations.
-createBILL(CART cart, int user_ID):Creates a bill for a specific user using cart details.
-autoGenerateBill(CART cart):Automatically generates a bill from cart information.
-autoConfirmSale(int bill_id, PRODUCT_REPO& repo):Confirms a completed sale and updates product inventory.
-getSaleReport():Displays or generates sales reports.

*/
#pragma once
#include <string>
#include <vector>
#include "../include/BILL.h"
#include "../include/CART.h"
#include "PRODUCT_REPO.h" 

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
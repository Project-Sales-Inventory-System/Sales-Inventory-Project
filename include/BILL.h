/*

BILL class represents a customer bill or invoice generated after purchasing products from the system.

STANDARD LIBRARIES USED:
-vector:Used for storing collections of data.
-string:Used for text handling.

PRIVATE DATA MEMBERS:
-billId:Unique identifier for the bill.
-customerId:Stores the ID of the customer associated with the bill.
-items:Vector containing all purchased products.
-item_count:Stores total number of purchased items.
-total_amount:Stores total bill amount.
-date:Stores bill generation date.
-payment_status:Stores current payment status

PRIVATE FUNCTIONS:
-getCurrentDate():Returns the current system date as a string.

PUBLIC FUNCTIONS:
-BILL():Default constructor.
-BILL(int id, int custId, const CART& c):Parameterized constructor that creates a bill using cart data.
-~BILL():Destructor for BILL class.
-generateBill():Generates the bill details and calculations.
-displayBill():Displays bill information.
-confirmPayment():Updates payment status after successful payment.

GETTER FUNCTIONS:
-getBillId():Returns bill ID.
-getUserId():Returns customer ID.
-getItemCount():Returns total number of purchased items.
-getTotalAmount():Returns total bill amount.
-getDate():Returns bill generation date.
-getPaymentStatus():Returns payment status.
-getItems():Returns list of purchased products.

SETTER FUNCTIONS:
-setCustomerId(int id):Sets customer ID.
-setBillId(int id):Sets bill ID.
-addItem(const PRODUCT& product):Adds a product to the bill.
-setPaymentStatus(std::string status):Updates payment status.

===============================================================================
*/
#pragma once
#include <vector>
#include <string>
#include "PRODUCT.h"
#include "CART.h"

class BILL {
private:
    int billId;
    int customerId;
    std::vector<PRODUCT> items;
    int item_count;
    double total_amount;
    std::string date;
    std::string payment_status;
    std::string getCurrentDate();

public:
    BILL(); 
    BILL(int id, int custId, const CART& c);
    ~BILL();

    void generateBill();
    void displayBill();
    void confirmPayment();

    // Getters
    int getBillId() const;
    int getUserId() const;
    void setCustomerId(int id);
    int getItemCount() const;
    double getTotalAmount() const ;
    std::string getDate() const ;
    void setBillId(int id);
    void addItem(const PRODUCT& product);
    void setPaymentStatus(std::string status);
    std::string getPaymentStatus() const;
    const std::vector<PRODUCT>& getItems() const;
};
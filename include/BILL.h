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
    CART& cart; 
    std::string getCurrentDate();

public:
    BILL(); 
    BILL(int id, int custId, CART& c);
    ~BILL();

    void generateBill();
    void displayBill();
    void confirmPayment();

    int getBillId() const;
    int getUserId() const;
    std::string getPaymentStatus() const;
    CART& getCart();
};
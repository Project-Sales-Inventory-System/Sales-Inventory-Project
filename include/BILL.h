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

    // Getters
    int getBillId() const;
    int getUserId() const;
    int getItemCount() const { return item_count; }
    double getTotalAmount() const { return total_amount; }
    std::string getDate() const { return date; }
    std::string getPaymentStatus() const { return payment_status; }
    CART& getCart();
};
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
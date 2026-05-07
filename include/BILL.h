#pragma once
#include<string>
#include"PRODUCT.h"
#include"CART.h"
#include<vector>
class BILL
{
    private:
    CART* cart;
    std::string customerId;
    std::vector<PRODUCT> items;
    int item_count;
    float total_amount;
    std:: string date;
    std:: string payment_status;
    std::string getCurrentDate();
    public:
    BILL();
    BILL(std::string custId, CART& cart);
    ~BILL();
    void generateBill();
    void displayBill();
    void markAsPaid();
    void saveBillToSalesReport();
    float getTotalAmount() const;
    int getItemCount() const;
    std::string getCustomerId() const;
    std::string getDate() const;
    std::string getPaymentStatus() const;
    const std::vector<PRODUCT>& getItems() const;
};
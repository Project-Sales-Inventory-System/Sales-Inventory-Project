#pragma once
#include<string>
#include"../include/PRODUCT.h"
#include"../include/CART.h"
class BILL
{
    private:
    int billId;
    int customerId;
    std::vector<PRODUCT> items;
    int item_count;
    float total_amount;
    std:: string date;
    std:: string payment_status;
    CART cart;
    std::string getCurrentDate();
    public:
    BILL();
    BILL(int id, int custId, CART& cart);
    ~BILL();
    void generateBill();
    void displayBill();
};
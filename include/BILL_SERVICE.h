#pragma  once
#include<string>
#include"../include/BILL.h"
#include"../include/CART.h"
class BILL_SERVICE
{
    private:
    std::vector<BILL> allBills;
    int bill_count;
    public:
    BILL_SERVICE();
    ~BILL_SERVICE();
    BILL createBILL(CART cart, int user_ID);
    BILL autoGenerateBill(CART cart);
    void autoConfirmSale(int bill_id);
    BILL* getSaleReport(int & count);
};
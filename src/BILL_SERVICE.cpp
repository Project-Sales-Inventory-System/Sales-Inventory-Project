#include<iostream>
#include<vector>
#include<string>
#include"../include/BILL_SERVICE.h"
#include"../include/BILL.h"
#include"../include/CART.h"
#include<iomanip>
using namespace std;
BILL_SERVICE::BILL_SERVICE()
{
    bill_count = 0;
}
BILL_SERVICE::~BILL_SERVICE()
{
    allBills.clear();
}
BILL BILL_SERVICE::createBILL(CART cart, int user_ID)
{
    if (cart.getItemCount() == 0) 
    {
        std::cout << "Error: Cart is empty! Cannot generate bill." << std::endl;
        return BILL(); 
    }
    int new_BILL_ID = bill_count + 1;
    BILL newBILL(new_BILL_ID,user_ID, cart);

    newBILL.generateBill();
    newBILL.displayBill();

    allBills.push_back(newBILL);
    bill_count ++;
    return newBILL;
}
void BILL_SERVICE::autoConfirmSale(int bill_id)
{
    cout << "Enter Your Bill_ID:" << endl;
    cin >> bill_id;
    for (int i = 0; i < allBills.size(); i++)
    {
        if (allBills[i].getBillId() == bill_id) 
        {

            //check payment status 
            if (allBills[i].getPaymentStatus() == "Confirmed") 
            {
                std::cout << "Bill ID " << bill_id << " is already confirmed!" << std::endl;
                return;
            }

            //confirms pending status
            allBills[i].confirmPayment();
            std::cout << "Bill ID " << bill_id << " has been confirmed!" << std::endl;
            return;
        }
    }

    std::cout << "Bill ID " << bill_id << " not found!" << std::endl;
}
BILL* BILL_SERVICE::getSaleReport(int & count)
{
    count = allBills.size();
    if (count == 0) 
    {
        std::cout << "No bills found!" << std::endl;
        return nullptr;
    }
    return allBills.data();
}
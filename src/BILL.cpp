#include<vector>
#include<iostream>
#include<string>
#include<iomanip>
#include<ctime>
#include"../include/BILL.h"
#include"../include/CART.h"
#include"../include/ConsoleHelper.h"
#include"../include/UI_config.h"
using namespace std;
BILL::BILL()
{
    billId        = 0;
    customerId    = 0;
    item_count    = 0;
    total_amount  = 0.0;
    payment_status = "UNPAID";
}
BILL::BILL(int id, int custId, CART& c)
{
    billId        = id;
    customerId    = custId;
    cart          = c;
    item_count    = 0;
    total_amount  = 0.0;
    payment_status = "UNPAID";
}
void BILL::generateBill()
{
    items = cart.cart_items;
    item_count = 0;
    total_amount = 0.0;
    for (const auto& p : items) {
        item_count   += p.getQuantity();
        total_amount += p.getPrice() * p.getQuantity();  // fixed: += not -=
    }
    ConsoleHelper::SetColor(12);
    payment_status = "⚠️ UNPAID";
    date = getCurrentDate();

    ConsoleHelper::SetColor(10);
    cout << endl;
    cout << " Bill #" << billId << endl;
    cout << " Generated on:" << date << endl;
    ConsoleHelper::ResetColor();
}
void BILL::displayBill()
{
    ConsoleHelper::ClearScreen();
    ConsoleHelper::Header();
    ConsoleHelper::SetColor(10);
    cout << string(50, '=') << endl;
    cout << " BILL RECEIPT " << endl;
    cout << string(50, '=') << endl;
    ConsoleHelper::ResetColor();
    
    //Bill Info
    cout << " Bill ID:" << endl;
    cout << " Customer ID:" << endl;
    cout << " Date:" << endl;
    cout << " Payment Status:" << endl;
    
    if (payment_status == "PAID")
        ConsoleHelper::SetColor(10);   // green
    else
        ConsoleHelper::SetColor(12);   // red
    cout << payment_status << endl;
    ConsoleHelper::ResetColor();

    // Table header
    cout << left << setw(20) << " Product Name" << "|" << setw(10) << " Quantity" << "|" << setw(12) << " Price (Rs)" << "|" << setw(15) << " Category" << endl;

    // Partition line
    cout << string(20, '-') << "+" << string(10, '-') << "+" << string(12, '-') << "+" << string(15, '-') << endl;
        
        for (const auto& p : items) {
            cout << left << setw(20) << p.getName() << "|" << setw(10) << p.getQuantity() << "|" << setw(12) << fixed << setprecision(2) << p.getPrice() << "|" << setw(15) << p.getCategory()  << endl;
        }
        // Partition line before totals
        cout << string(20, '-') << "+" << string(10, '-') << "+" << string(12, '-') << "+" << string(15, '-') << endl;

        // Totals
        cout << left << setw(30) << " TOTAL ITEMS: " << item_count << endl;
        cout << left << setw(30) << " TOTAL AMOUNT: Rs" << fixed << setprecision(2) << total_amount << endl;

    ConsoleHelper::PrintDivider();
    cout << endl;
    ConsoleHelper::SetColor(13);
    cout << "Press Enter to continue...";
    ConsoleHelper::SetColor(7);
    cin.ignore(10000, '\n'); 
}
//Current Date function
string BILL::getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << 1900 + ltm->tm_year << "-" << setw(2) << setfill('0') << 1 + ltm->tm_mon << "-" << setw(2) << setfill('0') << ltm->tm_mday;
    return ss.str();
}
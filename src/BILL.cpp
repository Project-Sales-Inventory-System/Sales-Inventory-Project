#include<vector>
#include<iostream>
#include<string>
#include<iomanip>
#include<ctime>
#include<fstream>
#include<sstream>
#include"../include/CART.h"
#include"../include/BILL.h"
#include"../include/ConsoleHelper.h"
#include"../include/UI_config.h"

#include"../include/USER.h"
using namespace std;
BILL::BILL()
{
    customerId    = "";
    item_count    = 0;
    total_amount  = 0.0;
    payment_status = "UNPAID";
}
BILL::BILL(std::string custId, CART& c)
{
    customerId    = custId;
    cart          = &c;
    item_count    = 0;
    total_amount  = 0.0;
    payment_status = "UNPAID";
}
BILL::~BILL() {}

void BILL::generateBill()
{
    items = cart->cart_items;
    item_count = 0;
    total_amount = 0.0;
    for (const auto& p : items) {
        item_count   += p.getQuantity();
        total_amount += p.getPrice() * p.getQuantity();
    }
    payment_status = "UNPAID";
    date = getCurrentDate();
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
    cout << " Customer: " << customerId << endl;
    cout << " Date: " << date << endl;
    cout << " Payment Status: ";
    
    if (payment_status == "PAID")
        ConsoleHelper::SetColor(10);   // green
    else
        ConsoleHelper::SetColor(12);   // red
    cout << payment_status << endl;
    ConsoleHelper::ResetColor();


    cout << left << setw(20) << " Product Name" << "|" << setw(10) << " Quantity" << "|" << setw(12) << " Price (Rs)" << "|" << setw(15) << " Category" << endl;


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

string BILL::getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << 1900 + ltm->tm_year << "-" << setw(2) << setfill('0') << 1 + ltm->tm_mon << "-" << setw(2) << setfill('0') << ltm->tm_mday;
    return ss.str();
}

void BILL::markAsPaid() {
    payment_status = "PAID";
}

void BILL::saveBillToSalesReport() {
    ofstream reportFile("sales.txt", ios::app);
    if (!reportFile.is_open()) {
        ConsoleHelper::SetColor(12);
        cout << "Error: Could not open sales.txt for writing!" << endl;
        ConsoleHelper::ResetColor();
        return;
    }
    
    // Write header separator
    reportFile << string(80, '=') << endl;
    reportFile << "SALE REPORT | Date: " << date << " | Customer: " << customerId << endl;
    reportFile << string(80, '=') << endl;
    
    // Write items
    reportFile << left << setw(25) << "Product Name" << setw(10) << "Qty" << setw(15) << "Price (Rs)" << setw(15) << "Category" << endl;
    reportFile << string(80, '-') << endl;
    
    for (const auto& p : items) {
        reportFile << left << setw(25) << p.getName() 
                   << setw(10) << p.getQuantity() 
                   << setw(15) << fixed << setprecision(2) << p.getPrice() 
                   << setw(15) << p.getCategory() << endl;
    }
    
    reportFile << string(80, '-') << endl;
    reportFile << "Total Items: " << item_count 
               << " | Total Amount: Rs " << fixed << setprecision(2) << total_amount 
               << " | Status: " << payment_status << endl;
    reportFile << string(80, '=') << endl << endl;
    
    reportFile.close();
}

float BILL::getTotalAmount() const {
    return total_amount;
}

int BILL::getItemCount() const {
    return item_count;
}

std::string BILL::getCustomerId() const {
    return customerId;
}

std::string BILL::getDate() const {
    return date;
}

std::string BILL::getPaymentStatus() const {
    return payment_status;
}

const std::vector<PRODUCT>& BILL::getItems() const {
    return items;
}
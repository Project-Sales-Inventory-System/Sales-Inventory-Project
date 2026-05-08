#include "../include/BILL.h"
#include "../include/ConsoleHelper.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
using namespace std;

static CART dummyCart;

BILL::BILL()
    : billId(0), customerId(0), item_count(0), total_amount(0.0),
      payment_status("UNPAID"), cart(dummyCart)
{}

BILL::BILL(int id, int custId, CART& c)
    : billId(id), customerId(custId), cart(c), item_count(0),
      total_amount(0.0), payment_status("UNPAID")
{}

BILL::~BILL() {
    items.clear();
}

int BILL::getBillId() const { return billId; }
int BILL::getUserId() const { return customerId; }
CART& BILL::getCart() { return cart; }
string BILL::getPaymentStatus() const { return payment_status; }

void BILL::confirmPayment() {
    payment_status = "PAID";
    ConsoleHelper::SetColor(10);
    cout << "\n Payment confirmed for Bill #" << billId << ".\n";
    ConsoleHelper::ResetColor();
}

void BILL::generateBill() {
    items = cart.getItems();
    item_count = 0;
    total_amount = 0.0;

    for (const auto& p : items) {
        item_count += p.getQuantity();
        total_amount += p.getPrice() * p.getQuantity();
    }

    payment_status = "UNPAID";
    date = getCurrentDate();

    ConsoleHelper::SetColor(10);
    cout << "\n Bill #" << billId << " generated successfully.\n";
    ConsoleHelper::ResetColor();
}

void BILL::displayBill() {
    ConsoleHelper::ClearScreen();
    ConsoleHelper::Header();

    ConsoleHelper::SetColor(15);
    cout << string(50, '=') << endl;
    ConsoleHelper::SetColor(10);
    cout << "                BILL RECEIPT" << endl;
    ConsoleHelper::SetColor(15);
    cout << string(50, '=') << endl;
    ConsoleHelper::ResetColor();

    cout << " Bill ID     : " << billId << endl;
    cout << " Customer ID : " << customerId << endl;
    cout << " Date        : " << date << endl;
    cout << " Status      : ";

    if (payment_status == "PAID")
        ConsoleHelper::SetColor(10);
    else
        ConsoleHelper::SetColor(12);

    cout << payment_status << endl;
    ConsoleHelper::ResetColor();

    cout << "\n";
    cout << left
         << setw(20) << " Product Name" << "|"
         << setw(8)  << " Qty"          << "|"
         << setw(14) << " Price (Rs)"   << "|"
         << setw(15) << " Category"     << endl;

    cout << string(20, '-') << "+"
         << string(8,  '-') << "+"
         << string(14, '-') << "+"
         << string(15, '-') << endl;

    for (const auto& p : items) {
        cout << left
             << setw(20) << (" " + p.getName())     << "|"
             << setw(8)  << (" " + to_string(p.getQuantity())) << "|"
             << " " << setw(13) << fixed << setprecision(2) << p.getPrice() << "|"
             << setw(15) << (" " + p.getCategory())  << endl;
    }

    cout << string(58, '-') << endl;
    cout << left << setw(30) << " TOTAL ITEMS  :" << item_count << endl;
    cout << left << setw(30) << " TOTAL AMOUNT :" << " Rs "
         << fixed << setprecision(2) << total_amount << endl;

    ConsoleHelper::PrintDivider();
    ConsoleHelper::SetColor(13);
    cout << "\n Press Enter to continue...";
    ConsoleHelper::ResetColor();
    cin.ignore(10000, '\n');
    cin.get();
}

string BILL::getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << 1900 + ltm->tm_year << "-"
       << setw(2) << setfill('0') << 1 + ltm->tm_mon << "-"
       << setw(2) << setfill('0') << ltm->tm_mday;
    return ss.str();
}
#include "../include/BILL.h"
#include "../include/ConsoleHelper.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

using namespace std;

BILL::BILL()
    : billId(0), customerId(0), item_count(0), total_amount(0.0),
      payment_status("UNPAID") 
{}

BILL::BILL(int id, int custId, const CART& c)
    : billId(id), customerId(custId), item_count(0),
      total_amount(0.0), payment_status("UNPAID"), items(c.getItems())
{}

BILL::~BILL() {
    items.clear();
}

int BILL::getBillId() const { return billId; }
int BILL::getUserId() const { return customerId; }
void BILL::setCustomerId(int id) { customerId = id; }
void BILL::setBillId(int id) { billId = id; }
int BILL::getItemCount() const { return item_count; }
double BILL::getTotalAmount() const { return total_amount; }
std::string BILL::getDate() const { return date; }
void BILL::setPaymentStatus(std::string status) { payment_status = status; }
const std::vector<PRODUCT>& BILL::getItems() const { return items; }
string BILL::getPaymentStatus() const { return payment_status; }

void BILL::confirmPayment() {
    payment_status = "PAID";
}
void BILL::addItem(const PRODUCT& product) {
    items.push_back(product);
    item_count += product.getQuantity();
    total_amount += product.getPrice() * product.getQuantity();
}
void BILL::generateBill() {
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
    ConsoleHelper::SetColor(10);
    cout << string(50, '=') << endl;
    cout << "                BILL RECEIPT " << endl;
    cout << string(50, '=') << endl;
    ConsoleHelper::ResetColor();

    cout << " Bill ID: " << billId << endl;
    cout << " Customer ID: " << customerId << endl;
    cout << " Date: " << date << endl;
    cout << " Payment Status: ";

    if (payment_status == "PAID")
        ConsoleHelper::SetColor(10);
    else
        ConsoleHelper::SetColor(12);

    cout << payment_status << endl;
    ConsoleHelper::ResetColor();

    cout << left << setw(20) << " Product Name" << "|"
         << setw(10) << " Qty" << "|"
         << setw(12) << " Price (Rs)" << "|"
         << setw(15) << " Category" << endl;

    cout << string(20, '-') << "+" << string(10, '-') << "+"
         << string(12, '-') << "+" << string(15, '-') << endl;

    for (const auto& p : items) {
        cout << left << setw(20) << p.getName() << "|"
             << setw(10) << p.getQuantity() << "|"
             << setw(12) << fixed << setprecision(2) << p.getPrice() << "|"
             << setw(15) << p.getCategory() << endl;
    }

    cout << string(50, '-') << endl;
    cout << left << setw(30) << " TOTAL ITEMS: " << item_count << endl;
    cout << left << setw(30) << " TOTAL AMOUNT: Rs" << fixed << setprecision(2) << total_amount << endl;

    ConsoleHelper::PrintDivider();
    cout << "\nPress Enter to continue...";
    cin.ignore(10000, '\n');
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
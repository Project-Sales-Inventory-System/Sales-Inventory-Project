#include"../include/BILL_SERVICE.h"
#include"../include/ConsoleHelper.h"
#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

BILL_SERVICE::BILL_SERVICE() {
    loadSalesFromFile();
}

BILL_SERVICE::~BILL_SERVICE() {}

void BILL_SERVICE::loadSalesFromFile() {
    ifstream file("sales.txt");
    if (!file.is_open()) return;
    
    string line;
    while (getline(file, line)) {
        if (line.find("SALE REPORT") != string::npos) {
            SaleRecord record;
            
            size_t datePos = line.find("Date: ") + 6;
            size_t custPos = line.find("Customer: ") + 10;
            record.date = line.substr(datePos, 10);
            record.customer = line.substr(custPos);
            
            // Read total line
            string totalLine;
            while (getline(file, totalLine)) {
                if (totalLine.find("Total Items:") != string::npos) {
                    sscanf(totalLine.c_str(), "Total Items: %d | Total Amount: Rs %f | Status: %s",
                           &record.items, &record.amount, &record.status[0]);
                    saleReports.push_back(record);
                    break;
                }
            }
        }
    }
    file.close();
}

void BILL_SERVICE::autoConfirmAndSaveSale(BILL& bill) {
    
    bill.markAsPaid();
    
    
    bill.saveBillToSalesReport();
    
    // Add to in-memory sales
    SaleRecord record;
    record.customer = bill.getCustomerId();
    record.date = bill.getDate();
    record.amount = bill.getTotalAmount();
    record.items = bill.getItemCount();
    record.status = "PAID";
    saleReports.push_back(record);
    
    ConsoleHelper::SetColor(10);
    cout << "\n✓ Payment Confirmed and Sale Recorded!" << endl;
    ConsoleHelper::ResetColor();
}

void BILL_SERVICE::displayAllSales() const {
    if (saleReports.empty()) {
        cout << "No sales records found." << endl;
        return;
    }
    
    ConsoleHelper::ClearScreen();
    ConsoleHelper::Header();
    ConsoleHelper::SetColor(10);
    cout << string(90, '=') << endl;
    cout << "ALL SALES REPORTS" << endl;
    cout << string(90, '=') << endl;
    ConsoleHelper::ResetColor();
    
    cout << left << setw(20) << "Customer" << setw(15) << "Date" << setw(15) << "Amount (Rs)"
         << setw(10) << "Items" << setw(12) << "Status" << endl;
    cout << string(90, '-') << endl;
    
    for (const auto& sale : saleReports) {
        cout << left << setw(20) << sale.customer << setw(15) << sale.date
             << setw(15) << fixed << setprecision(2) << sale.amount
             << setw(10) << sale.items << setw(12) << sale.status << endl;
    }
    
    cout << string(90, '-') << endl;
    cout << "Total Sales: " << saleReports.size() << " | Total Revenue: Rs "
         << fixed << setprecision(2) << getTotalRevenue() << endl;
    cout << string(90, '=') << endl;
    
    cout << "\nPress Enter to continue...";
    cin.ignore(10000, '\n');
}

void BILL_SERVICE::displaySalesByCustomer(const std::string& customer) const {
    vector<SaleRecord> customerSales;
    for (const auto& sale : saleReports) {
        if (sale.customer == customer) {
            customerSales.push_back(sale);
        }
    }
    
    if (customerSales.empty()) {
        cout << "No sales found for customer: " << customer << endl;
        return;
    }
    
    ConsoleHelper::ClearScreen();
    ConsoleHelper::Header();
    ConsoleHelper::SetColor(10);
    cout << "Sales for Customer: " << customer << endl;
    cout << string(80, '-') << endl;
    ConsoleHelper::ResetColor();
    
    cout << left << setw(15) << "Date" << setw(15) << "Amount (Rs)"
         << setw(10) << "Items" << setw(12) << "Status" << endl;
    cout << string(80, '-') << endl;
    
    float customerTotal = 0;
    for (const auto& sale : customerSales) {
        cout << left << setw(15) << sale.date << setw(15) << fixed << setprecision(2) << sale.amount
             << setw(10) << sale.items << setw(12) << sale.status << endl;
        customerTotal += sale.amount;
    }
    
    cout << string(80, '-') << endl;
    cout << "Total for this customer: Rs " << fixed << setprecision(2) << customerTotal << endl;
    cout << string(80, '-') << endl;
    
    cout << "\nPress Enter to continue...";
    cin.ignore(10000, '\n');
}

float BILL_SERVICE::getTotalRevenue() const {
    float total = 0;
    for (const auto& sale : saleReports) {
        if (sale.status == "PAID") {
            total += sale.amount;
        }
    }
    return total;
}

int BILL_SERVICE::getTotalSales() const {
    return saleReports.size();
}

void BILL_SERVICE::exportSalesReport() const {
    // Already saved in sales.txt by BILL class
    ConsoleHelper::SetColor(10);
    cout << "Sales report available in sales.txt" << endl;
    ConsoleHelper::ResetColor();
}
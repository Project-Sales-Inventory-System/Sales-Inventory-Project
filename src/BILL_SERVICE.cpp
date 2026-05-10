#include "../include/BILL_SERVICE.h"
#include "../include/ConsoleHelper.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
BILL_SERVICE::BILL_SERVICE() {
    bill_count = 0;
    loadSalesFromFile();
}

BILL_SERVICE::~BILL_SERVICE() {
    saveSalesFromFile();
}

// ─── File I/O ───────────────────────────────────────────────────────────────

void BILL_SERVICE::saveSalesFromFile() {
    std::ofstream file("sales_history.csv");
    for (const auto& bill : allBills) {
        file << bill.getBillId() << "," << bill.getUserId() << "," << bill.getPaymentStatus() << "\n";
    }
    file.close();
}

void BILL_SERVICE::loadSalesFromFile() {
    ifstream file("sales_history.csv");
    if (!file) return;
    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string id, uId, status;
        getline(ss, id, ',');
        getline(ss, uId, ',');
        getline(ss, status, ',');
        if (!id.empty()) {
            bill_count = std::max(bill_count, std::stoi(id));
            // In a full build, you'd push a reconstructed bill to allBills here
        }
    }
    file.close();
}

// ─── Bill Creation ───────────────────────────────────────────────────────────

BILL BILL_SERVICE::createBILL(CART cart, int user_ID) {
    bill_count++;
    BILL newBill(bill_count, user_ID, cart);
    newBill.generateBill();
    allBills.push_back(newBill);
    saveSalesFromFile();
    return newBill;
}

BILL BILL_SERVICE::autoGenerateBill(CART cart) {
    return createBILL(cart, 0); // guest user ID = 0
}

// ─── Confirm Sale ────────────────────────────────────────────────────────────

void BILL_SERVICE::autoConfirmSale(int bill_id, PRODUCT_REPO& repo) {
    for (auto& bill : allBills) {
        if (bill.getBillId() == bill_id) {

            if (bill.getPaymentStatus() == "PAID") {
                ConsoleHelper::SetColor(10);
                cout << " Bill #" << bill_id << " is already confirmed.\n";
                ConsoleHelper::ResetColor();
                return;
            }

            
            bill.confirmPayment();

            
            auto items = bill.getItems(); 
            for (auto& item : items) {
                repo.reduceStock(item.getName(), item.getQuantity());
            }

            // 3. Save both states
            saveSalesFromFile();
            repo.saveToFile();

            ConsoleHelper::SetColor(10);
            cout << " Sale confirmed and inventory updated for Bill #"
                 << bill_id << ".\n";
            ConsoleHelper::ResetColor();
            return;
        }
    }

    ConsoleHelper::SetColor(12);
    cout << " Bill ID #" << bill_id << " not found.\n";
    ConsoleHelper::ResetColor();
}

// ─── Report ──────────────────────────────────────────────────────────────────



void BILL_SERVICE::getSaleReport() {
    ConsoleHelper::SetColor(10);
    cout << "\n===============================================" << endl;
    cout << "SALES REPORT" << endl;
    cout << "===============================================" << endl;
    ConsoleHelper::ResetColor();
    
    if (allBills.empty()) {
        ConsoleHelper::SetColor(12);
        cout << "⚠️ No sales recorded." << endl;
        ConsoleHelper::ResetColor();
        return;
    }
    
    ConsoleHelper::SetColor(15);
    cout << "BILL ID | USER ID | STATUS | TOTAL ITEMS | AMOUNT" << endl;
    cout << "-----------------------------------------------" << endl;
    ConsoleHelper::ResetColor();
    
    double totalRevenue = 0.0;
    int totalSales = 0;
    
    for (const auto& bill : allBills) {
        if (bill.getPaymentStatus() == "PAID") {
            ConsoleHelper::SetColor(10);
            totalSales++;
            const auto& items = bill.getItems();
            int itemCount = 0;
            double billAmount = 0.0;
            for (const auto& item : items) {
                itemCount += item.getQuantity();
                billAmount += item.getPrice() * item.getQuantity();
            }
            totalRevenue += billAmount;
            
            cout << bill.getBillId() << "     | " 
                 << bill.getUserId() << "      | "
                 << bill.getPaymentStatus() << "   | "
                 << itemCount << "          | Rs "
                 << fixed << setprecision(2) << billAmount << endl;
        }
    }
    
    cout << "-----------------------------------------------" << endl;
    ConsoleHelper::SetColor(11);
    cout << "Total Sales: " << totalSales << endl;
    cout << "Total Revenue: Rs " << fixed << setprecision(2) << totalRevenue << endl;
    ConsoleHelper::ResetColor();
}
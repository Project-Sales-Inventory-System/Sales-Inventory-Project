#include "../include/BILL_SERVICE.h"
#include "../include/ConsoleHelper.h"
#include <fstream>
#include <sstream>
#include <iostream>
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
    ofstream file("sales_history.csv");
    if (!file) {
        ConsoleHelper::SetColor(12);
        cout << "Warning: Could not save sales history.\n";
        ConsoleHelper::ResetColor();
        return;
    }
    for (const auto& bill : allBills) {
        file << bill.getBillId()        << ","
             << bill.getUserId()        << ","
             << bill.getPaymentStatus() << ","
             << bill.getDate()          << ","
             << bill.getTotalAmount()   << ","
             << bill.getItemCount()     << "\n";
    }
    file.close();
}

void BILL_SERVICE::loadSalesFromFile() {
    ifstream file("sales_history.csv");
    if (!file) return;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, uId, status, date, total, itemCount;
        getline(ss, id,        ',');
        getline(ss, uId,       ',');
        getline(ss, status,    ',');
        getline(ss, date,      ',');
        getline(ss, total,     ',');
        getline(ss, itemCount, ',');

        if (!id.empty()) {
            int parsedId = stoi(id);
            bill_count = max(bill_count, parsedId);
            // Full reconstruction requires CART; we only track bill_count here.
            // Push reconstructed bills if CART serialization is added later.
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

            // 1. Mark as paid
            bill.confirmPayment();

            // 2. Reduce stock for each item
            auto items = bill.getCart().getItems();
            for (const auto& item : items) {
                repo.reduceStock(item.getName(), item.getQuantity());
            }

            // 3. Persist changes
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

BILL* BILL_SERVICE::getSaleReport(int& count) {
    count = static_cast<int>(allBills.size());
    return allBills.empty() ? nullptr : allBills.data();
}
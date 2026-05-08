#include "../include/BILL_SERVICE.h"
#include <fstream>
#include <sstream>
#include <iostream>

BILL_SERVICE::BILL_SERVICE() {
    bill_count = 0;
    loadSalesFromFile(); 
}

BILL_SERVICE::~BILL_SERVICE() {
    saveSalesFromFile();
}

void BILL_SERVICE::saveSalesFromFile() {
    std::ofstream file("sales_history.csv");
    for (const auto& bill : allBills) {
        file << bill.getBillId() << "," << bill.getUserId() << "," << bill.getPaymentStatus() << "\n";
    }
    file.close();
}

void BILL_SERVICE::loadSalesFromFile() {
    std::ifstream file("sales_history.csv");
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

void BILL_SERVICE::autoConfirmSale(int bill_id, PRODUCT_REPO& repo) {
    for (auto& bill : allBills) {
        if (bill.getBillId() == bill_id) {
            if (bill.getPaymentStatus() == "Confirmed") {
                std::cout << "Bill already confirmed." << std::endl;
                return;
            }

            // 1. Mark as paid
            bill.confirmPayment();

            
            auto items = bill.getCart().getItems(); 
            for (auto& item : items) {
                repo.reduceStock(item.getName(), item.getQuantity());
            }

            // 3. Save both states
            saveSalesFromFile();
            repo.saveToFile(); 
            
            std::cout << "Sale confirmed and inventory adjusted." << std::endl;
            return;
        }
    }
    std::cout << "Bill ID not found." << std::endl;
}
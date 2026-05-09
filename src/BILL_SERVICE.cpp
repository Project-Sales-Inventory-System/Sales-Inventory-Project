#include "../include/BILL_SERVICE.h"
#include "../include/ConsoleHelper.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

BILL_SERVICE::BILL_SERVICE() {
    bill_count = 0;
    loadSalesFromFile(); 
}

BILL_SERVICE::~BILL_SERVICE() {
    saveSalesFromFile();
}

void BILL_SERVICE::saveSalesFromFile() {
    std::ofstream file("sales_history.csv");
    if (!file) {
        std::cerr << "Error opening sales_history.csv for saving!" << std::endl;
        return;
    }

    for (const auto& bill : allBills) {
        const auto& items = bill.getItems();
        // Format: billId,userId,paymentStatus,itemCount,name,price,qty,category,...
        file << bill.getBillId() << ","
             << bill.getUserId() << ","
             << bill.getPaymentStatus() << ","
             << items.size();

        for (const auto& item : items) {
            file << "," << item.getName()
                 << "," << item.getPrice()
                 << "," << item.getQuantity()
                 << "," << item.getCategory();
        }
        file << "\n";
    }
    file.close();
}

void BILL_SERVICE::loadSalesFromFile() {
    std::ifstream file("sales_history.csv");
    if (!file) return;

    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string id, uId, status, itemCountStr;

        getline(ss, id, ',');
        getline(ss, uId, ',');
        getline(ss, status, ',');
        getline(ss, itemCountStr, ',');

        if (id.empty() || uId.empty()) continue;

        try {
            int billId    = std::stoi(id);
            int userId    = std::stoi(uId);
            int itemCount = std::stoi(itemCountStr);
            bill_count    = std::max(bill_count, billId);

            BILL bill;
            bill.setBillId(billId);
            bill.setCustomerId(userId);
            bill.setPaymentStatus(status);

            for (int i = 0; i < itemCount; i++) {
                std::string name, priceStr, qtyStr, category;
                getline(ss, name,     ',');
                getline(ss, priceStr, ',');
                getline(ss, qtyStr,   ',');
                getline(ss, category, ',');

                if (name.empty()) break;

                PRODUCT p(category, name, std::stod(priceStr), std::stoi(qtyStr));
                bill.addItem(p); 
            }

            allBills.push_back(bill);

        } catch (const std::exception& e) {
            std::cerr << "Error parsing bill record: " << line << std::endl;
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

            
            bill.confirmPayment();

            
            auto items = bill.getItems(); 
            for (const auto& item : items) {
                repo.reduceStock(item.getName(), item.getQuantity());
            }

            
            saveSalesFromFile();
            repo.saveToFile(); 
            
            std::cout << "Sale confirmed and inventory adjusted." << std::endl;
            return;
        }
    }
    std::cout << "Bill ID not found." << std::endl;
}

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

BILL BILL_SERVICE::autoGenerateBill(CART cart) {
    bill_count++;
    BILL bill(bill_count, 0, cart);
    bill.generateBill();
    allBills.push_back(bill);
    return bill;
}

BILL BILL_SERVICE::createBILL(CART cart, int user_ID) {
    bill_count++;
    BILL bill(bill_count, user_ID, cart);
    bill.generateBill();
    allBills.push_back(bill);
    return bill;
}
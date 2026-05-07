#pragma once
#include<string>
#include<vector>
#include"BILL.h"
class BILL_SERVICE
{
    private:
    struct SaleRecord {
        std::string customer;
        std::string date;
        float amount;
        int items;
        std::string status;
    };
    std::vector<SaleRecord> saleReports;
    void loadSalesFromFile();
    
    public:
    BILL_SERVICE();
    ~BILL_SERVICE();
    void autoConfirmAndSaveSale(BILL& bill);
    void displayAllSales() const;
    void displaySalesByCustomer(const std::string& customer) const;
    float getTotalRevenue() const;
    int getTotalSales() const;
    void exportSalesReport() const;
};
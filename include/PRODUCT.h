#pragma once
#include <string>
class PRODUCT
{
    private:
    std::string product_name;
    double product_price;
    int product_qty;
    std::string product_category;
  

public:
    PRODUCT();
    PRODUCT(std::string product_category, std::string product_name, double product_price, int product_qty);
    void setName(std::string name);
    std::string getName() const;
    void setPrice(double price);
    double getPrice() const;
    void setQuantity(int qty);
    int getQuantity() const;
    std::string getCategory() const;
    void displayInfo() const;
    void displaySearchInfo() const;
    void updateQuantity(int qty);
    
    bool operator<(const PRODUCT& other) const;  
    bool operator>(const PRODUCT& other) const;  
};
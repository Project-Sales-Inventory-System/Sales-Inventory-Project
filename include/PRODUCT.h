/*
PRODUCT class represents a product available in the system.

PRIVATE DATA MEMBERS:
-product_name:Stores the name of the product.
-product_price:Stores the price of the product.
-product_qty:Stores available quantity of the product.
-product_category:Stores category of the product.

PUBLIC FUNCTIONS:
-PRODUCT():Default constructor.
-PRODUCT(std::string product_category,std::string product_name,double product_price,int product_qty):Parameterized constructor used to initialize product details.
-setName(std::string name):Sets product name.
-setCategory(std::string name):Sets product category.
-getName() const:Returns product name.
-setPrice(double price):Sets product price.
-getPrice() const:Returns product price.
-setQuantity(int qty):Sets product quantity.
-getQuantity() const:Returns product quantity.
-getCategory() const:Returns product category.
-displayInfo() const:Displays complete product information.
-displaySearchInfo() const:Displays product information for search results.
-updateQuantity(int qty):Updates product quantity.

OPERATOR OVERLOADING:
-operator<(const PRODUCT& other) const:Compares products using less-than operator.
-operator>(const PRODUCT& other) const:Compares products using greater-than operator.


*/
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
    void setCategory(std:: string name);
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
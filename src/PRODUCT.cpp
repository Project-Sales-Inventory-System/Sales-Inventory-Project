#include"PRODUCT.h"
#include<iostream>
#include<iomanip>
using namespace std;
PRODUCT:: PRODUCT()
{
    product_name =" ";
    product_price=0;
    product_qty=0;
    product_category= " ";
}
PRODUCT:: PRODUCT (string product_category, std:: string product_name, double product_price,int product_qty )
{
    this-> product_category= product_category;
    this-> product_name = product_name;
    this-> product_price= product_price;
    this-> product_qty= product_qty;
}
void PRODUCT:: setName( string name)
{
    this-> product_name= name;
}
std::string PRODUCT::getName() const { return product_name;}
void PRODUCT:: setPrice( double price)
{
    this-> product_price= price;
}
double PRODUCT::getPrice() const { return product_price; }
void PRODUCT:: setQuantity( int qty)
{
    this-> product_qty= qty;
}
int PRODUCT::getQuantity() const
{
    return product_qty;
}
std::string PRODUCT::getCategory() const
{
    return product_category;
}

void PRODUCT:: updateQuantity(int qty)
{
    this-> product_qty= qty;
}
bool PRODUCT:: operator<( const PRODUCT& other) const
{
    return product_price<other. product_price;
}
bool PRODUCT:: operator>( const PRODUCT& other) const
{
    return product_price<other. product_price;
}
void PRODUCT:: displayInfo() const
{
    cout << left
         << setw(20) << product_name << "|"
         << setw(15) << product_category << "|"
         << setw(12) << fixed << setprecision(2) << product_price << "|"
         << setw(12) << product_qty << endl;
}

void PRODUCT:: displaySearchInfo() const
{
    cout << product_name << " - Rs" << fixed << setprecision(2) << product_price << endl;
}
#include<cassert>
#include<iostream>
#include"../include/PRODUCT.h"

int main(){
    PRODUCT p1("Electronics", "mobile", 30000.00, 10);

    //Test getName
    assert(p1.getName()=="mobile");

    //Test getPrice
    assert(p1.getPrice()==30000.00);

    //Test getQuantity
    assert(p1.getQuantity()==10);

    //Test setCategory
    p1.setPrice(20000.00);
    assert(p1.getPrice()==20000.00);

    //Test setQuantity
    p1.setQuantity(5);
    assert(p1.getQuantity()==5);

    //Test updateQuantity
    p1.updateQuantity(15);
    assert(p1.getQuantity()==15);

    //Test setName
    p1.setName("smartPhone");
    assert(p1.getName()=="smartPhone");

    //Test getCategory
    assert(p1.getCategory()=="Electronics");

    
    std::cout<<"All PRODUCT tests passed sucessfully!" << std::endl;
    return 0;
}
#include<cassert>
#include<iostream>
#include<sstream>
#include<string>
#include"../include/PRODUCT_SERVICE.h"
#include"../include/PRODUCT_REPO.h"
#include"../include/PRODUCT.h"

int main(){
    PRODUCT_REPO repo;
    PRODUCT p1("clothes", "Shirt", 1000, 5);
    repo.addProduct(p1);

    PRODUCT p2("Electronics", "Laptop", 300000, 5);
    repo.addProduct(p2);

    PRODUCT_SERVICE service(repo);

    // Test displayProducts
    {
        std::ostringstream buffer;
        std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
        service.displayProducts();
        std::cout.rdbuf(old);
        assert(!buffer.str().empty());
        assert(buffer.str().find("Shirt") != std::string::npos);
        assert(buffer.str().find("Laptop") != std::string::npos);
        assert(buffer.str().find("Apple") == std::string::npos);
    }

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
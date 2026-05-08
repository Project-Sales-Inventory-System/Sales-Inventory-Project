#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "../include/PRODUCT_REPO.h"
#include "../include/PRODUCT.h"

int main() {
    PRODUCT_REPO p1;

    PRODUCT P("Clothes", "vest", 500, 10);
    p1.addProduct(P);

    // Test addProduct
    {
        vector<PRODUCT> results = p1.searchByName("vest");
        assert(!results.empty());
        assert(results[0].getName() == "vest" || results[0].getName() == "Vest");
        assert(results[0].getCategory() == "Clothes" || results[0].getCategory() == "clothes");
        assert(results[0].getPrice() == 500);
        assert(results[0].getQuantity() == 10);
    }
    
    // Test searchByName with matching name
    {
        vector<PRODUCT> results = p1.searchByName("vest");
        assert(!results.empty());
        assert(results[0].getName() == "vest");
    }

    // Test searchByName with different case (case insensitive, should find)
    {
        vector<PRODUCT> results = p1.searchByName("Vest");
        assert(!results.empty());
        assert(results[0].getName() == "vest");
    }

    // Test searchByName with non-existing name
    {
        vector<PRODUCT> results = p1.searchByName("xyz");
        assert(results.empty());
    }

    // Test searchByCategory with matching category
    {
        vector<PRODUCT> results = p1.searchByCategory("Clothes");
        assert(!results.empty());
        assert(results[0].getCategory() == "Clothes");
    }

    // Test searchByCategory with different case (case insensitive, should find)
    {
        vector<PRODUCT> results = p1.searchByCategory("Clothes");
        assert(!results.empty());
        assert(results[0].getCategory() == "clothes");
    }

    // Test searchByCategory with non-existing category
    {
        vector<PRODUCT> results = p1.searchByCategory("abc");
        assert(results.empty());
    }

    // Test getAllProducts
    {
        std::ostringstream buffer;
        std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
        p1.getAllProducts(true);
        std::cout.rdbuf(old);
        assert(!buffer.str().empty());
    }

    // Test saveToFile
    p1.saveToFile();
    std::ifstream file("my_file.csv");
    assert(file.is_open());
    file.close();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
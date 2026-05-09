#pragma once
#include <string>
#include <vector>
#include <queue>
#include <set>
#include "PRODUCT.h"

class PRODUCT_REPO
{
private:
    std::vector<PRODUCT> all_products;
    std::priority_queue<PRODUCT, std::vector<PRODUCT>, std::greater<PRODUCT>> sorted_price;
    void rebuildSorting();
    void showCategory();
    void showProductsByCategory(std::string category);

public:
    std::set<std::string> getCategoryInfo();
    PRODUCT_REPO();
    void addProduct(PRODUCT product);
    void removeProduct();
    void updateProduct();

    void reduceStock(std::string productName, int quantitySold);

    std::vector<PRODUCT> searchByName(std::string name);
    std::vector<PRODUCT> searchByCategory(std::string category);
    void getAllProducts(bool showCount);
    void saveToFile();
    void loadFromFile();
};
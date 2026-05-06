#pragma once
#include <string>
#include <vector>
#include <queue>
#include<set>
#include "PRODUCT.h"
using namespace std;
class PRODUCT_REPO
{
    private:
    vector<PRODUCT> all_products;
    priority_queue<PRODUCT, vector<PRODUCT>, greater<PRODUCT>> sorted_price;
    void rebuildSorting();
    set<string> getCategoryInfo();
    void showCategory();
    void showProductsByCategory(string category);
    public:
        PRODUCT_REPO();
        void addProduct(PRODUCT product);
        void removeProduct();
        void updateProduct();
        vector<PRODUCT> searchByName(string name);
        vector<PRODUCT> searchByCategory(string category);
        void getAllProducts(bool showCount);
        void saveToFile();
        void loadFromFile();
        void reduceStock(const std::string& productName, int quantity);
};
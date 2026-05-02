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
        void searchByName(string name);
        void searchByCategory(string category);
        void getAllProducts(bool showCount);
        void saveToFile();
        void loadFromFile();
};
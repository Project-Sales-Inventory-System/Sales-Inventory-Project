/*
PRODUCT_REPO class : manages all product-related operations in the system.

STANDARD LIBRARIES USED:
-string:Used for storing and manipulating text data.
-vector:Used for storing collections of data dynamically.
-queue:Used for queue-related data structures such as priority queues.
-set:Used for storing unique sorted elements.

PRIVATE DATA MEMBERS:
-all_products:Vector containing all products in the repository.
-sorted_price:Priority queue used to maintain products sorted by price.

PRIVATE FUNCTIONS:
-rebuildSorting():Rebuilds product sorting structure based on prices.
-showCategory():Displays all available product categories.
-showProductsByCategory(std::string category):Displays products belonging to a specific category.

PUBLIC FUNCTIONS:
-getCategoryInfo():Returns all unique product categories.
-PRODUCT_REPO():Constructor that initializes product repository.
-addProduct(PRODUCT product):Adds a new product to the repository.
-removeProduct():Removes a product from the repository.
-updateProduct():Updates existing product information.
-reduceStock(std::string productName, int quantitySold):Reduces stock quantity after a sale.
-searchByName(std::string name):Searches products using product name.
-searchByCategory(std::string category):Searches products belonging to a category.
-getAllProducts(bool showCount):Displays all products and optionally product count.
-saveToFile():Saves product data to file storage.
-loadFromFile():Loads product data from file storage.

*/
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
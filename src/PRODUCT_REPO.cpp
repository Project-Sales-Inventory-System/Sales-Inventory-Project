#include"../include/ConsoleHelper.h"
#include"../include/PRODUCT_REPO.h"
#include<iostream>
#include"../include/PRODUCT.h"
#include<iomanip>
#include<set>
#include<queue>
#include<vector>
#include<limits>
#include<sstream>
#include<fstream>
#include<algorithm>
#include"../include/stringUtlis.h"
using namespace std;

PRODUCT_REPO::PRODUCT_REPO() {
    loadFromFile();
    rebuildSorting();
}

void PRODUCT_REPO::addProduct(PRODUCT product)
{
    all_products.push_back(product);
    rebuildSorting();
    saveToFile();
}

void PRODUCT_REPO::rebuildSorting()
{
    while(!sorted_price.empty()) 
    {
        sorted_price.pop();
    }
        for(int i=0; i<all_products.size(); i++)
        {
            sorted_price.push(all_products[i]);
        }
}
std:: set<string> PRODUCT_REPO::getCategoryInfo()
{
    set<string> category;

        for(int i=0; i<all_products.size(); i++)
        {
             category.insert(all_products[i].getCategory());
        }
       return category;
}
void PRODUCT_REPO:: showCategory()
    {
        set<string> Info= getCategoryInfo();
       for(auto it: Info)
        {
            std::cout<<it<<std::endl;
        }
    }
    void PRODUCT_REPO::showProductsByCategory(string category)
    {
        for(int i=0; i<all_products.size(); i++)
        {
            if(category==all_products[i].getCategory())
            {
                std::cout << (i+1) << ". ";
                all_products[i].displaySearchInfo();
            }
        }
    }

void PRODUCT_REPO:: removeProduct()
{
    if(all_products.empty())
    {
        ConsoleHelper::SetColor(12);
        std::cout<<"⚠️ No product found, can't delete!!!"<<std::endl;
        return;
    }
    ConsoleHelper::SetColor(14);
    std::cout<<"Available Categories:"<<std::endl;
    showCategory();
    string choice;
    std::cout<<"Select the Category: ";
    std::cin>>choice;
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    choice = toLower(trim(choice));
    
    set<string> verify= getCategoryInfo();
    bool categoryFound = false;
    string actualCategory;
    
    for(const auto& cat : verify)
    {
        if(toLower(cat) == choice)
        {
            categoryFound = true;
            actualCategory = cat;
            break;
        }
    }
    
    if(!categoryFound)
    {
        ConsoleHelper::SetColor(12);
        std::cout<<"⚠️ Category not found!!"<<endl;
        return;
    }
    
    // Find all products in this category
    vector<int> matchingIndices;
    std::cout<<endl;
    std::cout<<"    PRODUCTS IN CATEGORY: "<<actualCategory<<"   "<<endl;
    std::cout<<"INDEX | PRODUCT NAME - PRICE"<<endl;
    std::cout<<"-------------------------------------------"<<endl;
    for(int i=0; i<all_products.size(); i++)
    {
        if(toLower(all_products[i].getCategory()) == choice)
        {
            matchingIndices.push_back(i);
            std::cout<<"  "<<matchingIndices.size()<<"    | ";
            all_products[i].displaySearchInfo();
        }
    }
    std::cout<<"-------------------------------------------"<<endl;
    
    if(matchingIndices.empty())
    {
        ConsoleHelper::SetColor(12);
        std::cout<<"⚠️ No products in this category!"<<endl;
        return;
    }
    
    int index;
    std::cout<<"Enter Index No. to remove (e.g., 1, 2, 3...): ";
    std::cin>>index;
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if(index<=0 || index>matchingIndices.size())
    {
        ConsoleHelper::SetColor(12);
        std::cout<<"⚠️ Invalid choice!"<<endl;
        return;
    }
    
    int actualIndex = matchingIndices[index-1];
    all_products.erase(all_products.begin() + actualIndex);
    saveToFile();
    std::cout<<"Product removed successfully!"<<endl;
    ConsoleHelper::SetColor(10);
    std::cout<<"⚠️ Product removed successfully!"<<endl;
}
void PRODUCT_REPO:: updateProduct()
{
    if(all_products.empty())
    {
        ConsoleHelper::SetColor(12);
        std::cout<<"⚠️ No product found."<<endl;
        std::cout<<"⚠️ Can't Update."<<endl;
        return;
    }
    std::cout<<"Available Categories:"<<endl;
    showCategory();
    string choice;

    std::cout<<"Select the Category: ";
    std::cin>>choice;
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    choice = toLower(trim(choice));
    
    set<string> verify= getCategoryInfo();
    bool categoryFound = false;
    string actualCategory;
    
    for(const auto& cat : verify)
    {
        if(toLower(cat) == choice)
        {
            categoryFound = true;
            actualCategory = cat;
            break;
        }
    }
    
    if(!categoryFound)
    {
        ConsoleHelper::SetColor(12);
        std::cout<<"⚠️ Category not found!!"<<endl;
        return;
    }
    
    vector<int> matchingIndices;
    std::cout<<endl;
    std::cout<<"PRODUCTS IN CATEGORY: "<<actualCategory<<" "<<endl;
    ConsoleHelper::SetColor(10);
    std::cout<<"INDEX | PRODUCT NAME - PRICE"<<endl;
    ConsoleHelper::SetColor(15);
    std::cout<<"-------------------------------------------"<<endl;
    ConsoleHelper::ResetColor();
    for(int i=0; i<all_products.size(); i++)
    {
        if(toLower(all_products[i].getCategory()) == choice)
        {
            matchingIndices.push_back(i);
            std::cout<<"  "<<matchingIndices.size()<<"    | ";
            all_products[i].displaySearchInfo();
        }
    }
    ConsoleHelper::SetColor(15);
    std::cout<<"-------------------------------------------"<<endl;
    ConsoleHelper::ResetColor();

    if(matchingIndices.empty())
    {
        ConsoleHelper::SetColor(12);
        std::cout<<"⚠️ No products in this category!"<<endl;
        ConsoleHelper::ResetColor();
        return;
    }
    
    int index;
    std::cout<<"Enter Index No. to update (e.g., 1, 2, 3...): ";
    std::cin>>index;
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
    ConsoleHelper::SetColor(12);
    if(index<=0 || index>matchingIndices.size())
    {
        std::cout<<" ⚠️ Invalid choice!"<<endl;
        ConsoleHelper::ResetColor();
        return;
    }
    
    int actualIndex = matchingIndices[index-1];
    
    std::cout<<endl;
    ConsoleHelper::SetColor(10);
    std::cout<<"SELECTED PRODUCT TO UPDATE:"<<endl;
    ConsoleHelper::SetColor(15);
    std::cout<<"==============================================="<<endl;
    std::cout<<"Name: "<<all_products[actualIndex].getName()<<endl;
    std::cout<<"Price: Rs"<<std::fixed<<std::setprecision(2)<<all_products[actualIndex].getPrice()<<endl;
    std::cout<<"Quantity: "<<all_products[actualIndex].getQuantity()<<endl;
    std::cout<<"Category: "<<all_products[actualIndex].getCategory()<<endl;
    ConsoleHelper::SetColor(15);    
    std::cout<<"==============================================="<<endl;
    ConsoleHelper::ResetColor();
    std::cout<<endl;
    
    ConsoleHelper::SetColor(10);
    std::cout<<"What do you want to Update:"<<endl;
    ConsoleHelper::SetColor(15);
    ConsoleHelper::PrintDivider();
    std::cout<<"1. Name"<<endl;
    std::cout<<"2. Price"<<endl;
    std::cout<<"3. Quantity"<<endl;
    ConsoleHelper::SetColor(15);
    ConsoleHelper::PrintDivider();
    ConsoleHelper::ResetColor();
    int option;
    std::cout<<"Select: ";
    std::cin>>option;
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if(option==1)
    {
        string name;
        std::cout<<"Current Name: "<<all_products[actualIndex].getName()<<endl;
        std::cout<<"Enter new name: ";
        getline(std::cin, name);
        all_products[actualIndex].setName(name);
        ConsoleHelper::SetColor(10);
        std::cout<<"Name updated successfully!"<<endl;
        ConsoleHelper::ResetColor();
    }
    else if(option==2)
    {
        double price;
        std::cout<<"Current Price: Rs"<<std::fixed<<std::setprecision(2)<<all_products[actualIndex].getPrice()<<endl;
        std::cout<<"Enter new price: ";
        std::cin>>price;
        std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
        all_products[actualIndex].setPrice(price);
        ConsoleHelper::SetColor(10);
        std::cout<<"Price updated successfully!"<<endl;
        ConsoleHelper::ResetColor();
    }
    else if(option==3)
    {
        int qty;
        std::cout<<"Current Quantity: "<<all_products[actualIndex].getQuantity()<<endl;
        std::cout<<"Enter new quantity: ";
        std::cin>>qty;
        std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
        all_products[actualIndex].setQuantity(qty);
        ConsoleHelper::SetColor(10);
        std::cout<<"Quantity updated successfully!"<<endl;
        ConsoleHelper::ResetColor();
    }
    else
    {
        ConsoleHelper::SetColor(12);
        std::cout<<"⚠️ Invalid option!"<<endl;
        ConsoleHelper::ResetColor();
    }
    rebuildSorting();
}
vector<PRODUCT> PRODUCT_REPO::searchByName(string name)
{
    string input = toLower(trim(name));
    vector<PRODUCT> results;

    for (const auto& product : all_products)
    {
        string productName = toLower(trim(product.getName()));
        if (productName.find(input) != string::npos)
        {
            results.push_back(product);
        }
    }

    return results;
}
void PRODUCT_REPO::reduceStock(string productName, int quantitySold) {
    bool found = false;
    string searchName = toLower(trim(productName));

    for (auto& p : all_products) {
        if (toLower(trim(p.getName())) == searchName) {
            int currentQty = p.getQuantity();
            if (currentQty >= quantitySold) {
                p.setQuantity(currentQty - quantitySold);
            } else {
                p.setQuantity(0);
            }
            found = true;
            break;
        }
    }
    
    if (found) {
        rebuildSorting();
        saveToFile(); 
    }
}
vector<PRODUCT> PRODUCT_REPO::searchByCategory(string category)
{
    string cat = toLower(trim(category));
    vector<PRODUCT> results;

    for (const auto& product : all_products)
    {
        if (toLower(trim(product.getCategory())) == cat)
        {
            results.push_back(product);
        }
    }

    // Display the results
    if (results.empty())
    {
        cout << "⚠️ No products found in category: " << category << endl;
        return results;
    }

    cout << endl;
    cout << "PRODUCTS IN CATEGORY: " << category << " -------" << endl;
    cout << "PRODUCT NAME - PRICE - STOCK" << endl;
    cout << "-------------------------------------------" << endl;
    for (const auto& product : results)
    {
        product.displaySearchInfo();
    }
    cout << "-------------------------------------------" << endl;

    return results;
}
void PRODUCT_REPO:: getAllProducts(bool showCount)
{
    ConsoleHelper::Header();
    cout << setfill(' ');// ye
    ConsoleHelper::SetColor(15); 
    cout << "\n" << string(58, '=') << endl;
    ConsoleHelper::SetColor(10);
    cout << setw(35) << "  TOTAL PRODUCTS" << endl;
    ConsoleHelper::SetColor(15);
    cout << string(58, '=') << "\n" << endl;
    ConsoleHelper::ResetColor();
    
    rebuildSorting();
    int total_count = all_products.size();
    auto temp = sorted_price;
    while(!temp.empty())
    {
        ConsoleHelper::SetColor(10);
        temp.top().displaySearchInfo();
        temp.pop();
    }
    ConsoleHelper::PrintDivider();
    if (showCount==true)
    {
        std::cout<<"Total Products In System: "<<total_count<<endl;
    }
}
   void PRODUCT_REPO::saveToFile() {
    ofstream my_file("my_file.csv");
    if(!my_file) {
        ConsoleHelper::SetColor(12);
        cout << "⚠️ Error: Could not open file for saving!" << endl;
        ConsoleHelper::ResetColor();
        return;
    }
    for(const auto& p : all_products) {
        my_file << p.getCategory() << "," 
                << p.getName() << "," 
                << p.getPrice() << "," 
                << p.getQuantity() << endl;
    }
    my_file.close();
}
    void PRODUCT_REPO::loadFromFile() {
    all_products.clear();
    ifstream my_file("my_file.csv");
    if(!my_file) return;

    string line;
    while(getline(my_file, line)) {
        stringstream ss(line);
        string category, name, priceStr, qtyStr;
        
        getline(ss, category, ',');
        getline(ss, name, ',');
        getline(ss, priceStr, ',');
        getline(ss, qtyStr, ',');

        if(!category.empty() && !name.empty()) {
            PRODUCT p(category, name, stod(priceStr), stoi(qtyStr));
            all_products.push_back(p);
            sorted_price.push(p);
        }
    }
    my_file.close();
}
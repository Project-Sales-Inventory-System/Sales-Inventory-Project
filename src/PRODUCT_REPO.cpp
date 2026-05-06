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

void PRODUCT_REPO::addProduct(PRODUCT product)
{
    all_products.push_back(product);
    sorted_price.push(product);
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
        std::cout<<"No product found, can't delete!!!"<<std::endl;
        return;
    }
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
        std::cout<<"Category not found!!"<<endl;
        return;
    }
    
    // Find all products in this category
    vector<int> matchingIndices;
    std::cout<<endl;
    std::cout<<"------- PRODUCTS IN CATEGORY: "<<actualCategory<<" -------"<<endl;
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
        std::cout<<"No products in this category!"<<endl;
        return;
    }
    
    int index;
    std::cout<<"Enter Index No. to remove (e.g., 1, 2, 3...): ";
    std::cin>>index;
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if(index<=0 || index>matchingIndices.size())
    {
        std::cout<<"Invalid choice!"<<endl;
        return;
    }
    
    int actualIndex = matchingIndices[index-1];
    all_products.erase(all_products.begin() + actualIndex);
    std::cout<<"Product removed successfully!"<<endl;
}
void PRODUCT_REPO:: updateProduct()
{
    if(all_products.empty())
    {
        std::cout<<"No product found."<<endl;
        std::cout<<"Can't Update."<<endl;
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
        std::cout<<"Category not found!!"<<endl;
        return;
    }
    
    // Find all products in this category
    vector<int> matchingIndices;
    std::cout<<endl;
    std::cout<<"------- PRODUCTS IN CATEGORY: "<<actualCategory<<" -------"<<endl;
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
        std::cout<<"No products in this category!"<<endl;
        return;
    }
    
    int index;
    std::cout<<"Enter Index No. to update (e.g., 1, 2, 3...): ";
    std::cin>>index;
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if(index<=0 || index>matchingIndices.size())
    {
        std::cout<<"Invalid choice!"<<endl;
        return;
    }
    
    int actualIndex = matchingIndices[index-1];
    
    // Show selected product confirmation
    std::cout<<endl;
    std::cout<<"==============================================="<<endl;
    std::cout<<"SELECTED PRODUCT TO UPDATE:"<<endl;
    std::cout<<"Name: "<<all_products[actualIndex].getName()<<endl;
    std::cout<<"Price: Rs"<<std::fixed<<std::setprecision(2)<<all_products[actualIndex].getPrice()<<endl;
    std::cout<<"Quantity: "<<all_products[actualIndex].getQuantity()<<endl;
    std::cout<<"Category: "<<all_products[actualIndex].getCategory()<<endl;
    std::cout<<"==============================================="<<endl;
    std::cout<<endl;
    
    std::cout<<"What do you want to Update:"<<endl;
    std::cout<<"1. Name"<<endl;
    std::cout<<"2. Price"<<endl;
    std::cout<<"3. Quantity"<<endl;
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
        std::cout<<"Name updated successfully!"<<endl;
    }
    else if(option==2)
    {
        double price;
        std::cout<<"Current Price: Rs"<<std::fixed<<std::setprecision(2)<<all_products[actualIndex].getPrice()<<endl;
        std::cout<<"Enter new price: ";
        std::cin>>price;
        std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
        all_products[actualIndex].setPrice(price);
        std::cout<<"Price updated successfully!"<<endl;
    }
    else if(option==3)
    {
        int qty;
        std::cout<<"Current Quantity: "<<all_products[actualIndex].getQuantity()<<endl;
        std::cout<<"Enter new quantity: ";
        std::cin>>qty;
        std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
        all_products[actualIndex].setQuantity(qty);
        std::cout<<"Quantity updated successfully!"<<endl;
    }
    else
    {
        std::cout<<"Invalid option!"<<endl;
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

    return results;
}
void PRODUCT_REPO:: getAllProducts(bool showCount)
{
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("------TOTAL PRODUCTS------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
    
    rebuildSorting();
    int total_count = all_products.size();
    auto temp = sorted_price;
    while(!temp.empty())
    {
        temp.top().displaySearchInfo();
        temp.pop();
    }
    ConsoleHelper::PrintDivider();
    if (showCount==true)
    {
        std::cout<<"Total Products In System: "<<total_count<<endl;
    }
}
    void PRODUCT_REPO:: saveToFile()
    {
        std::ofstream my_file("my_file.csv");
        if(!my_file)
        {
            std::cout<<"file not created";
        }
        for(int i=0; i<all_products.size(); i++)
        {
            my_file<<all_products[i].getCategory()<<","<<all_products[i].getName()<<","<<all_products[i].getPrice()<<","<<all_products[i].getQuantity()<<endl;
        }
        

    }
    void PRODUCT_REPO:: loadFromFile()
    {
        ifstream my_file("my_file.csv", ios::in);
        if(!my_file)
        {
            std::cout<<"file doesn't exist";
            return;
        }
        string line;
        while(getline(my_file, line))
        {
            std::stringstream ss(line);
            std::string category, name;
            double price;
            int qty;
            getline(ss, category, ',');
            getline(ss,name,',');
            ss>>price;
            ss.ignore();
            ss>>qty;
            ss.ignore();
            PRODUCT p(category,name, price, qty);
            all_products.push_back(p);
            sorted_price.push(p);
            
        }
    }
    PRODUCT_REPO::PRODUCT_REPO()
    {
        loadFromFile();
    }

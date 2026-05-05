#include"../include/ConsoleHelper.h"
#include"PRODUCT_REPO.h"
#include<iostream>
#include"PRODUCT.h"
#include<iomanip>
#include<set>
#include<queue>
#include<vector>
#include<limits>
#include<sstream>
#include<fstream>
#include<algorithm>
#include<stringUtlis.h>
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
            cout<<it<<endl;
        }
    }
    void PRODUCT_REPO::showProductsByCategory(string category)
    {
        for(int i=0; i<all_products.size(); i++)
        {
            if(category==all_products[i].getCategory())
            {
                cout << (i+1) << ". ";
                all_products[i].displaySearchInfo();
            }
        }
    }

void PRODUCT_REPO:: removeProduct()
{
    if(all_products.empty())
    {
        cout<<"No product found, can't delete!!!"<<endl;
        return;
    }
    cout<<"Available Categories:"<<endl;
    showCategory();
    string choice;
    cout<<"Select the Category: ";
    cin>>choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
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
        cout<<"Category not found!!"<<endl;
        return;
    }
    
    // Find all products in this category
    vector<int> matchingIndices;
    cout<<endl;
    cout<<"------- PRODUCTS IN CATEGORY: "<<actualCategory<<" -------"<<endl;
    cout<<"INDEX | PRODUCT NAME - PRICE"<<endl;
    cout<<"-------------------------------------------"<<endl;
    for(int i=0; i<all_products.size(); i++)
    {
        if(toLower(all_products[i].getCategory()) == choice)
        {
            matchingIndices.push_back(i);
            cout<<"  "<<matchingIndices.size()<<"    | ";
            all_products[i].displaySearchInfo();
        }
    }
    cout<<"-------------------------------------------"<<endl;
    
    if(matchingIndices.empty())
    {
        cout<<"No products in this category!"<<endl;
        return;
    }
    
    int index;
    cout<<"Enter Index No. to remove (e.g., 1, 2, 3...): ";
    cin>>index;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if(index<=0 || index>matchingIndices.size())
    {
        cout<<"Invalid choice!"<<endl;
        return;
    }
    
    int actualIndex = matchingIndices[index-1];
    all_products.erase(all_products.begin() + actualIndex);
    cout<<"Product removed successfully!"<<endl;
}
void PRODUCT_REPO:: updateProduct()
{
    if(all_products.empty())
    {
        cout<<"No product found."<<endl;
        cout<<"Can't Update."<<endl;
        return;
    }
    cout<<"Available Categories:"<<endl;
    showCategory();
    string choice;
    cout<<"Select the Category: ";
    cin>>choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
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
        cout<<"Category not found!!"<<endl;
        return;
    }
    
    // Find all products in this category
    vector<int> matchingIndices;
    cout<<endl;
    cout<<"------- PRODUCTS IN CATEGORY: "<<actualCategory<<" -------"<<endl;
    cout<<"INDEX | PRODUCT NAME - PRICE"<<endl;
    cout<<"-------------------------------------------"<<endl;
    for(int i=0; i<all_products.size(); i++)
    {
        if(toLower(all_products[i].getCategory()) == choice)
        {
            matchingIndices.push_back(i);
            cout<<"  "<<matchingIndices.size()<<"    | ";
            all_products[i].displaySearchInfo();
        }
    }
    cout<<"-------------------------------------------"<<endl;
    
    if(matchingIndices.empty())
    {
        cout<<"No products in this category!"<<endl;
        return;
    }
    
    int index;
    cout<<"Enter Index No. to update (e.g., 1, 2, 3...): ";
    cin>>index;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if(index<=0 || index>matchingIndices.size())
    {
        cout<<"Invalid choice!"<<endl;
        return;
    }
    
    int actualIndex = matchingIndices[index-1];
    
    // Show selected product confirmation
    cout<<endl;
    cout<<"==============================================="<<endl;
    cout<<"SELECTED PRODUCT TO UPDATE:"<<endl;
    cout<<"Name: "<<all_products[actualIndex].getName()<<endl;
    cout<<"Price: Rs"<<fixed<<setprecision(2)<<all_products[actualIndex].getPrice()<<endl;
    cout<<"Quantity: "<<all_products[actualIndex].getQuantity()<<endl;
    cout<<"Category: "<<all_products[actualIndex].getCategory()<<endl;
    cout<<"==============================================="<<endl;
    cout<<endl;
    
    cout<<"What do you want to Update:"<<endl;
    cout<<"1. Name"<<endl;
    cout<<"2. Price"<<endl;
    cout<<"3. Quantity"<<endl;
    int option;
    cout<<"Select: ";
    cin>>option;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if(option==1)
    {
        string name;
        cout<<"Current Name: "<<all_products[actualIndex].getName()<<endl;
        cout<<"Enter new name: ";
        getline(cin, name);
        all_products[actualIndex].setName(name);
        cout<<"Name updated successfully!"<<endl;
    }
    else if(option==2)
    {
        double price;
        cout<<"Current Price: Rs"<<fixed<<setprecision(2)<<all_products[actualIndex].getPrice()<<endl;
        cout<<"Enter new price: ";
        cin>>price;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        all_products[actualIndex].setPrice(price);
        cout<<"Price updated successfully!"<<endl;
    }
    else if(option==3)
    {
        int qty;
        cout<<"Current Quantity: "<<all_products[actualIndex].getQuantity()<<endl;
        cout<<"Enter new quantity: ";
        cin>>qty;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        all_products[actualIndex].setQuantity(qty);
        cout<<"Quantity updated successfully!"<<endl;
    }
    else
    {
        cout<<"Invalid option!"<<endl;
    }
    rebuildSorting();
}
void PRODUCT_REPO::searchByName(string name)
{
    string input = toLower(trim(name));

for (int i = 0; i < all_products.size(); i++)
{
    string productName = all_products[i].getName(); // already clean

    if (productName.find(input) != string::npos)
    {
        all_products[i].displaySearchInfo();
    }
}
}
void PRODUCT_REPO::searchByCategory(string category)
{
    string originalCategory = category;
    category = toLower(trim(category));

    vector<int> matchingIndices;
    string actualCategory = "";

    for(int i = 0; i < all_products.size(); i++)
    {
        if(toLower(trim(all_products[i].getCategory())) == category)
        {
            if(actualCategory.empty())
                actualCategory = all_products[i].getCategory();

            matchingIndices.push_back(i);
        }
    }

    if(matchingIndices.empty())
    {
        cout << "No products found in category: " << originalCategory << endl;
        return;
    }

    cout << "\n------- PRODUCTS IN CATEGORY: " << actualCategory << " -------\n";
    cout << "INDEX | PRODUCT NAME - PRICE\n";
    cout << "-------------------------------------------\n";

    for(int idx = 0; idx < matchingIndices.size(); idx++)
    {
        cout << "  " << (idx + 1) << "    | ";
        all_products[matchingIndices[idx]].displaySearchInfo();
    }

    cout << "-------------------------------------------\n";
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
        cout<<"Total Products In System: "<<total_count<<endl;
    }
}
    void PRODUCT_REPO:: saveToFile()
    {
        std::ofstream my_file("my_file.csv");
        if(!my_file)
        {
            cout<<"file not created";
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
            cout<<"file doesn't exist";
            return;
        }
        string line;
        while(getline(my_file, line))
        {
            std::stringstream ss(line);
            std:: string category, name;
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
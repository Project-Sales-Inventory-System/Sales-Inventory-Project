#include"SELLER.h"
#include"../include/USER.h"
#include"../include/BILL.h"
#include"../include/PRODUCT.h"
#include"../include/AUTHORITY_SERVICE.h"
#include"../include/ConsoleHelper.h"
#include<string>
#include<iostream>
#include<iomanip>
#include<limits>
#include"USER_ACCOUNT.h"
using namespace std;

SELLER:: SELLER(USER_ACCOUNT sDetails, PRODUCT_REPO& repository){
    user_acc = sDetails;
    repo = &repository;
}

std:: string SELLER:: getUsername() const{
    return user_acc.getUsername();
}

bool SELLER:: authenticate(AUTHORITY_SERVICE& auth) {
    return auth.verifyClient(user_acc.getUsername(), "");   
}

void SELLER:: performAction(){
    cout<<"Seller interacting"<<endl;
}

void SELLER::SellerMenu()
{
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("--------SELLER MENU -------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
    cout << "[1] Add Product" << endl;
    cout << "[2] Search Product" << endl;
    cout << "[3] View Products" << endl;
    cout << "[4] Logout" << endl;
    cout << "Enter your choice: ";
}

void SELLER:: viewProduct(std:: string){
    ConsoleHelper::ClearScreen();
    if (repo)
    {
        repo->getAllProducts(false);
    }
}

void SELLER:: searchProduct(std:: string keyword){
    ConsoleHelper::ClearScreen();
    ConsoleHelper::PrintHeader("SEARCH PRODUCTS");
    ConsoleHelper::PrintHeader("-SEARCH OPTION-");
    ConsoleHelper::PrintDivider();
    cout << "[1] Search by Product Name" << endl;
    cout << "[2] Search by Category" << endl;
    cout << "[3] Back to Menu" << endl;
    ConsoleHelper::PrintDivider();
    cout << "Enter your choice: ";
    
    int searchChoice;
    cin >> searchChoice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    switch(searchChoice)
    {
        case 1:
        {
            string productName;
            cout << "Enter product name to search: ";
            getline(cin, productName);
            
            if (!productName.empty() && repo)
            {
                repo->searchByName(productName);
            }
            else if (productName.empty())
            {
                cout << "Error: Product name cannot be empty!" << endl;
            }
            break;
        }
        case 2:
        {
            string category;
            cout << "Enter product category to search: ";
            getline(cin, category);
            
            if (!category.empty() && repo)
            {
                repo->searchByCategory(category);
            }
            else if (category.empty())
            {
                cout << "Error: Category cannot be empty!" << endl;
            }
            break;
        }
        case 3:
            break;
        default:
            cout << "Invalid choice!" << endl;
    }
    
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void SELLER:: addProduct(PRODUCT product){
    if (repo)
    {
        repo->addProduct(product);
        repo->saveToFile();
    }
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("--------PRODUCT ADDED SUCESSFULLY-------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
}


void SELLER::startSession()
{
    bool sellerLoggedIn = true;
    while (sellerLoggedIn)
    {
        SellerMenu();
        int choice;
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again." << endl;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
            case 1:
            {
                string category, name;
                double price;
                int qty;
                cout << "Enter product category: ";
                getline(cin, category);
                cout << "Enter product name: ";
                getline(cin, name);
                cout << "Enter product price: ";
                cin >> price;
                cout << "Enter product quantity: ";
                cin >> qty;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                PRODUCT product(category, name, price, qty);
                addProduct(product);
                break;
            }
            case 2:
                searchProduct("");
                break;
            case 3:
                viewProduct("");
                break;
            case 4:
                cout << "Logging out..." << endl;
                sellerLoggedIn = false;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}
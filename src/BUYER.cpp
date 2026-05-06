#include"BUYER.h"
#include<iostream>
#include<iomanip>
#include<limits>
using namespace std;
#include"../include/ConsoleHelper.h"
#include"../include/USER.h"
#include<CART.h>
//#include"../include/BILL.h"
#include"../include/PRODUCT.h"
#include"AUTHORITY_SERVICE.h"
    BUYER::BUYER(USER_ACCOUNT Bdetails, PRODUCT_REPO& repository)
    {
    user_acc = Bdetails;
    repo = &repository;
}
bool BUYER:: authenticate(AUTHORITY_SERVICE& auth) {
     return auth.verifyClient(user_acc.getUsername(), "");
}
void BUYER:: performAction() {
    cout<<"Buyer interacting"<<endl;
}
std:: string BUYER:: getUsername()const{
    return user_acc.getUsername();
}
void BUYER::BuyerMenu()
{
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("--------BUYER MENU -------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();  
    cout << "[1] View Product" << endl;
    cout << "[2] Search Product" << endl;
    cout << "[3] Logout" << endl;
    cout<<"Enter your choice: ";
    // cout << "[4] View Cart" << endl;
    // cout << "[5] Edit Cart" << endl;
    
    }

void BUYER:: viewProduct(std:: string) {
    ConsoleHelper::ClearScreen();
    if (repo)
    {
        repo->getAllProducts(false);
    }
}
void BUYER:: searchProduct(std:: string keyword){
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
void BUYER:: startSession()
{
    bool buyerLoggedIn= true;
    while(buyerLoggedIn)
    {
        BuyerMenu();
        int choice;
        cin>> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again." << endl;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(choice)
        {
            case 1: viewProduct(""); break;
            case 2: searchProduct(""); break;
            case 3:
                cout<<"Logging out..."<<endl;
                buyerLoggedIn=false; 
                break;
            default:cout<<"Invalid choice"<<endl;
        }
    }
}
void BUYER:: myProducts(){}

void BUYER:: placeOrder(){
        //LOGIC
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("--------PLACE ORDER-------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
}
void BUYER:: viewCart(){
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("--------VIEW CART-------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
    //LOGIC
}
void BUYER :: editCart(){
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("--------EDIT CART-------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
    //LOGIC
}
void  BUYER:: requestBill(){
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("--------BILL-------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
    //LOGIC
}

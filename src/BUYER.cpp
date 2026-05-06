#include"../include/BUYER.h"
#include<iostream>
#include<iomanip>
#include<limits>
using namespace std;
#include"../include/ConsoleHelper.h"
#include"../include/USER.h"
#include"../include/CART.h"
//#include"../include/BILL.h"
#include"../include/PRODUCT.h"
#include"../include/AUTHORITY_SERVICE.h"
    BUYER::BUYER(USER_ACCOUNT Bdetails, PRODUCT_REPO& repository)
    {
        CART cart;
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
    cout << "[4] View Cart" << endl;
    cout << "[5] Edit Cart" << endl;
    cout<<"Enter your choice: ";

    
    }

void BUYER:: viewProduct(std:: string) {
    ConsoleHelper::ClearScreen();
    if (repo)
    {
        repo->getAllProducts(false);
    }
}
void BUYER::searchProduct(std::string keyword) {
    bool search_again = true;

    while (search_again) {
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

        if (searchChoice == 3) return;  

        vector<PRODUCT> results;

        switch (searchChoice) {
            case 1: {
                string productName;
                cout << "Enter product name to search: ";
                getline(cin, productName);
                if (productName.empty()) {
                    cout << "Error: Product name cannot be empty!" << endl;
                } else {
                    results = repo->searchByName(productName);
                }
                break;
            }
            case 2: {
                string category;
                cout << "Enter product category to search: ";
                getline(cin, category);
                if (category.empty()) {
                    cout << "Error: Category cannot be empty!" << endl;
                } else {
                    results = repo->searchByCategory(category);
                }
                break;
            }
            default:
                cout << "Invalid choice!" << endl;
                continue; 
        }

        if (results.empty()) {
            cout << "No result found. Press Enter...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        bool interacting = true;
        while (interacting) {
            cout << endl;
            cout << "ADD TO CART: Enter index number and A, e.g. [1A]" << endl;
            cout << "TO VIEW CART: Enter V" << endl;
            cout << "TO SEARCH AGAIN: Enter S" << endl;
            cout << "TO EXIT: Enter 0" << endl;
            cout << "Enter your choice: ";

            string choice;
            getline(cin, choice);

            if (choice == "0") {
                search_again = false;
                interacting = false;
            }
            else if (choice.size() >= 2 && (choice.back() == 'a' || choice.back() == 'A')) {
                string indexStr = choice.substr(0, choice.size() - 1);
                int id = stoi(indexStr);
                if (id < 1 || id > results.size()) {  
                    cout << "Invalid index" << endl;
                } else {
                    cart.addItem(results[id - 1]);
                    cout << results[id - 1].getName() << " added to Cart!!" << endl;
                }
            }
            else if (choice == "s" || choice == "S") {
                interacting = false; 
            }
            else if (choice == "v" || choice == "V") {
                cart.viewCart();
            }
            else {
                cout << "Invalid input" << endl;
            }
        }
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
    cart.viewCart();
}
void BUYER :: editCart(){
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("--------EDIT CART-------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
    bool editing = true;
    while(editing)
    {
        ConsoleHelper::ClearScreen();
        cart.viewCart();
        if(cart.getItemCount()==0)
        {
            cout<<"Cart is empty!!"<<endl;
            editing=false;
            break;
        }
        cout << "[R] Remove Item\n";
        cout << "[U] Update Quantity\n";
        cout << "[B] Back to Menu\n";
        cout << "Enter choice: ";
        
        char choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch(choice)
        {
            case 'R':
            case 'r':
            {
                string productName;
                cout << "Enter product name to remove: ";
                getline(cin, productName);
                cart.removeItem(productName);
                break;
            }
            case 'U':
            case 'u':
            {
                string productName;
                int qty;
                cout << "Enter product name to update: ";
                getline(cin, productName);
                cout << "Enter new quantity: ";
                cin >> qty;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cart.updateQuantity(productName, qty);
                break;
            }
            case 'B':
            case 'b':
                editing = false;
                break;
            default:
                cout << "Invalid choice!" << endl;
                cout << "Press Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}
    

void  BUYER:: requestBill(){
    ConsoleHelper::SetColor(11);
    ConsoleHelper::PrintHeader("--------BILL-------");
    ConsoleHelper::ResetColor();
    ConsoleHelper::PrintDivider();
    //LOGIC
}
